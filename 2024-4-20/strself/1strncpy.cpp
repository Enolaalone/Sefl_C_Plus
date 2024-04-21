#include <cstdio>
#include <cstring>

char *strncpy(char *dest, const char *src, size_t n)
{
    int len=(n>strlen(src))?strlen(src):n;
    char*dt=dest+strlen(dest);
    for (size_t i = 0; i < len; i++,dt++)
    {
        *dt=src[i];
    }
    *dt='\0';
    return dest;
    
}