
// ���ַ������Ƶ����� dest ��
#include <stdio.h>
#include <string.h>
//C �⺯�� void *memcpy(void *str1, const void *str2, size_t n) �Ӵ洢�� str2 ���� n ���ֽڵ��洢�� str1
void *memcpy_0(void *str1, const void *str2, size_t n){
    for (char* p1 = (char*)str1,*p2 = (char*)str2; (*p2)!='\0' && n>0 ;p1++,p2++,n--) {
        *p1=*p2;
    }
    return str1;


}
//int main ()
//{
//    const char src[50] = "http://www.runoob.com";
//    char dest[50];
////    printf("%d", strlen(src));
//    memcpy_0(dest, src, strlen(src)+1);
//    printf("dest = %s\n", dest);
//
//    return(0);
//}

//int main()
//
//{
//    char *s="http://www.runoob.com";
//    char d[20];
//    memcpy_0(d, s+11, 6);// �ӵ� 11 ���ַ�(r)��ʼ���ƣ��������� 6 ���ַ�(runoob)
//    // ���� memcpy(d, s+11*sizeof(char), 6*sizeof(char));
//    d[6]='\0';
//    printf("%s", d);
//    return 0;
//}

#include<stdio.h>
#include<string.h>

int main(void)
{
    char src[] = "***";
    char dest[] = "abcdefg";
    printf("ʹ�� memcpy ǰ: %s\n", dest);
    memcpy_0(dest, src, strlen(src));
    printf("ʹ�� memcpy ��: %s\n", dest);
    return 0;
}