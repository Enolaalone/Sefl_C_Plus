/* Return the offset of one string within another.
   Copyright (C) 1994-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _LIBC
# include <config.h>
#endif

#include <string.h>

#define RETURN_TYPE char *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((void*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#include "str-two-way.h"

#undef strstr

#ifndef STRSTR
#define STRSTR strstr
#endif

static inline char *
strstr2 (const unsigned char *hs, const unsigned char *ne)//ne只有两个字符
{
  uint32_t h1 = (ne[0] << 16) | ne[1];//将ne中的两个字符装入h1,uint32_t 32位相对于unsigned int
  uint32_t h2 = 0;
  for (int c = hs[0]; h1 != h2 && c != 0; c = *++hs)//*++hs访问下一个字符
      h2 = (h2 << 16) | c;//复制int c到h2，一次只复制一个字符，比较两个字符
  return h1 == h2 ? (char *)hs - 2 : NULL;// h1和h2匹配上则只返回减去两个匹配字符的地址
}

static inline char *
strstr3 (const unsigned char *hs, const unsigned char *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);//将3个字符装入int h1由小到大
  uint32_t h2 = 0;
  for (int c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;//将复制到c的最低位//并左移空出一个字节方便下一次复制
  return h1 == h2 ? (char *)hs - 3 : NULL;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % sizeof (shift))

/* Fast strstr algorithm with guaranteed linear-time performance.
   Small needles up to size 3 use a dedicated linear search.  Longer needles
   up to size 256 use a novel modified Horspool algorithm.  It hashes pairs
   of characters to quickly skip past mismatches.  The main search loop only
   exits if the last 2 characters match, avoiding unnecessary calls to memcmp
   and allowing for a larger skip if there is no match.  A self-adapting
   filtering check is used to quickly detect mismatches in long needles.
   By limiting the needle length to 256, the shift table can be reduced to 8
   bits per entry, lowering preprocessing overhead and minimizing cache effects.
   The limit also implies worst-case performance is linear.
   Needles larger than 256 characters use the linear-time Two-Way algorithm.  */
char *
STRSTR (const char *haystack, const char *needle)//在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'。
{
  const unsigned char *hs = (const unsigned char *) haystack;
  const unsigned char *ne = (const unsigned char *) needle;

  /* Handle short needle special cases first.  */
  if (ne[0] == '\0')//ne为空
    return (char *)hs;//hs为空
  hs = (const unsigned char *)strchr ((const char*)hs, ne[0]);
  if (hs == NULL || ne[1] == '\0')
    return (char*)hs;
  if (ne[2] == '\0')
    return strstr2 (hs, ne);
  if (ne[3] == '\0')
    return strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = strlen ((const char*)ne);
  size_t hs_len = __strnlen ((const char*)hs, ne_len | 512);//如果hs大于ne长度返回ne_len | 512固定值，否则直接返回hs长度
  if (hs_len < ne_len)//hs长度小于 ne
    return NULL;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  if (memcmp (hs, ne, ne_len) == 0)//hs开头就是ne，直接返回hs
    return (char *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  if (__glibc_unlikely (ne_len > 256))//如果needle长度超过256，使用Two-Way算法。
    return two_way_long_needle (hs, hs_len, ne, ne_len);

  const unsigned char *end = hs + hs_len - ne_len;//因此，end = hs + hs_len - ne_len确切地指向了在保证needle完全位于haystack内部时，haystack上的最后一个可能的搜索起始位置。
  uint8_t shift[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t offset = 0;

  /* Initialize bad character shift hash table.  */
  memset (shift, 0, sizeof (shift));
  for (int i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;//传入地址得到哈希值（256以内）
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
//   这行代码的结果是计算出当在haystack中找到与needle末尾匹配的字符对，但不是完整的needle匹配时，可以跳过的字符数。这是为了在确认当前位置不是完整匹配后，快速移动到下一个潜在的匹配位置。
// shift1的值反映了从needle的最后一个字符向前跳过多少个字符，直到到达一个新的搜索起点。这种跳过机制基于needle中字符的分布，旨在减少不必要的比较，提高搜索效率。
// 总的来说，shift1是一种基于needle末尾字符对的预计算跳跃策略，用于在搜索过程中优化性能，它确保在找到部分匹配时能够有效地跳转到下一个潜在的匹配位置，从而避免在不可能匹配的区段内进行过多的字符比较。
  shift[hash2 (ne + m1)] = m1;

  while (1)
    {
      if (__glibc_unlikely (hs > end))
	{
	  end += __strnlen ((const char*)end + m1 + 1, 2048);//扩大搜索范围
	  if (hs > end)
	    return NULL;
	}

      /* Skip past character pairs not in the needle.  */
      do
	{
	  hs += m1;//指向一个ne 长度
	  tmp = shift[hash2 (hs)];//返回匹配到的字符在ne的相对位置
	}
      while (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;//调整指针指向可能匹配的ne的头
      if (tmp < m1)
	continue;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      if (m1 < 15 || memcmp (hs + offset, ne + offset, 8) == 0)//快速过滤，匹配字符较小《15，或者偏移后前八字符一致
	{
	  if (memcmp (hs, ne, m1) == 0)//比较ne_len长度的字符
	    return (void *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (strstr)
