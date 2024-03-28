#include <stdio.h>
#include <string.h>

char *strncat_(char *dest, const char *src, size_t n)
{
    char*p=dest,*q=(char*)src;
    while (*p!='\0')
    {
        p++;
    }
    for (;n>0 && *q!='\0';n--,q++,p++)
    {
        *p=*q;
    }
    *p='\0';
    
    return dest;
}




int main ()
{
  char src[50], dest[50];

   strcpy(src,  "This is source");
   strcpy(dest, "This is destination");

   strncat_(dest, src, 10);

   printf("最终的目标字符串： |%s|", dest);
   
   return(0);
}
