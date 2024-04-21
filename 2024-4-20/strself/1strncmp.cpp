#include <cstdio>
#include <cstring>

int strncmp(const char *str1, const char *str2, size_t n)
{
    int len=(strlen(str1)>strlen(str2))?strlen(str2):strlen(str1);
    if(n<len)len=n;
    for (size_t i = 0; i < len; i++)
    {
        if(str1[i]>str2[i])return 1;
        else if(str1[i]<str2[i])return -1;
        else if(str1[i]==str2[i]&&i==len-1&&strlen(str1)!=strlen(str2))return (strlen(str1)>strlen(str2))?1:-1;
        else if(str1[i]==str2[i]&&i==len-1&&strlen(str1)!=strlen(str2))return 0;

    }
    
}
