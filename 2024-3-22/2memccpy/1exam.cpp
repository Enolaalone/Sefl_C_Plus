#include <stdio.h>
#include <string.h>

void* __cdecl __memccpy(void *desk,const void *src,int c,size_t count){
    while (count && (*((char *)(desk=(char *)desk+1)-1)=*((char *)(src =(char *)src+1)-1))!=(int)c)
        count--;
    return (count?desk: nullptr);

}




int main() {
    return 0;
}