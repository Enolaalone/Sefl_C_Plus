#include <cstdio>
#include <cstring>

char *strchr(const char *str, int c){
    for (size_t i = 0; i < strlen(str); i++)
    {
        if(str[i]==(char)c)return (char*)(str+i);
    }

    return NULL;
}
