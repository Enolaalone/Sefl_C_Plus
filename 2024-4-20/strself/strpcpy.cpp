#include <cstdio>
#include <cstring>

char *stpcpy0(char *dest, const char *src){
    char *dt=dest;
    int len=strlen(dest);
    dest+=len;

    for (size_t i = 0; src[i]!='\0'; i++,dt++)
    {
        *dt=src[i];
    }
    *dt='\0';
    return dest;

}