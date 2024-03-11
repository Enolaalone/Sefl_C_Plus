#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//指针数组长度
#define OVERFLOW -2//指针数组长度
#define LIST_SIZE 100// int* next长度
#define Length_LIST_SIZE 10// int* next增加长度
bool pr=false;

typedef struct List{//链表结构
    int val;
    struct List* next;
}List;

void print(bool *r);//菜单
bool InitList(List* head);//建立链表
bool DestroyList(List* head);//销毁链表--2

int main() {//主函数
    char E[4] = "\0";
    int num, l_num;
    //初始化-------------------------------
    List **ps = (List **) malloc(ListLength * sizeof(List *));//链表数组
    if (!ps)exit(OVERFLOW);//未创建成功
    for (int i = 0; i < ListLength; ++i) {//初始化链表数组
        ps[i] = (List *) malloc(sizeof(List));
        if (!ps[i])exit(OVERFLOW);
        ps[i]->next = NULL;
        ps[i]->val = 0;

    }
    while (1) {
        printf("选择对以下哪个链表进行操作（1-99），按0退出！:\n");
        gets(E);
        l_num = atoi(E);
        if (l_num == 0)break;
        else {
            while (1) {
                print(&pr);
                gets(E);
                num = atoi(E);
                if (num == 0) {
                    pr = false;
                    break;
                } else if (num == 1) {
                    if (InitList(ps[l_num]))
                        printf("链表创建成功!\n");
                    else
                        printf("链表已经存在!\n");
                }
                else if(num==2){
                    if (DestroyList(ps[l_num]))
                        printf("链表销毁成功!\n");
                    else
                        printf("链表不存在!\n");
                }

            }
        }

    }
    free(ps);
    return 0;
}
void print(bool *r){
    if(!*r){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf("1.InisList\t8.PreNum\n");
        printf("2.DestroyList\t9.LaterNum\n");
        printf("3.ClearList\t10.AddList\n");
        printf("4.EmptyList\t11.DeleteList\n");//----------------------------------4
        printf("5.ListLong\t12.RunList\n");//----------------------------------5
        printf("6.GetVal\t13.Write\n");//----------------------------------6
        printf("7.LocalNum\t14.Read\n");//----------------------------------7
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("请选择你的操作[1-14]:\n");
    }
    *r=true;//打印一次
}


bool InitList(List* head){
    if(head->next)return false;
    head->next=(List*) malloc(sizeof(List));
    if(!head->next) exit(OVERFLOW);
    head->next->val=0;
    head->next->next=NULL;
    return true;
}//创建链表----1

bool DestroyList(List* head){
    if(!head->next)return false;
    head->next=NULL;
    head->val=0;
    return true;
}//销毁链表--2