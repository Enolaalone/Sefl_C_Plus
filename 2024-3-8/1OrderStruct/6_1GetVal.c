#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//指针数组长度
#define OVERFLOW -2//指针数组长度
#define LIST_SIZE 100// int* next长度
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
void print(bool *r);
//------------------------------------------------------------------------------------
int main() {//主函数
    char E[4]="\0";
    int num,l_num;
    //初始化-------------------------------
    List** ps=(List**) malloc(ListLength*sizeof (List*));//链表数组
    if(!ps)exit(OVERFLOW);//未创建成功
    for (int i = 0; i < ListLength; ++i) {//初始化链表数组
        ps[i]=(List*) malloc(sizeof (List));
        if(!ps[i])exit(OVERFLOW);
        ps[i]->next=NULL;
        ps[i]->val=0;
        ps[i]->list_size=0;
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
                        printf("线性表创建成功！\n");
                    }
                    else printf("线性表已经创建！\n");
                }
                else if(num==2){
                    printf("%d\n",num);
                    if(ps[l_num]->next){
                        if(DestroyList(ps[l_num]))
                        printf("销毁表成功！\n");
                        else exit(-1);
                    }
                    else printf("线性表已经销毁！\n");
                }
                else if(num==3){
                    printf("%d\n",num);
                    if(!ClearList(ps[l_num])) break;
                    else printf("线性表已清除！\n");
                }
                else if(num==4){
                    printf("%d\n",num);
                    if(EmptyList(ps[l_num])) printf("线性表是空的！\n");
                    else printf("线性表非空！\n");
                }
                else if(num==5){//---------5
                    printf("%d\n",num);
                    printf("表长为%d!\n", ListLong(ps[l_num]));
                }
                else if(num==6){//---------6
                    printf("%d\n",num);
                    int*e,i;
                    printf("获取元素的位置：\n");
                    scanf("%d",&i);
                    if(GetVal(ps[l_num],i,e)){
                        printf("%d号元素为%d\n",i,*e);
                    } else printf("元素不存在!\n");
                }


            }

        }

    }

    free(ps);
    return 0;
}

bool InitList(List* head){//创建链表
    head->next=(int*) malloc(LIST_SIZE*sizeof (int ));
    if(!head->next){//未创建成功
        exit(OVERFLOW);
    }
    head->val=0;
    head->list_size=LIST_SIZE;//线性表长度
    return true;
}
bool DestroyList(List*head){
    if(head->next){
        free(head->next);//释放空间
        head->next=NULL;//清空数组
        head->val=0;//长度0
        head->list_size=0;//大小0
        return true;
    } else return false;

}//销毁列表

bool ClearList(List*head){
    if(head->next){
        head->val=0;//使用长度为0
        return true;
    }else{
        printf("链表不存在！\n");
        return false;
    }

};//清空列表
bool EmptyList(List*head){//-------------4
    if(head->val==0)return true;
    else return false;
};//测定表是否为空
int ListLong(List*head){
    return head->val;
}//测定表长
bool GetVal(List* head,int i,int *e){
    if(head->val==0 | i<1 |i>head->val) return false;
    *e=head->next[i-1];//访问next数组中i号元素
    return true;
};//返回表元素
void print(bool *r){
    if(!*r){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf("1.InisList\t         \n");
        printf("2.DestroyList\t         \n");
        printf("3.ClearList\t         \n");
        printf("4.EmptyList\t         \n");//----------------------------------4
        printf("5.ListLong\t         \n");//----------------------------------5
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("请选择你的操作[1-14]:\n");
    }
    *r=true;//打印一次
}