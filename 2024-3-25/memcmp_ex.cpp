/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Torbjorn Granlund (tege@sics.se).

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
# include "config.h"
#endif

#if defined HAVE_STRING_H || defined _LIBC
# include <string.h>
#endif

#undef memcmp

#ifndef MEMCMP
# define MEMCMP memcmp
#endif

#ifdef _LIBC

# include <memcopy.h>
# include <endian.h>

# if __BYTE_ORDER == __BIG_ENDIAN
#  define WORDS_BIGENDIAN
# endif

#else	/* Not in the GNU C library.  */

# include <sys/types.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
# define OPSIZ	(sizeof (op_t))

/* Type to use for unaligned operations.  */
typedef unsigned char byte;//无符号字符

# ifndef WORDS_BIGENDIAN
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
# else
#  define MERGE(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
# endif

#endif	/* In the GNU C library.  */

#ifdef WORDS_BIGENDIAN
# define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#else
# define CMP_LT_OR_GT(a, b) memcmp_bytes ((a), (b))
#endif

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#ifndef WORDS_BIGENDIAN
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */

static int memcmp_bytes (op_t, op_t) __THROW;

// __THROW是在GNU C库（glibc）和其他一些C库中使用的宏，用于标记函数原型以表明这些函数不会抛出异常。这个宏的具体定义可能因库的版本和目标编译环境而异，但通常，它在C语言的上下文中用于改善交叉编译器的兼容性和性能，特别是在与C++混合编程时。


// 在上下文中提及的`op_t`是在GNU C Library (glibc)的`memcmp`实现代码片段中使用的一个类型别名。`op_t`通常定义为一个能够一次性通过单个加载/存储操作处理的最大无符号类型。这种类型的定义允许内存操作（如比较、复制）以最高的效率执行，因为它们可以在每个操作中处理尽可能多的数据。

// 在不同的系统和架构上，`op_t`的具体类型可能会有所不同，以适应该平台上单个操作能够高效处理的最大数据宽度。例如，在32位系统上，`op_t`可能被定义为`unsigned long`，因为这通常是32位系统中可以一次性操作的最大单位。在64位系统上，`op_t`可能被定义为`unsigned long long`或其他64位宽的数据类型，以便利用64位处理器的能力进行更大范围的一次性内存操作。

// 通过使用`op_t`类型，`memcmp`函数和其他内存操作函数可以在不牺牲可移植性的同时，最大化利用硬件的能力，提高处理速度。这是因为`op_t`类型的定义考虑到了目标平台的具体特性，包括CPU的字长和最优内存访问模式。

