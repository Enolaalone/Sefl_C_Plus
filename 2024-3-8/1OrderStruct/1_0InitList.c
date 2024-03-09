#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//指针数组长度
#define OVERFLOW -2//指针数组长度
bool pr=false;
typedef struct List{//链表结构
    struct List* next;
    int val;
}List;

bool InitList(List* head);//建立链表
void print(bool *pr);
//------------------------------------------------------------------------------------
int main() {//主函数
    char E[4]="\0";
    int num,l_num;

    List** ps=(List**) malloc(ListLength*sizeof (List*));//链表数组
    if(!ps)exit(OVERFLOW);//未创建成功
    for (int i = 0; i < ListLength; ++i) {
        ps[i]=(List*) malloc(sizeof (List));
        if(!ps[i])exit(OVERFLOW);
        ps[i]->next=NULL;
        ps[i]->val=0;
    }

    while(1){
        printf("选择对以下哪个链表进行操作（1-99），按0退出！:\n");
        gets(E);
        l_num= atoi(E);
        if(l_num==0)break;
        else {
            while(1){
                print(&pr);
                gets(E);
                num= atoi(E);
                if(num==0){
                    pr=false;
                    break;}
                else if(num==1){//建立链表
                    printf("%d\n",num);
                    if(!ps[l_num]->next){
                        InitList(ps[l_num]);
                        printf("线性链表创建成功！\n");
                    }
                    else printf("线性链表已经创建！\n");
                }


            }

        }

    }

    free(ps);
    return 0;
}

bool InitList(List* head){//创建链表
    head->next=(List*) malloc(sizeof (List));
    if(!head->next){//未创建成功
        exit(OVERFLOW);
    }
    head->next->next=NULL;
    head->next->val=0;
    return true;
}

void print(bool *pr){
    if(!*pr){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf("1.InisList\n");
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("请选择你的操作[1-14]:\n");
    }
    *pr=true;//打印一次
}