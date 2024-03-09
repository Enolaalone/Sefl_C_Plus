#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//ָ�����鳤��
#define OVERFLOW -2//ָ�����鳤��
#define LIST_SIZE 100// int* next����
bool pr=false;

typedef struct List{//����ṹ
    int* next;
    int val;
    int list_size;
}List;

bool InitList(List* head);//��������
bool DestroyList(List*head);//�����б�
bool ClearList(List*head);//����б�
bool EmptyList(List*head);//�ⶨ���Ƿ�Ϊ��
int ListLong(List*head);//�ⶨ��
bool GetVal(List *head,int i,int *e);//���ر�Ԫ��
void print(bool *r);
//------------------------------------------------------------------------------------
int main() {//������
    char E[4]="\0";
    int num,l_num;
    //��ʼ��-------------------------------
    List** ps=(List**) malloc(ListLength*sizeof (List*));//��������
    if(!ps)exit(OVERFLOW);//δ�����ɹ�
    for (int i = 0; i < ListLength; ++i) {//��ʼ����������
        ps[i]=(List*) malloc(sizeof (List));
        if(!ps[i])exit(OVERFLOW);
        ps[i]->next=NULL;
        ps[i]->val=0;
        ps[i]->list_size=0;
    }

    while(1){
        printf("ѡ��������ĸ�������в�����1-99������0�˳���:\n");
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
                else if(num==1){//��������
                    printf("%d\n",num);
                    if(!ps[l_num]->next){
                        InitList(ps[l_num]);
                        printf("���Ա����ɹ���\n");
                    }
                    else printf("���Ա��Ѿ�������\n");
                }
                else if(num==2){
                    printf("%d\n",num);
                    if(ps[l_num]->next){
                        if(DestroyList(ps[l_num]))
                        printf("���ٱ�ɹ���\n");
                        else exit(-1);
                    }
                    else printf("���Ա��Ѿ����٣�\n");
                }
                else if(num==3){
                    printf("%d\n",num);
                    if(!ClearList(ps[l_num])) break;
                    else printf("���Ա��������\n");
                }
                else if(num==4){
                    printf("%d\n",num);
                    if(EmptyList(ps[l_num])) printf("���Ա��ǿյģ�\n");
                    else printf("���Ա�ǿգ�\n");
                }
                else if(num==5){//---------5
                    printf("%d\n",num);
                    printf("��Ϊ%d!\n", ListLong(ps[l_num]));
                }
                else if(num==6){//---------6
                    printf("%d\n",num);
                    int*e,i;
                    printf("��ȡԪ�ص�λ�ã�\n");
                    scanf("%d",&i);
                    if(GetVal(ps[l_num],i,e)){
                        printf("%d��Ԫ��Ϊ%d\n",i,*e);
                    } else printf("Ԫ�ز�����!\n");
                }


            }

        }

    }

    free(ps);
    return 0;
}

bool InitList(List* head){//��������
    head->next=(int*) malloc(LIST_SIZE*sizeof (int ));
    if(!head->next){//δ�����ɹ�
        exit(OVERFLOW);
    }
    head->val=0;
    head->list_size=LIST_SIZE;//���Ա���
    return true;
}
bool DestroyList(List*head){
    if(head->next){
        free(head->next);//�ͷſռ�
        head->next=NULL;//�������
        head->val=0;//����0
        head->list_size=0;//��С0
        return true;
    } else return false;

}//�����б�

bool ClearList(List*head){
    if(head->next){
        head->val=0;//ʹ�ó���Ϊ0
        return true;
    }else{
        printf("�������ڣ�\n");
        return false;
    }

};//����б�
bool EmptyList(List*head){//-------------4
    if(head->val==0)return true;
    else return false;
};//�ⶨ���Ƿ�Ϊ��
int ListLong(List*head){
    return head->val;
}//�ⶨ��
bool GetVal(List* head,int i,int *e){
    if(head->val==0 | i<1 |i>head->val) return false;
    *e=head->next[i-1];//����next������i��Ԫ��
    return true;
};//���ر�Ԫ��
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
        printf("��ѡ����Ĳ���[1-14]:\n");
    }
    *r=true;//��ӡһ��
}