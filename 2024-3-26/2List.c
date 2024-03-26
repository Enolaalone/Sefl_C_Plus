#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//指针数组长度
#define OVERFLOW -2//指针数组长度
#define ERROR -1
#define LIST_SIZE 100// int* next长度
#define Length_LIST_SIZE 10// int* next增加长度
bool pr=false;

typedef struct List{//链表结构
    int val;
    struct List* next;
}List;

void print(bool *r);//菜单
bool InitList(List** head);//建立链表
bool DestroyList(List** head);//销毁链表--2
bool ClearList(List* head);//清空链表--3
bool ListEmpty(List* head);//检测链表是否为空---4
int ListLong(List* head);//检测链表长度---5
bool GetVal(List* head,int i,int* e);//返回第i个元素的值--6
int LocalNum(List* head,int e);//返回和元素e相等的值--7
bool PreNum(List* head,int k,int* e);//返回q元素的后驱--8
bool LaterNum(List* head,int k,int* e);//返回q元素的后驱--9
bool ListInsert(List* head,int i,int k);//i元素前插入元素k--10
bool ListDelete(List* head,int i);//删除i个元素--11
bool ListRun(List* head);//遍历链表--12
bool Write(List *head,char* name);//写入文件--13
bool Read(List *head,char* name);//读入文件--14
int main() {
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

bool InitList(List** head){
    if(*head)return false;
    (*head)=(List*) malloc( sizeof (List));
    if(!(*head)) exit(OVERFLOW);
    (*head)->val=0;
    (*head)->next=NULL;
    return true;
}//建立链表
bool DestroyList(List** head){
    if(!(*head))return false;
    List *p=(*head)->next,*q=p;
    for ( ;p!=NULL ;) {
        p=p->next;
        free(q);
    }
    free((*head));
    *head=NULL;
    return true;

}//销毁链表--2

bool ClearList(List* head){
    if(!head)return false;
    List *p=(head)->next,*q=p;
    for ( ;p!=NULL ;) {
        p=p->next;
        free(q);
    }
    head->val=0;
    return true;

}//清空链表--3

bool ListEmpty(List* head){
    if(head->next)return false;
    else return true;
}//检测链表是否为空---4

int ListLong(List* head){
    if(!head)return ERROR;
    return head->val;
}//检测链表长度---5

bool GetVal(List* head,int i,int* e){
    List *p=head->next;
    if(!p||i<0||i>head->val-1)return false;
    for (int j = 0; j < i; ++j) {
        p=p->next;
    }
    *e=p->val;
    return true;

}//返回第i个元素的值--6

int LocalNum(List* head,int e){
    int i=0;
    List *p=head->next;
    if(!p)return ERROR;
    for (; p->val!=e && p!=NULL; p=p->next) {
        i++;
    }
    if(!p)return ERROR;
    else return i;

}//返回和元素e相等的值--7

bool PreNum(List* head,int k,int* e){
    List *p=head->next,*q;
    if(!p||k<1||k>head->val-1) return false;

    for (int i = 0; i < k; ++i) {
        q=p;
        p=p->next;
    }
    *e=q->val;
    return true;

}//返回q元素的后驱--8

bool LaterNum(List* head,int k,int* e){
    List *p=head->next;
    if(!p||k<0||k>head->val-2) return false;

    for (int i = 0; i < k; ++i) {
        p=p->next;
    }
    *e=p->next->val;
    return true;
}//返回q元素的后驱--9

bool ListInsert(List* head,int i,int k){
    List *p=head->next,*q=p;
    if(!p||i<0||i>head->val-1) return false;

    for (int j = 0; j < i; ++j) {
        q=p;
        p=p->next;
    }
    q->next=(List*) malloc(sizeof (List));
    if(!q)exit(OVERFLOW);
    q=q->next;
    q->val=k;
    q->next=p;
    head->val++;
    return true;

}//i元素前插入元素k--10

bool ListDelete(List* head,int i){
    List *p=head->next,*q=head;
    if(!p||i<0||i>head->val-1) return false;

    for (int j = 0; j < i; ++j) {
        q=p;
        p=p->next;
    }
    p=p->next;
    free(q->next);
    q->next=p;
    head->val--;
    return true;
}//删除i个元素--11

bool ListRun(List* head){
    int i=0;
    List *p=head->next;
    if(!p)return false;
    for (; p!=NULL; p=p->next) {
        printf("%d\t",p->val);
        if(!(i+1)%10)printf("\n");
    }
    return true;
}//遍历链表--12

bool Write(List *head,char* name){
    printf("输入文件名称!\n");
    gets(name);
    FILE *pf= fopen(name,"w");
    List *p=head->next;
    if(!p)return false;
    for (; p!=NULL ;p=p->next) {
        fprintf(pf,"%d\n",p->val);
    }
    fclose(pf);
    return true;

}//写入文件--13

bool Read(List *head,char* name){
    char word[10];
    printf("输入文件名称!\n");
    gets(name);
    FILE *fp= fopen(name,"r");
    List *p,*q=head;
    p=(List*) malloc(sizeof (List));
    if(!p)exit(OVERFLOW);
    while (fgets(word,sizeof (word),fp)!=NULL){
        q->next=p;
        sscanf(word,"%d",&q->val);
        head->val++;
        q->next=NULL;
        p=(List*) malloc(sizeof (List));
        if(!p)exit(OVERFLOW);
    }
    return true;
}//读入文件--14