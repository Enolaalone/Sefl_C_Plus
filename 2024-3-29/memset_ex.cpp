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
#include <memcopy.h>

#ifndef MEMSET
# define MEMSET memset
#endif

void *
inhibit_loop_to_libcall
MEMSET (void *dstpp, int c, size_t len)
{
  long int dstp = (long int) dstpp;//地址转换

  if (len >= 8)//替换的字符数大于8
    {
      size_t xlen;//批量操作次数
      op_t cccc;//unsigned int 4字节x32，或者unsigned long int 8字节x64

      cccc = (unsigned char) c;
      cccc |= cccc << 8;//复制到一半
      cccc |= cccc << 16;//复制剩下一半，将char复制为4字节

      //如果是64位系统 8字节
      if (OPSIZ > 4)
    	/* Do the shift in two steps to avoid warning if long has 32 bits.  */
	    cccc |= (cccc << 16) << 16;//将unsigned char复制为unsigned ,long int 8字节,移位计数的范围仅为 0-31

      /* There are at least some bytes to set.
    	 No need to test for LEN == 0 in this alignment loop.  */
      while (dstp % OPSIZ != 0)//地址没有对齐，逐字节复制
      {
      ((byte *) dstp)[0] = c;//
      dstp += 1;//地址向后移动一位
      len -= 1;//需要复制的字符-1
      }

      /* Write 8 `op_t' per iteration until less than 8 `op_t' remain.  */
      xlen = len / (OPSIZ * 8);
      while (xlen > 0)
      {
        //如果op_t为unsigned int 地址每次加4字节 一次复制了32位，一共复制32字节
        ((op_t *) dstp)[0] = cccc;
        ((op_t *) dstp)[1] = cccc;
        ((op_t *) dstp)[2] = cccc;
        ((op_t *) dstp)[3] = cccc;
        ((op_t *) dstp)[4] = cccc;
        ((op_t *) dstp)[5] = cccc;
        ((op_t *) dstp)[6] = cccc;
        ((op_t *) dstp)[7] = cccc;
        dstp += 8 * OPSIZ;//实际地址改变到复制的末尾地址
        xlen -= 1;//while循环的复制次数-1
      }
      len %= OPSIZ * 8;//不够32字节的部分

      /* Write 1 `op_t' per iteration until less than OPSIZ bytes remain.  */
      xlen = len / OPSIZ;//查看4字节的次数
      while (xlen > 0)
      {
        ((op_t *) dstp)[0] = cccc;
        dstp += OPSIZ;//实际地址改变到复制的末尾地址
        xlen -= 1;//while循环的复制次数-1
      }
      len %= OPSIZ;
    }

  /* Write the last few bytes.  */
    while (len > 0)
    {
      ((byte *) dstp)[0] = c;
      dstp += 1;
      len -= 1;
    }

  return dstpp;
}
libc_hidden_builtin_def (MEMSET)
