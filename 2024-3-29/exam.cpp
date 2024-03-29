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
  long int dstp=(long int)dstpp;
  if (len>8)
  {
    size_t xlen;
    op_t cccc;

    cccc=(unsigned char)c;
    cccc|=cccc<<8;
    cccc|=cccc<<16;

    if (OPSIZ>4)
    {
      cccc|=(cccc<<16)<<16;
    }

    while (dstp%(OPSIZ)!=0)
    {
      ((byte*)dstp)[0]=c;
      dstp+=1;
      len-=1;
    }

    xlen=len/(OPSIZ*8);
    while (xlen>0)
    {
      ((op_t*)dstp)[0]=cccc;
      ((op_t*)dstp)[1]=cccc;
      ((op_t*)dstp)[2]=cccc;
      ((op_t*)dstp)[3]=cccc;
      ((op_t*)dstp)[4]=cccc;
      ((op_t*)dstp)[5]=cccc;
      ((op_t*)dstp)[6]=cccc;
      ((op_t*)dstp)[7]=cccc;

      dstp+=OPSIZ*8;
      xlen-=1;
    }
    len%=OPSIZ*8;

    xlen=len/OPSIZ;
    while (xlen>0)
    {
      ((op_t*)dstp)[0]=cccc;
      dstp+=OPSIZ;
      xlen-=1;
    }
    len%=OPSIZ;
  }

  while (len>0)
  {
    ((byte*)dstp)[0]=c;
    dstp+=1;
    len-=1;
  }
  return dstpp;
  

}
libc_hidden_builtin_def (MEMSET)
