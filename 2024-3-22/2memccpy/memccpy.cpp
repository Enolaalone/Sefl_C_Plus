/***
*memccpy.c - copy bytes until a character is found
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _memccpy() - copies bytes until a specifed character
*       is found, or a maximum number of characters have been copied.
*
*******************************************************************************/

#include <string.h>

/***
*char *_memccpy(dest, src, c, count) - copy bytes until character found
*
*Purpose:
*       Copies bytes from src to dest until count bytes have been
*       copied, or up to and including the character c, whichever
*       comes first.
*
*Entry:
*       void *dest - pointer to memory to receive copy
*       void *src  - source of bytes
*       int  c     - character to stop copy at
*       size_t count - max number of bytes to copy
*
*Exit:
*       returns pointer to byte immediately after c in dest
*       returns NULL if c was never found
*
*Exceptions:
*
*******************************************************************************/

void * __cdecl _memccpy (//
        void * dest,//目的指针
        const void * src,//复制指针
        int c,//字符
        size_t count//复制字节数
        )
{
        while ( count && (*((char *)(dest = (char *)dest + 1) - 1) =
        *((char *)(src = (char *)src + 1) - 1)) != (char)c )//字节数大于零  && 目的指针 和 复制指针 同时指向下一地址，再比较上一地址
                count--;//说明：返回指向字符ch后的第一个字符的指针，如果src前n个字节中不存在ch则返回NULL。

        return(count ? dest : NULL);
}
