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
#include <stdint.h>
#include <libc-pointer-arith.h>

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (const char *str, const char *reject)//检索字符串 str 开头连续有几个字符都不含字符串reject中的字符
{
  if (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))//reject中没有字符或者只有一个字符，用strchrnul检索
    return __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  创建查找表：

// 它会创建一个256位的查找表（table），用于标记reject字符串中存在的字符。这个表被初始化为全0，然后遍历reject字符串，将对应字符在表中的位置标记为1。
  unsigned char table[256];
//   内联优化：作者注释中提到，“使用多个小的memset以便在大多数目标上实现内联”。这表明这种分割内存初始化操作的做法可能是为了允许编译器更容易地将memset调用内联到包含它的函数中。内联是一种编译时优化，可以通过消除函数调用的开销来提高程序的运行速度。
  unsigned char *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned char *s = (unsigned char*) reject;
  unsigned char tmp;//reject中目标元素
  do
    p[tmp = *s++] = 1;//将查询的元素标记
  while (tmp);

  s = (unsigned char*) str;
  //查询前四个
  if (p[s[0]]) return 0;
  if (p[s[1]]) return 1;
  if (p[s[2]]) return 2;
  if (p[s[3]]) return 3;

  s = (unsigned char *) PTR_ALIGN_DOWN (s, 4);//s指针向前对齐
// 当unsigned char类型的值被用于运算表达式中，并与unsigned int类型的变量一起使用时，unsigned char类型的值会自动提升（promote）到int或unsigned int类型（具体取决于平台和编译器如何处理整数提升）。在这个过程中，unsigned char类型的值（通常为0到255的范围）会保持其数值不变地扩展到更大的整数类型。
  unsigned int c0, c1, c2, c3;                 
  do
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  while ((c0 | c1 | c2 | c3) == 0);//是否都没有被标记.,或者没有到达末尾

  size_t count = s - (unsigned char *) str;
  return (c0 | c1) != 0 ? count - c0 + 1 : count - c2 + 3;//如果c0 c1有一个为1，根据1出现的位置确定count值大小，如果没有找到返回 str最后一个字符的序号
}
libc_hidden_builtin_def (strcspn)
