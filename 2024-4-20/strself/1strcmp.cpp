#include <cstdio>
#include <cstring>

int strcmp(const char *str1, const char *str2){
    int len=(strlen(str1)>strlen(str2))?strlen(str2):strlen(str1);

    for (size_t i = 0; i < len; i++)
    {
        if(str1[i]>str2[i])return 1;
        else if(str1[i]<str2[i])return -1;
        else if(str1[i]==str2[i]&&i==len-1&&strlen(str1)!=strlen(str2))return (strlen(str1)>strlen(str2))?1:-1;
        else if(str1[i]==str2[i]&&i==len-1&&strlen(str1)!=strlen(str2))return 0;

    }
    


}
