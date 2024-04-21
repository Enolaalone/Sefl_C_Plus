#include <stdio.h>
#include <string.h>//Ctr+B

//寻找字符串str 前n 个字符中第一c出现位置
void *memchr_self(const void *str, int c, size_t n){
    char *p=(char*)str;
    char ch=(char)c;
    for (int i = 0; p[i]!='\0'&&i<n; ++i) {
        if (p[i]==ch)
            return &p[i];
    }
    return nullptr;
}


int main ()
{
    const char str[] = "http://www.runoob.com";
    const char ch = '.';
    char *ret;

    ret = (char*)memchr_self(str, ch, strlen(str));

    printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);//|.| 之后的字符串是 - |.runoob.com|

    return(0);
}