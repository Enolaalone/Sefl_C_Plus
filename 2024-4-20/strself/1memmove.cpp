#include <stdio.h>

 void *memmove0(void *str1, const void *str2, size_t n){
    char *p1=(char*)str1;
    char *p2=(char*)str2;

   if ((int)(p1-p2)<=0)//p1在p2前面
   {
      for (;str2!=nullptr,n>0; n--)
      {
         *p1++=*p2++;
      }
      *p1='\0';
      return str1;
   }else//p1在p2后面
   {
      p1+=n;
      p2+=n;
      p1[1]='\0';//字符串末尾
      
      for (;n>0; n--)
      {
         *p1--=*p2--;
      }
      
      return str1;
   }
   
   


 }

 int main ()
{
   const char dest[] = "oldstring";
   const char src[]  = "newstring";

   printf("Before memmove dest = %s, src = %s\n", dest, src);
   memmove0((void*)dest, src, 9);
   printf("After memmove dest = %s, src = %s\n", dest, src);

   return(0);
}