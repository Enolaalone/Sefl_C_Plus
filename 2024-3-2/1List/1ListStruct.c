#include <stdio.h>
//Hash数据结构
typedef struct aList{//链
  int num;//数组位置
  struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//序号
    char name[25];//项目名称
    L *next;//链
}AL,*ALP;



int main() {
    return 0;
}