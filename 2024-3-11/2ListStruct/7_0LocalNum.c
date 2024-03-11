#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//ָ�����鳤��
#define OVERFLOW -2//ָ�����鳤��
#define LIST_SIZE 100// int* next����
#define Length_LIST_SIZE 10// int* next���ӳ���
bool pr=false;

typedef struct List{//����ṹ
    int val;
    struct List* next;
}List;

void print(bool *r);//�˵�
bool InitList(List** head);//��������
bool DestroyList(List** head);//��������--2
bool ClearList(List* head);//�������--3
bool ListEmpty(List* head);//��������Ƿ�Ϊ��---4
int ListLong(List* head);//���������---5
bool GetVal(List* head,int i,int* e);//���ص�i��Ԫ�ص�ֵ--6
int LocalNum(List* head,int e);//���غ�Ԫ��e��ȵ�ֵ--7

int main() {//������
    char E[4] = "\0";
    int num, l_num;
    //��ʼ��-------------------------------
    List *ps[ListLength];//��������
    for (int i = 0; i < ListLength; ++i) {
        ps[i]=NULL;
    }

    while (1) {
        printf("ѡ��������ĸ�������в�����1-99������0�˳���:\n");
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
                        printf("�������ɹ�!\n");
                    else
                        printf("�����Ѿ�����!\n");
                }
                else if(num==2){
                    if (DestroyList(&ps[l_num]))
                        printf("�������ٳɹ�!\n");
                    else
                        printf("��������!\n");
                }
                else if(num==3){
                    if (ClearList(ps[l_num]))
                        printf("������ճɹ�!\n");
                    else
                        printf("��������!\n");
                }
                else if(num==4){
                    if(ps[l_num]){
                        if (!ListEmpty(ps[l_num]))
                            printf("����Ϊ��!\n");
                        else
                            printf("�����!\n");
                    } else printf("��������!\n");
                }

                else if(num==5){
                    if(ps[l_num]){
                        int length= ListLong(ps[l_num]);
                        if (length)
                            printf("������Ϊ%d!\n",length);
                        else
                            printf("�����!\n");
                    } else printf("��������!\n");
                }

                else if(num==6){
                    if(ps[l_num]){
                        int i;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("�����ȡ�ڼ���Ԫ�ص�ֵ:\n");
                        scanf("%d",&i);

                        if (GetVal(ps[l_num],i,e))
                            printf("��%d��Ԫ�ص�ֵΪ%d!\n",i,*e);
                        else
                            printf("��ȡԪ��ʧ��!\n");
                        free(e);
                    } else printf("��������!\n");
                }

                else if(num==7){
                    if(ps[l_num]){
                        int e,i;
                        printf("������Ҫ��ѯ��Ԫ��:\n");
                        scanf("%d",&e);
                        i= LocalNum(ps[l_num],e);
                        if (i)
                            printf("Ԫ��%d��λ���ڱ��е�λ����%d!\n",e,i);
                        else
                            printf("�����ڸ�Ԫ��!\n");
                    } else printf("��������!\n");
                }

            }
        } else printf("�����ڸ���������!\n");

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
        printf("��ѡ����Ĳ���[1-14]:\n");
    }
    *r=true;//��ӡһ��
}


bool InitList(List** head){
    if(*head)return false;
    (*head)=(List*) malloc(sizeof(List));
    if(!*head) exit(OVERFLOW);
    (*head)->val=0;//��ʼ��
    (*head)->next=NULL;
    return true;
}//��������----1

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
}//��������--2

bool ClearList(List* head){
    List *p,*q;
    if(!head)return false;
    for (q=head->next; q !=NULL ; q=q->next) {
        free(p);
        p=q;
    }
    q=NULL;
    head->next=NULL;
    return true;
}//�������--3

bool ListEmpty(List* head){
    if(head->next)return false;
    else return true;
}//��������Ƿ�Ϊ��---4

int ListLong(List* head){
    int i=0;
    for (List *p=head->next; p !=NULL ;p=p->next) {
        i++;
    }
    return i;
}//���������---5

bool GetVal(List* head,int i,int* e){
    List *p=head->next;
    if(i<1||i>head->val) return false;
    for (int j = 0; j < i; ++j) {
        p=p->next;
    }
    *e=p->val;
    return true;
}//���ص�i��Ԫ�ص�ֵ--6

int LocalNum(List* head,int e){
    int i = 1;
    List *p=head->next;
    for (; p!=NULL ; ++i) {
        if(p->val!=e)p=p->next;
        else return i;
    }
    return 0;

}//���غ�Ԫ��e��ȵ�ֵ--7