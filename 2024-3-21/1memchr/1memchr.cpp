#include <stdio.h>
#include <string.h>//Ctr+B

//Ѱ���ַ���str ǰn ���ַ��е�һc����λ��
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

    printf("|%c| ֮����ַ����� - |%s|\n", ch, ret);//|.| ֮����ַ����� - |.runoob.com|

    return(0);
}