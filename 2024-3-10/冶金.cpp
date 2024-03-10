#include <stdio.h>
#include<stdlib.h>

void Compare(int o,int v,int r[]){
    int min=0,max=o/v,bg=o/v;
    while (o-v*bg<bg)
    {
        bg--;
    }min=bg+1;
    
    r[0]=min;r[1]=max;

}
int main(){
    int r[2],n,n1,n2,ls[2]={INT_MAX,0};
    scanf("%d",&n);
    while (n!=0)
    {
        scanf("%d %d",&n1,&n2);
        Compare(n1,n2,r);
        if(r[0]<ls[0])ls[0]=r[0];
        if(r[1]>ls[1])ls[1]=r[1];
        n--;
    }
    

    for (int i = 0; i < 2; i++)
    {
        printf("%d\n",ls[i]);
    }
    
}