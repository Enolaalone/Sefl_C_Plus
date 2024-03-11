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

int main() {//主函数
    char E[4] = "\0";
    int num, l_num;
    //初始化-------------------------------
    List *ps[ListLength];//链表数组
    for (int i = 0; i < ListLength; ++i) {
        ps[i]=NULL;
    }

    while (1) {
        printf("选择对以下哪个链表进行操作（1-99），按0退出！:\n");
        gets(E);
        l_num = atoi(E);
        if (l_num == 0)break;
        else if(l_num<=99 && l_num>=0) {
            while (1) {
                print(&pr);
                gets(E);
                num = atoi(E);
                if (num == 0) {
                    pr = false;
                    break;
                } else if (num == 1) {
                    if (InitList(&ps[l_num]))
                        printf("链表创建成功!\n");
                    else
                        printf("链表已经存在!\n");
                }
                else if(num==2){
                    if (DestroyList(&ps[l_num]))
                        printf("链表销毁成功!\n");
                    else
                        printf("链表不存在!\n");
                }
                else if(num==3){
                    if (ClearList(ps[l_num]))
                        printf("链表清空成功!\n");
                    else
                        printf("链表不存在!\n");
                }
                else if(num==4){
                    if(ps[l_num]){
                        if (!ListEmpty(ps[l_num]))
                            printf("链表不为空!\n");
                        else
                            printf("链表空!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==5){
                    if(ps[l_num]){
                        int length= ListLong(ps[l_num]);
                        if (length)
                            printf("链表长度为%d!\n",length);
                        else
                            printf("链表空!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==6){
                    if(ps[l_num]){
                        int i;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("输入获取第几个元素的值:\n");
                        scanf("%d",&i);

                        if (GetVal(ps[l_num],i,e))
                            printf("第%d个元素的值为%d!\n",i,*e);
                        else
                            printf("获取元素失败!\n");
                        free(e);
                    } else printf("链表不存在!\n");
                }

                else if(num==7){
                    if(ps[l_num]){
                        int e,i;
                        printf("输入想要查询的元素:\n");
                        scanf("%d",&e);
                        i= LocalNum(ps[l_num],e);
                        if (i)
                            printf("元素%d的位置在表中的位置在%d!\n",e,i);
                        else
                            printf("不存在该元素!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==8){
                    if(ps[l_num]){
                        int k;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("输入获取某元素的前驱元素:\n");
                        scanf("%d",&k);

                        if (PreNum(ps[l_num],k,e))
                            printf("第%d元素的前驱元素为%d!\n",k,*e);
                        else
                            printf("获取前驱元素失败!\n");
                        free(e);
                    } else printf("链表不存在!\n");
                }

                else if(num==9){
                    if(ps[l_num]){
                        int k;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("输入获取某元素的后驱元素:\n");
                        scanf("%d",&k);

                        if (LaterNum(ps[l_num],k,e))
                            printf("第%d元素的后取元素为%d!\n",k,*e);
                        else
                            printf("获取后驱元素失败!\n");
                        free(e);
                    } else printf("链表不存在!\n");
                }

                else if(num==10){
                    if(ps[l_num]){
                        int i,k;
                        printf("输入在第几个元素前插入某元素:\n");
                        scanf("%d %d",&i,&k);

                        if (ListInsert(ps[l_num],i,k))
                            printf("插入成功!\n");
                        else
                            printf("插入元素失败!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==11){
                    if(ps[l_num]){
                        int i,k;
                        printf("输入删除第几个元素:\n");
                        scanf("%d",&i);

                        if (ListDelete(ps[l_num],i))
                            printf("删除成功!\n");
                        else
                            printf("删除失败!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==12){
                    if(ps[l_num]){
                        if (ListRun(ps[l_num]))
                            printf("遍历成功!\n");
                        else
                            printf("遍历失败!\n");
                    } else printf("链表不存在!\n");
                }

                else if(num==13){
                    if(ps[l_num]){
                        char name[30];
                        printf("输入建立的文件名称\n");
                        scanf("%s",name);
                        if (Write(ps[l_num],name))
                            printf("文件创建成功!\n");
                        else
                            printf("创建失败!\n");
                    } else printf("链表不存在!\n");
                }

            }
        } else printf("不存在该线性链表!\n");

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
    (*head)=(List*) malloc(sizeof(List));
    if(!*head) exit(OVERFLOW);
    (*head)->val=0;//初始化
    (*head)->next=NULL;
    return true;
}//创建链表----1

bool DestroyList(List** head){
    List *p,*q=*head;
    if(!*head)return false;
    for (; q !=NULL ; q=q->next) {
        free(p);
        p=q;
    }
    q=NULL;
    *head=NULL;
    return true;
}//销毁链表--2

bool ClearList(List* head){
    List *p,*q;
    if(!head)return false;
    for (q=head->next; q !=NULL ; q=q->next) {
        free(p);
        p=q;
    }
    q=NULL;
    head->next=NULL;
    head->val=0;
    return true;
}//清空链表--3

bool ListEmpty(List* head){
    if(head->next)return false;
    else return true;
}//检测链表是否为空---4

int ListLong(List* head){
    int i=0;
    for (List *p=head->next; p !=NULL ;p=p->next) {
        i++;
    }
    return i;
}//检测链表长度---5

bool GetVal(List* head,int i,int* e){
    List *p=head->next;
    if(i<1||i>head->val) return false;
    for (int j = 0; j < i; ++j) {
        p=p->next;
    }
    *e=p->val;
    return true;
}//返回第i个元素的值--6

int LocalNum(List* head,int e){
    int i = 1;
    List *p=head->next;
    for (; p!=NULL ; ++i) {
        if(p->val!=e)p=p->next;
        else return i;
    }
    return 0;

}//返回和元素e相等的值--7

bool PreNum(List* head,int k,int* e){
    List *p=head->next,*q;
    int num= LocalNum(head,k);//确定位置，如果没有num=0
    if(num && p!=NULL){
        for (int i = 1; i!=num ; ++i) {
            if(i==1&&p->val) return false;//一号元素没有前驱
            else{
                q=p;//保留前节点
                p=p->next;
            }
        }
        *e=q->val;
        return true;
    }
    else return false;
}//--8返回q元素的后驱--8

bool LaterNum(List* head,int k,int* e){
    List *p=head->next;
    int num= LocalNum(head,k);//确定位置，如果没有num=0
    if(num && p!=NULL){
        for (int i = 1; i!=num ; ++i) {
            p=p->next;
        }
        if(p->next!=NULL){
            *e=p->next->val;
            return true;
        } else return false;
    }
    else return false;
}//返回q元素的后驱--9

bool ListInsert(List* head,int i,int k){
    List *p=head->next,*q;
    if(p!=NULL && i>1 && i<=head->val){
        for (int j=1;j!=i;++j) {
            q=p;//保留前节点
            p=p->next;
        }
        q->next=(List*) malloc(sizeof(List));
        q=q->next;
        q->val=k;
        q->next=p;
        head->val++;
        return true;
    }
    else return false;
}//i元素前插入元素k--10

bool ListDelete(List* head,int i){
    List *p=head->next,*q=head;
    if(p!=NULL && i>1 && i<=head->val){
        for (int j=1;j!=i;++j) {
            q=p;//保留前节点
            p=p->next;
        }
        List* f=p;
        p=p->next;
        q->next=p;
        free(f);
        head->val--;
        return true;
    }
    else return false;
}//删除i个元素--11

bool ListRun(List* head){
    List *p=head->next;
    if(p!=NULL){
        printf("------all elements------\n");
        for (; p!=NULL ;p=p->next ) {
            printf("%d\n",p->val);
        }
        printf("-----------end--------\n");
        return true;
    }else return false;
}//遍历链表--12

bool Write(List *head,char* name){
    List *p= head->next;
    if(!p){
        FILE *pf= fopen(name,"w");
        if(!pf)exit(-1);
        for (;p!=NULL ;p=p->next) {
            fprintf(pf,"%d\n",p->val);
        }
        fclose(pf);
        return true;
    } else return false;
}//写入文件--13