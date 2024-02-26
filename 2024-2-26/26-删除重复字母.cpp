#include <stdio.h>
int removeDuplicates(int* nums, int numsSize) {
    int p=0;
    for(int i=1;i<numsSize;i++){
        if(nums[i]!=nums[p]){
            p++;
            nums[p]=nums[i];
            }
        }
    numsSize=p+1;
    return numsSize;
}

int main(){
    int num=5;
    int a[5]={1,1,2,2,3};
    int b=removeDuplicates(a,num);
    printf("%d\n",b);
    for (int i = 0; i < b; i++)
    {
        printf("%d,",a[i]);
    }
    return 0;
}
