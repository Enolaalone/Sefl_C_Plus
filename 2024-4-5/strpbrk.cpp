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

#include <string.h>

#undef strpbrk

#ifndef STRPBRK
#define STRPBRK strpbrk
#endif

/* Find the first occurrence in S of any character in ACCEPT.  */
char *
STRPBRK (const char *s, const char *accept)//检索字符串 str1 中第一个匹配字符串 str2 中字符的字符
{
  s += strcspn (s, accept);//检索sccept中的字符第一次在s中出现的位置，没有找到返回最后一个字符序号
  return *s ? (char *)s : NULL;//如果没找到则*s='\0'返回NULL
}
libc_hidden_builtin_def (strpbrk)