// 在实际使用中，`op_t`类型的变量通常用于表示可以一次性从内存中加载或存储的数据块。这使得在执行内存比较、复制等操作时，可以最小化所需的CPU周期数，从而提高性能。然而，正如你所指出的，当涉及到逐字节比较内存内容时，需要先获取变量的地址，然后将这些地址转换为字节指针，最后逐个字节地进行比较。
static int
memcmp_bytes (op_t a, op_t b)
{
  long int srcp1 = (long int) &a;
  long int srcp2 = (long int) &b;//将地址转换为（long int）方便加减
//   这行代码是将变量`a`的地址转换为`long int`类型的值，并将这个值赋给变量`srcp1`。这样做有几个目的：

// 1. **指针操作**：通过将指针转换为整数类型，代码可以对地址进行数值操作。这种操作在低级编程中很常见，尤其是在需要精确控制内存访问的场合。

// 2. **移植性和兼容性**：`long int`类型通常被选择用于存储指针转换值，是因为它在大多数平台上都能够保证足够的大小来存放指针值。即便如此，最安全的做法是使用`uintptr_t`类型，它是C99标准中专门为存放转换为无符号整数的指针而定义的。不过，`long int`在许多情况下仍然足够用。

// 3. **逐字节比较**：在上下文中，将指针转换为整数类型允许函数通过逐字节的方式比较两个变量`a`和`b`的内存内容。这是通过迭代增加`srcp1`和`srcp2`（后者同样是转换后的`b`的地址）来实现的，每次迭代比较一对字节，直到发现不匹配的字节或完成所有指定的比较。

// 4. **类型安全和警告**：直接对指针进行算术运算在某些情况下可能会触发编译器警告，因为这可能导致未定义行为。将指针先转换为整型，进行算术操作后再转换回相应的指针类型，是避免这类警告的一种常见做法。不过，这行代码没有将`long int`转回指针类型来访问内存，而是通过将整数类型的地址再次转换为`byte*`类型来访问具体的字节。

// 这种操作属于底层编程技巧，在处理需要直接访问和操作内存地址的场合（如某些类型的比较、复制和加密算法）时尤其有用。然而，这也需要开发者对所用平台的内存模型和数据类型的大小有深入的理解。
  op_t a0, b0;//大小为unsigned char 即一个字节

  do
    {
      a0 = ((byte *) srcp1)[0];//将（long int）转换为unsigned char * 地址，访问该地址
      b0 = ((byte *) srcp2)[0];
//       这行代码执行了几个步骤来访问内存中的特定字节：

// 1. **类型转换**：`srcp1`是一个`long int`类型的变量，它存储了某个变量`a`的地址（已经被转换为整数类型）。这里，`(byte *)`将`srcp1`的值再次转换回指针类型，这次是转换为`byte *`类型的指针。`byte`通常是`unsigned char`的别名，表示单个字节。

// 2. **内存访问**：转换后的指针指向`srcp1`所表示的内存地址。通过`[0]`索引，代码访问这个地址指向的第一个字节。这种方式实际上是按字节访问内存，能够读取存储在该地址的具体字节值。

// 3. **赋值给`a0`**：读取到的字节值被赋给变量`a0`。这个值是从原始内存地址（即变量`a`的地址）开始的第一个字节。

// 在上下文中，这行代码是用于实现`memcmp_bytes`函数的一部分，该函数逐字节比较两个内存区域。此处的操作是获取第一个内存区域（由`a`表示）的当前字节以进行比较。相应地，代码中还会有类似的操作来获取第二个内存区域（由`b`表示）的当前字节，以便进行比较。

// 这种按字节访问和比较的方法是处理不同数据块（特别是在它们可能不完全对齐的情况下）的有效方式，它确保了比较操作能够精确地进行，而不受数据在内存中布局的影响。
      srcp1 += 1;//访问下一地址
      srcp2 += 1;
    }
  while (a0 == b0);
  return a0 - b0;
}
#endif

static int memcmp_common_alignment (long, long, size_t) __THROW;

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
static int
memcmp_common_alignment (long int srcp1, long int srcp2, size_t len)
{
  op_t a0, a1;
  op_t b0, b1;

  switch (len % 4)
    {
    default: /* Avoid warning about uninitialized local variables.  */
    case 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      goto do1;
    case 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      goto do2;
    case 0:
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	return 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      goto do3;
    case 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	goto do0;
      /* Fall through.  */
    }

  do
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      if (a1 != b1)
	return CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      if (a0 != b0)
	return CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      if (a1 != b1)
	return CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      if (a0 != b0)
	return CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  while (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  if (a1 != b1)
    return CMP_LT_OR_GT (a1, b1);
  return 0;
}

static int memcmp_not_common_alignment (long, long, size_t) __THROW;

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
static int
memcmp_not_common_alignment (long int srcp1, long int srcp2, size_t len)
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  int shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  switch (len % 4)
    {
    default: /* Avoid warning about uninitialized local variables.  */
    case 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      goto do1;
    case 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      goto do2;
    case 0:
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	return 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      goto do3;
    case 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	goto do0;
      /* Fall through.  */
    }

  do
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = MERGE(a2, shl, a3, shr);
      if (x != b3)
	return CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = MERGE(a3, shl, a0, shr);
      if (x != b0)
	return CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = MERGE(a0, shl, a1, shr);
      if (x != b1)
	return CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = MERGE(a1, shl, a2, shr);
      if (x != b2)
	return CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  while (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = MERGE(a2, shl, a3, shr);
  if (x != b3)
    return CMP_LT_OR_GT (x, b3);
  return 0;
}

int
MEMCMP (const void *s1, const void *s2, size_t len)
{
  op_t a0;
  op_t b0;
  long int srcp1 = (long int) s1;
  long int srcp2 = (long int) s2;
  op_t res;

  if (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      while (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  if (res != 0)
	    return res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      if (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      else
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      if (res != 0)
	return res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  while (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      if (res != 0)
	return res;
      len -= 1;
    }

  return 0;
}
libc_hidden_builtin_def(memcmp)
#ifdef weak_alias
# undef bcmp
weak_alias (memcmp, bcmp)
#endif

#undef __memcmpeq
strong_alias (memcmp, __memcmpeq)
libc_hidden_def(__memcmpeq)
