#include <stdio.h>
#include <string.h>

int memcmp_0(const void *str1, const void *str2, size_t n){
    char*p1=(char*)str1;
    char*p2=(char*)str2;
    for (; ; p1++,p2++) {
        if(*p1=='\0'&& *p2!='\0') return -1;
        else if(*p1!='\0'&& *p2=='\0') return 1;
        else if(*p1=='\0'&& *p2=='\0') return 0;

        else if((*p1)>(*p2))return 1;
        else if((*p1)<(*p2))return -1;

    }


}



int main ()
{
    char str1[15];
    char str2[15];
    int ret;

    memcpy(str1, "abcdef", 6);
    memcpy(str2, "ABCDEF", 6);

    ret = memcmp_0(str1, str2, 5);

    if(ret > 0)
    {
        printf("str2 小于 str1");
    }
    else if(ret < 0)
    {
        printf("str1 小于 str2");
    }
    else
    {
        printf("str1 等于 str2");
    }

    return(0);
}