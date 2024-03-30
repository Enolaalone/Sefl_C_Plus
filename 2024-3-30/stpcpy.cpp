/* Copyright (C) 1992-2024 Free Software Foundation, Inc.
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

#define NO_MEMPCPY_STPCPY_REDIRECT
#include <string.h>
#include <stdint.h>
#include <memcopy.h>
#include <string-fzb.h>
#include <string-misc.h>

#undef __stpcpy
#undef stpcpy

#ifndef STPCPY
# define STPCPY __stpcpy
#endif

static __always_inline char *
write_byte_from_word (op_t *dest, op_t word)//从word中按字节写入
{
  char *d = (char *) dest;//地址转换为(char*)
  for (size_t i = 0; i < OPSIZ; i++, ++d)//按照系统位数抓取字节
    {
      char c = extractbyte (word, i);//摘录字节
      *d = c;//写入字节
      if (c == '\0')//如果是末尾结束
	break;
    }
  return d;
}
//op_t单位批量处理
static __always_inline char *
stpcpy_aligned_loop (op_t *restrict dst, const op_t *restrict src)//限制*dst的内容只能通过该指针访问
{
  op_t word;//32x long int
  while (1)
    {
      word = *src++;//将复制的内容放入word
      if (has_zero (word))//有空字节结束
	break;
      *dst++ = word;//将word的内容填入dst
    }

  return write_byte_from_word (dst, word);
}

static __always_inline char *
stpcpy_unaligned_loop (op_t *restrict dst, const op_t *restrict src,
		       uintptr_t ofs)
{
  op_t w2a = *src++;
  uintptr_t sh_1 = ofs * CHAR_BIT;//char_bit 一字节8位，乘以src对齐所需要的字节数
  uintptr_t sh_2 = OPSIZ * CHAR_BIT - sh_1;//系统字节数，

  op_t w2 = MERGE (w2a, sh_1, (op_t)-1, sh_2);
  if (!has_zero (w2))
    {
      op_t w2b;

      /* Unaligned loop.  The invariant is that W2B, which is "ahead" of W1,
	 does not contain end-of-string.  Therefore it is safe (and necessary)
	 to read another word from each while we do not have a difference.  */
      while (1)
	{
	  w2b = *src++;
	  w2 = MERGE (w2a, sh_1, w2b, sh_2);
	  /* Check if there is zero on w2a.  */
	  if (has_zero (w2))
	    goto out;
	  *dst++ = w2;
	  if (has_zero (w2b))
	    break;
	  w2a = w2b;
	}

      /* Align the final partial of P2.  */
      w2 = MERGE (w2b, sh_1, 0, sh_2);
    }

out:
  return write_byte_from_word (dst, w2);
}


/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
char *
STPCPY (char *dest, const char *src)
{
  /* Copy just a few bytes to make DEST aligned.  */
  size_t len = (-(uintptr_t) dest) % OPSIZ;//向后对齐地址的距离
  for (; len != 0; len--, ++dest)
    {
      char c = *src++;
      *dest = c;
      if (c == '\0')//src到末尾
	return dest;
    }

  /* DEST is now aligned to op_t, SRC may or may not be.  */
  uintptr_t ofs = (uintptr_t) src % OPSIZ;//向前对齐地址差距
  return ofs == 0 ? stpcpy_aligned_loop ((op_t*) dest, (const op_t *) src)
		  : stpcpy_unaligned_loop ((op_t*) dest,
					   (const op_t *) (src - ofs) , ofs);
}
weak_alias (__stpcpy, stpcpy)
libc_hidden_def (__stpcpy)
libc_hidden_builtin_def (stpcpy)
