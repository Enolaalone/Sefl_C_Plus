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
bool PreNum(List* head,int k,int* e);//����qԪ�صĺ���--8
bool LaterNum(List* head,int k,int* e);//����qԪ�صĺ���--9
bool ListInsert(List* head,int i,int k);//iԪ��ǰ����Ԫ��k--10
bool ListDelete(List* head,int i);//ɾ��i��Ԫ��--11
bool ListRun(List* head);//��������--12
bool Write(List *head,char* name);//д���ļ�--13

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

                else if(num==8){
                    if(ps[l_num]){
                        int k;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("�����ȡĳԪ�ص�ǰ��Ԫ��:\n");
                        scanf("%d",&k);

                        if (PreNum(ps[l_num],k,e))
                            printf("��%dԪ�ص�ǰ��Ԫ��Ϊ%d!\n",k,*e);
                        else
                            printf("��ȡǰ��Ԫ��ʧ��!\n");
                        free(e);
                    } else printf("��������!\n");
                }

                else if(num==9){
                    if(ps[l_num]){
                        int k;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("�����ȡĳԪ�صĺ���Ԫ��:\n");
                        scanf("%d",&k);

                        if (LaterNum(ps[l_num],k,e))
                            printf("��%dԪ�صĺ�ȡԪ��Ϊ%d!\n",k,*e);
                        else
                            printf("��ȡ����Ԫ��ʧ��!\n");
                        free(e);
                    } else printf("��������!\n");
                }

                else if(num==10){
                    if(ps[l_num]){
                        int i,k;
                        printf("�����ڵڼ���Ԫ��ǰ����ĳԪ��:\n");
                        scanf("%d %d",&i,&k);

                        if (ListInsert(ps[l_num],i,k))
                            printf("����ɹ�!\n");
                        else
                            printf("����Ԫ��ʧ��!\n");
                    } else printf("��������!\n");
                }

                else if(num==11){
                    if(ps[l_num]){
                        int i,k;
                        printf("����ɾ���ڼ���Ԫ��:\n");
                        scanf("%d",&i);

                        if (ListDelete(ps[l_num],i))
                            printf("ɾ���ɹ�!\n");
                        else
                            printf("ɾ��ʧ��!\n");
                    } else printf("��������!\n");
                }

                else if(num==12){
                    if(ps[l_num]){
                        if (ListRun(ps[l_num]))
                            printf("�����ɹ�!\n");
                        else
                            printf("����ʧ��!\n");
                    } else printf("��������!\n");
                }

                else if(num==13){
                    if(ps[l_num]){
                        char name[30];
                        printf("���뽨�����ļ�����\n");
                        scanf("%s",name);
                        if (Write(ps[l_num],name))
                            printf("�ļ������ɹ�!\n");
                        else
                            printf("����ʧ��!\n");
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
    head->val=0;
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

bool PreNum(List* head,int k,int* e){
    List *p=head->next,*q;
    int num= LocalNum(head,k);//ȷ��λ�ã����û��num=0
    if(num && p!=NULL){
        for (int i = 1; i!=num ; ++i) {
            if(i==1&&p->val) return false;//һ��Ԫ��û��ǰ��
            else{
                q=p;//����ǰ�ڵ�
                p=p->next;
            }
        }
        *e=q->val;
        return true;
    }
    else return false;
}//--8����qԪ�صĺ���--8

bool LaterNum(List* head,int k,int* e){
    List *p=head->next;
    int num= LocalNum(head,k);//ȷ��λ�ã����û��num=0
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
}//����qԪ�صĺ���--9

bool ListInsert(List* head,int i,int k){
    List *p=head->next,*q;
    if(p!=NULL && i>1 && i<=head->val){
        for (int j=1;j!=i;++j) {
            q=p;//����ǰ�ڵ�
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
}//iԪ��ǰ����Ԫ��k--10

bool ListDelete(List* head,int i){
    List *p=head->next,*q=head;
    if(p!=NULL && i>1 && i<=head->val){
        for (int j=1;j!=i;++j) {
            q=p;//����ǰ�ڵ�
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
}//ɾ��i��Ԫ��--11

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
}//��������--12

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
}//д���ļ�--13