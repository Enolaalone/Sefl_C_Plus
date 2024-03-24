#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//指针数组长度
#define OVERFLOW -2//指针数组长度
#define ERROR -1//指针数组长度
#define LIST_SIZE 100// int* next长度
#define Length_LIST_SIZE 10// int* next增加长度
bool pr=false;

typedef struct List{//链表结构
    int* next;
    int val;
    int list_size;
}List;

bool InitList(List* head);//建立链表
bool DestroyList(List*head);//销毁列表
bool ClearList(List*head);//清空列表
bool EmptyList(List*head);//测定表是否为空
int ListLong(List*head);//测定表长
bool GetVal(List *head,int i,int *e);//返回表元素
int LocalNum(List *head,int q);//查找元素--7
bool PreNum(List *head,int q,int* pre_e);//查找前驱元素--8
bool LaterNum(List *head,int q,int* pre_e);//查找后驱元素--9
bool AddList(List *head,int i,int e);//在i位置插入e--10
bool DeleteList(List *head,int i,int* e);//删除i位置---11
int RunList(List *head);//遍历列表--12
bool Write(List *head);//写入文件--13
bool Read(List *head);//读取文件--14
void print(bool *r);

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

bool InitList(List* head){
    int* p=(int*) malloc(LIST_SIZE*sizeof (List));
    if(!p) return false;
    head->next=p;
    head->list_size=LIST_SIZE;
    head->val=0;
    return true;
}//建立链表

bool DestroyList(List*head){
    free(head->next);
    head->next=NULL;

    head->list_size=0;
    head->val=0;
    return true;
}//销毁列表

bool ClearList(List*head){
    head->val=0;
    return true;
}//清空列表

bool EmptyList(List*head){
    if(head->val)return false;
    else return true;
}//测定表是否为空

int ListLong(List*head){
    return head->val;
}//测定表长

bool GetVal(List *head,int i,int *e){
    if(i+1>head->val)return false;

    *e=head->next[i];
    return true;
}//返回表元素

int LocalNum(List *head,int q){
    for (int i = 0; i < head->val; ++i) {
        if(head->next[i]==q) return i;
    }
    return ERROR;

}//查找元素--7


bool PreNum(List *head,int q,int* pre_e){
    int pos= LocalNum(head,q);
    if(pos==-1||pos==0)return false;

    *pre_e=head->next[pos-1];
    return true;
}//查找前驱元素--8

bool LaterNum(List *head,int q,int* pre_e){
    int pos= LocalNum(head,q);
    if(pos==-1||pos==head->val-1)return false;
    *pre_e=head->next[pos+1];
    return true;

}//查找后驱元素--9

bool AddList(List *head,int i,int e){
    if(i<0||i>head->val-1) return false;
    if(head->val+1>head->list_size){
        int*p=(int*) realloc(head->next,(LIST_SIZE+Length_LIST_SIZE)*sizeof (int));
        if(!p)return OVERFLOW;
        else head->next=p;
        head->list_size+=Length_LIST_SIZE;
    }

    for (int j = head->val; j >i ; --j) {
        head->next[j]=head->next[j-1];
    }

    head->next[i]=e;
    head->val++;
    return true;
}//在i位置插入e--10

bool DeleteList(List *head,int i,int* e){
    if(i<0||i>head->val-1) return false;
    *e=head->next[i];
    for (int j = i; j <head->val-1 ; ++j) {
        head->next[j]=head->next[j+1];
    }
    head->val--;
    return true;
}//删除i位置---11

int RunList(List *head){
    for (int i = 0; i < head->val; ++i) {
        printf("%d\t",head->next[i]);
        if(!(i+1)%10)printf("\n");
    }
    return head->val;

}//遍历列表--12

bool Write(List *head){
    char name[20];
    printf("输入文件名称\n");
    gets(name);
    FILE *pf= fopen(name,"w");
    if(!pf)return OVERFLOW;
    for (int i = 0; i < head->val; ++i) {
        fprintf(pf,"%d\n",head->next[i]);
    }
    fclose(pf);
    return true;
}//写入文件--13

bool Read(List *head){
    head->val=0;
    char name[20],word[20];
    printf("输入文件名称\n");
    gets(name);
    FILE *fp= fopen(name,"r");
    while (fgets(word,sizeof (word),fp)!=NULL){
        if(sscanf(word,"%d",&head->next[head->val++])==1) printf("%d\n",head->val);
        else printf("%s\n",word);
    }

    return true;
}//读取文件--14






