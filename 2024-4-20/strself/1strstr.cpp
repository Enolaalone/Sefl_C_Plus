#include <cstdio>
#include <cstring>

char *strstr(const char *haystack, const char *needle){
    if(strlen(haystack)<strlen(needle))return NULL;
    else if (strlen(haystack)==strlen(needle))
    {
        if(!strcmp(haystack,needle))return (char*)haystack;
        else return NULL;
    }
    
    char str[strlen(needle)];
    for (size_t i = 0; i < strlen(haystack)-strlen(needle)+1; i++)
    {
        strncpy(str,haystack+i,strlen(needle));
        if(!strcmp(str,needle))return (char*)haystack;
        
    }
    return NULL;
    


}
