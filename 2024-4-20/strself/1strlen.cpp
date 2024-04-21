#include <cstdio>
#include <cstring>

size_t strlen(const char *str){
    size_t i=0;
    while (*str!='\0')
    {
        i++;    
        str++;
    }
    return i;
    
}
