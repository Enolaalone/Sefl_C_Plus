#include <stdio.h>

void *memset_(void *str, int c, size_t n)
{
    char* p=(char*)str;
    for (;n>0;n--)
    {
        *p=(char)c;
        p++;
    }
    return str;
}



int main(){
    char buffer[10];

    // 将 buffer 数组的前5个字节设置为字符 'A'，并添加字符串终止符
    memset_(buffer, 'A', 5);
    buffer[5] = '\0'; // 确保添加字符串终止符
    printf("Buffer after memset: %s\n", buffer);

    // 将 buffer 数组清零，使用 '\0' 替代 0
    memset_(buffer, '\0', sizeof(buffer)); // 使用'\0'确保一致性及可读性
    printf("Buffer after memset: %s\n", buffer);

    return 0;


}