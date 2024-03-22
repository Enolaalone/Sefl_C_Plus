#include <string.h>

void *
memchr(const void *s, int c, size_t n)
{
    if (n != 0) {
        const unsigned char *p = s;

        do {
            if (*p++ == (unsigned char)c)
                return ((void *)(p - 1));
        } while (--n != 0);
    }
    return (NULL);
}