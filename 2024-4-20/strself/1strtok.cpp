#include <cstdio>
#include <cstring>

char *strtok(char *str, const char *delim){
    static char**olds,*begin,*end;

    if(!delim)return NULL;
    if(!str){
        str=*olds;
    }

    if(*str=='\0'){
        *olds=str;
        return NULL;
    }
    str+=strspn(str,delim);
    if(*begin=='\0'){
        *olds=str;
        return NULL;
    }
    end=str+strcspn(str,delim);
    if (*end='\0')
    {
        *olds=str;
        return NULL;
    }
    
    *end='\0';
    *olds=end+1;
    return str;

}
