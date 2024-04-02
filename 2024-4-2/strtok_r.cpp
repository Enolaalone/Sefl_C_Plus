/* Reentrant string tokenizer.  Generic version.
   Copyright (C) 1991-2024 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <string.h>

#ifndef _LIBC
/* Get specification.  */
# include "strtok_r.h"
# define __strtok_r strtok_r
#endif

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/
char *
__strtok_r (char *s, const char *delim, char **save_ptr)//分割字符串
{
  char *end;

  if (s == NULL)//如果 s 是 NULL，函数会从 save_ptr 指向的位置开始处理，这允许连续分割同一个字符串。
    s = *save_ptr;

  if (*s == '\0')//如果 s 指向的字符串的第一个字符就是结束符（\0），或者通过跳过所有的分隔符后，指针指向的字符是结束符，说明没有更多的子串可以返回，函数返回 NULL。
    {
      *save_ptr = s;
      return NULL;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);//检索s字符串中第一个不在delim中出现的位置，或者结束位置，作为开头
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

  /* Find the end of the token.  */
  end = s + strcspn (s, delim);//检索s字符串中delim中的字符第一次出现的位置，或者结束位置，作为结尾
  if (*end == '\0')
    {
      *save_ptr = end;//保存范围==访问的位置；
      return s;//返回分割的 字符串
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;//save_ptr保存下次分割的起点，最后一定是直到末尾\0
  return s;
}
#ifdef weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#endif
