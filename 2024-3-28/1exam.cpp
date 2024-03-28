/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is handled correctly.
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

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#ifndef	a1
#define	a1	dest	/* First arg is DEST.  */
#define	a1const
#define	a2	src	/* Second arg is SRC.  */
#define	a2const	const
#undef memmove
#endif
#if	!defined(RETURN) || !defined(rettype)
#define	RETURN(s)	return (s)	/* Return DEST.  */
#define	rettype		void *
#endif

#ifndef MEMMOVE
#define MEMMOVE memmove
#endif

rettype
inhibit_loop_to_libcall
MEMMOVE (a1const void *a1, a2const void *a2, size_t len)
{
    unsigned long int dstp=(long int)dest;
    unsigned long int srcp=(long int)src;

if (dstp-srcp>=len)
{
#if MEMCPY_OK_FOR_MEMMOVE
    dest=memcpy(dstp,srcp,len);
#else
{
    if (len>=OP_T_THRES)
    {
        len-=(-dstp)%OPSIZ;
        BYTE_COPT_FWD(dtsp,srcp,(-dstp)%OPSIZ);
        PAGE_COPT_FWD_MAYBE(dtsp,srcp,len,len);
        WORD_COPT_FWD(dtsp,srcp,len,len);
    }
    BYTE_COPT_FWD(dtsp,srcp,len);
}
#endif
}

else
{
    dtsp+=len;
    srcp+=len;
    if (len>=OP_T_THRES)
    {
        len-=(dstp)%OPSIZ;
        BYTE_COPT_BWD(dtsp,srcp,(-dstp)%OPSIZ);
        WORD_COPT_BWD(dtsp,srcp,len,len);
    }
    BYTE_COPT_BWD(dtsp,srcp,len);
}
RETURN(dest);

}

#ifndef memmove
libc_hidden_builtin_def (memmove)
#endif
