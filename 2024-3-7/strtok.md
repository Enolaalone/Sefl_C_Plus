### strtok()

#### 定义：

C 库函数 **char \*strtok(char \*str, const char \*delim)** 分解字符串 **str** 为一组字符串，**delim** 为分隔符

#### 参数：

- **str** -- 要被分解成一组小字符串的字符串。
- **delim** -- 包含分隔符的 C 字符串。

#### 返回值

该函数返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。

```c
#include <string.h>
#include <stdio.h>
 
int main () {
   char str[80] = "This is - www.runoob.com - website";
   const char s[2] = "-";
   char *token;
   
   /* 获取第一个子字符串 */
   token = strtok(str, s);
   
   /* 继续获取其他的子字符串 */
   while( token != NULL ) {
      printf( "%s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}
```

char* token获取分割的字符串;

不再追加str，token = strtok(NULL, s);返回其他字符串

```c
   while( token != NULL ) {
      printf( "%s\n", token );
    
      token = strtok(NULL, s);
   }
```
