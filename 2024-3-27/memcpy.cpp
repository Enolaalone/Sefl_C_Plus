/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is NOT handled correctly.
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

#include <string.h>
#include <memcopy.h>

#ifndef MEMCPY
# define MEMCPY memcpy
#endif

void *
MEMCPY (void *dstpp, const void *srcpp, size_t len)
{
  unsigned long int dstp = (long int) dstpp;
  unsigned long int srcp = (long int) srcpp;
// 这行代码是将一个指针（`dstpp`）转换为一个无符号长整型（`unsigned long int`）的值，赋值给变量`dstp`。

// 在C语言中，指针是用来存储内存地址的变量。虽然指针本身是一个整数（表示一个地址），但它通常被处理为一个特殊的类型，以便于区分是一个数值还是一个内存地址。在进行某些操作时，特别是涉及位操作或者需要与其他整数值进行比较或计算时，可能会需要将指针转换为整数类型。

// 这里的转换是为了后续的内存复制操作。因为内存地址本质上是一个数值，所以可以通过将指针转换为一个整数类型（如`unsigned long int`），来进行数学运算或位操作。这样的操作可能包括计算对齐、地址偏移等。

// `unsigned long int`类型被选用是因为它通常足够大，可以存储一个内存地址。这样的转换允许代码直接操作地址值，而不是通过指针解引用或其他间接手段。这是底层内存操作中常见的技术，用于提高效率或处理特定的硬件或操作系统约束。

// 简而言之，这行代码的目的是为了将目标内存地址的指针转换为一个可以进行数值运算的整数形式，以便于进行后续的内存复制优化操作。
  /* Copy from the beginning to the end.  */

  /* If there not too few bytes to copy, use word copy.  */
  if (len >= OP_T_THRES)//OP_T_THRES定义为16或8。
//   在这行代码中，`if (len >= OP_T_THRES)`是一个条件判断语句，用于检查是否有足够多的字节需要被复制，以决定使用哪种复制方法。这里，`len`表示要复制的字节长度，而`OP_T_THRES`是一个预定义的阈值（threshold），代表“操作阈值”。

// - **`len`**：这是一个`size_t`类型的变量，指定了需要从源内存地址复制到目标内存地址的字节总数。
// - **`OP_T_THRES`**：这是一个常量或宏，定义了选择不同复制策略的界限。如果`len`大于或等于这个阈值，就意味着有足够多的数据需要被复制，从而使用更高效的复制方法是合理的。这个阈值通常是基于性能优化考量设定的，可能与CPU的缓存行大小、内存页面大小或者是某种操作（如字对齐）的最佳执行条件有关。

// 这个条件判断的背后逻辑是，当需要复制的数据量较大时，采取特定的优化措施（如利用CPU的字对齐特性进行批量复制）会更有效率。如果`len`小于`OP_T_THRES`，则意味着需要复制的数据量较小，使用这些优化措施相比于简单的字节复制可能不会带来太多性能提升，因此可能直接使用字节级的复制即可。

// - 在`len >= OP_T_THRES`为真的情况下，代码会执行更复杂的复制逻辑，可能包括对齐目标地址、使用页复制或字复制等优化手段。
// - 如果这个条件不成立，即`len`小于`OP_T_THRES`，则可能直接使用逐字节复制，因为在处理小块数据时，这种方法简单且足够有效。
    {
      /* Copy just a few bytes to make DSTP aligned.  */
      len -= (-dstp) % OPSIZ;//得出距离dstp最近的对齐地址，len减去这段距离
      BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

      /* Copy whole pages from SRCP to DSTP by virtual address manipulation,
	 as much as possible.  */

      PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);//虚拟页拷贝，实现每次四字节的拷贝，快速

      /* Copy from SRCP to DSTP taking advantage of the known alignment of
	 DSTP.  Number of bytes remaining is put in the third argument,
	 i.e. in LEN.  This number may vary from machine to machine.  */

      WORD_COPY_FWD (dstp, srcp, len, len);

      /* Fall out and copy the tail.  */
    }

  /* There are just a few bytes to copy.  Use byte memory operations.  */
  BYTE_COPY_FWD (dstp, srcp, len);//如果还有字符，就逐字节拷贝，

  return dstpp;
}
libc_hidden_builtin_def (MEMCPY)