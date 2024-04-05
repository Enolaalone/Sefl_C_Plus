/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
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

#include <libc-pointer-arith.h>
#include <string-fzb.h>
#include <string-fzc.h>
#include <string-fzi.h>
#include <string-shift.h>
#include <string.h>

#ifdef STRLEN
# define __strlen STRLEN
#endif

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (const char *str)
{
  /* Align pointer to sizeof op_t.  */
  const uintptr_t s_int = (uintptr_t) str;//转换指针为unsigned int 类型
  const op_t *word_ptr = (const op_t*) PTR_ALIGN_DOWN (str, sizeof (op_t));//str向前对齐

  op_t word = *word_ptr;
  find_t mask = shift_find (find_zero_all (word), s_int);//找到\0出现的位置
  // find_eq_all函数：这个函数的目的是比较两个op_t类型的值——在这个上下文中，一个是从内存中读取的word，另一个是通过repeat_bytes函数构造的repeated_c，其中包含了要搜索的字节c_in在整个op_t类型值中重复的形式。find_eq_all函数将这两个值进行比较，并生成一个新的op_t类型的值，该值的每个位代表对应的字节是否匹配。如果对应的字节相等，则相应的位被设置为1；否则，设置为0

  // shift_find函数：此函数接受find_eq_all的结果，并根据原始指针s（已转换为整数s_int）的对齐情况进行调整。目的是确保只考虑那些实际位于搜索范围内的字节。因为word可能包括了实际搜索起始点之前的字节（如果s没有在op_t的边界上），shift_find通过shift操作来排除这些字节，确保生成的掩码仅反映从s开始的有效比较。
  if (mask != 0)
    return index_first (mask);//返回距离

  do//向后批量处理字符串
    word = *++word_ptr;
  while (! has_zero (word));

  return ((const char *) word_ptr) + index_first_zero (word) - str;//word_ptr的地址减去str，加上\0出现的位置相对于word_ptr的距离，即为长度，不包含\0
}
#ifndef STRLEN
weak_alias (__strlen, strlen)
libc_hidden_builtin_def (strlen)
#endif
