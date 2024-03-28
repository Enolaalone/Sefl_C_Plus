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
bool ListDelete(List* head,int i,int *e);//删除i个元素--11
bool ListRun(List* head);//遍历链表--12
bool Write(List *head,char* name);//写入文件--13
bool Read(List *head,char* name);//读入文件--14
int main() {
    char E[5],name[20];
    int l_num,num,length,locate;
    List *M[100];
    for (int i = 0; i < LIST_SIZE; ++i) {
        M[i]=NULL;
    }
    while (1){
        printf("输入需要操作的表(1,99),按0退出！\n");
        gets(E);
        l_num= atoi(E);
        if(l_num==0)break;
        else if(l_num<0||l_num>99)printf("无此链表请重输入！\n");
        while (1){
            pr=false;
            print(&pr);
            gets(E);
            num= atoi(E);
            if(num==0)break;
            else if(num==1){
                if(!M[l_num]){
                    if(InitList(&M[l_num])){
                        printf("链表创建成功！\n");
                    } else printf("链表创建失败！\n");
                } else{
                    printf("链表已经存在！\n");
                }
            }
            else if(num==2){
                if(M[l_num]){
                    if(DestroyList(&M[l_num])){
                        printf("链表销毁成功！\n");
                    } else printf("链表销毁失败！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==3){
                if(M[l_num]){
                    if(ClearList(M[l_num])){
                        printf("链表清除成功！\n");
                    } else printf("链表清除失败！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==4){
                if(M[l_num]){
                    if(ListEmpty(M[l_num])){
                        printf("链表为空！\n");
                    } else printf("链表不为空！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==5){
                if(M[l_num]){
                    length= ListLong(M[l_num]);
                    if(length){
                        printf("链表长度为%d！\n",length);
                    } else printf("链表为空！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==6){
                if(M[l_num]){
                    printf("需要获取元素的位置!\n");
                    scanf("%d",&locate);
                    int *e=(int*) malloc(sizeof (int));
                    if(GetVal(M[l_num],locate-1,e)){
                        printf("链表第%d元素为%d！\n",locate,*e);
                    } else printf("链表为空！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }



            else if(num==7){
                if(M[l_num]){
                    printf("需要获取的元素!\n");
                    int *e=(int*) malloc(sizeof (int));
                    scanf("%d",e);
                    locate=LocalNum(M[l_num],*e)+1;
                    if(locate){
                        printf("链表第%d元素的位置为%d！\n",*e,locate);
                    } else printf("未找到指定元素！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }


            else if(num==8){
                if(M[l_num]){
                    int *e=(int*) malloc(sizeof (int));
                    printf("需要获取前驱元素的元素位置!\n");
                    scanf("%d",&locate);
                    if(PreNum(M[l_num],locate-1,e)){
                        printf("链表第%d号元素的前驱元素为%d！\n",locate,*e);
                    } else printf("未找到指定元素！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }


            else if(num==9){
                if(M[l_num]){
                    int *e=(int*) malloc(sizeof (int));
                    printf("需要获取后驱元素的元素位置!\n");
                    scanf("%d",&locate);
                    if(LaterNum(M[l_num],locate-1,e)){
                        printf("链表第%d号元素的后驱元素为%d！\n",locate,*e);
                    } else printf("未找到指定元素！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }


            else if(num==10){
                if(M[l_num]){
                    printf("需要插入元素及其位置!\n");
                    int *e=(int*) malloc(sizeof (int));
                    scanf("%d %d",e,&locate);

                    if(ListInsert(M[l_num],locate-1,*e)){
                        printf("元素插入成功！\n");
                    } else printf("元素插入失败！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }


            else if(num==11){
                if(M[l_num]){
                    printf("需要删除元素的位置!\n");
                    int *e=(int*) malloc(sizeof (int));
                    scanf("%d",&locate);

                    if(ListDelete(M[l_num],locate-1,e)){
                        printf("删除的元素为%d！\n",*e);
                    } else printf("元素删除失败！\n");
                    free(e);
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==12){
                if(M[l_num]){
                    if(ListRun(M[l_num])){
                        printf("链表遍历成功！\n");
                    } else printf("链表为空！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }
            else if(num==13){
                if(M[l_num]){
                    if(Write(M[l_num],name)){
                        printf("链表写入成功！\n");
                    } else printf("链表写入失败！\n");
                } else{
                    printf("链表不存在！\n");
                }
            }

            else if(num==14){
                if(M[l_num]) {
                    if (Read(M[l_num], name)) {
                        printf("链表读入成功！\n");
                    }
                }
                else printf("链表不存在！\n");

            } else printf("错误重新输入！\n");

        }
    }

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

bool ListDelete(List* head,int i,int *e){
    List *p=head->next,*q=head;
    if(!p||i<0||i>head->val-1) return false;

    for (int j = 0; j < i; ++j) {
        q=p;
        p=p->next;
    }
    p=p->next;
    *e=q->next->val;
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