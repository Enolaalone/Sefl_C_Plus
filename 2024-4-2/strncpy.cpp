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

#undef strncpy

#ifndef STRNCPY
 #define STRNCPY strncpy
#endif

char *
STRNCPY (char *s1, const char *s2, size_t n)//复制前n个字符
{
  size_t size = __strnlen (s2, n);
  if (size != n)//说明超出了字符串的范围
    memset (s1 + size, '\0', n - size);//将超出部分设置为\0
  return memcpy (s1, s2, size);//复制
}
libc_hidden_builtin_def (strncpy)
