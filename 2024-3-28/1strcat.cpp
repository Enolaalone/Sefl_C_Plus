#include <stdio.h>
#include <string.h>

char *strcat_(char *dest, const char *src)

{
    char*p=dest,*q=(char*)src;
    while (*p!='\0')
    {
        p++;
    }
    for (;*q!='\0';q++,p++)
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
 
   strcat_(dest, src);
 
   printf("最终的目标字符串： |%s|", dest);
   
   return(0);
}
