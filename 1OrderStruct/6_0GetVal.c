#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//ָ�����鳤��
#define OVERFLOW -2//ָ�����鳤��
bool pr=false;
typedef struct List{//����ṹ
    struct List* next;
    int val;
}List;

bool InitList(List* head);//��������
bool DestroyList(List*head);//�����б�
bool ClearList(List*head);//����б�
bool EmptyList(List*head);//�ⶨ���Ƿ�Ϊ��
int ListLong(List*head);//�ⶨ��
bool GetVal(List head,int i,int *e);//���ر�Ԫ��
void print(bool *pr);
//------------------------------------------------------------------------------------
int main() {//������
    char E[4]="\0";
    int num,l_num;

    List** ps=(List**) malloc(ListLength*sizeof (List*));//��������
    if(!ps)exit(OVERFLOW);//δ�����ɹ�
    for (int i = 0; i < ListLength; ++i) {//��ʼ����������
        ps[i]=(List*) malloc(sizeof (List));
        if(!ps[i])exit(OVERFLOW);
        ps[i]->next=NULL;
        ps[i]->val=0;
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
                        printf("�����������ɹ���\n");
                    }
                    else printf("���������Ѿ�������\n");
                }
                else if(num==2){
                    printf("%d\n",num);
                    if(ps[l_num]->next){
                        if(DestroyList(ps[l_num]))
                        printf("��������ɹ���\n");
                        else exit(-1);
                    }
                    else printf("���������Ѿ����٣�\n");
                }
                else if(num==3){
                    printf("%d\n",num);
                    if(!ClearList(ps[l_num])) break;
                    else printf("�����������\n");
                }
                else if(num==4){
                    printf("%d\n",num);
                    if(EmptyList(ps[l_num])) printf("�����ǿյģ�\n");
                    else printf("����ǿգ�\n");
                }
                else if(num==5){//---------5
                    printf("%d\n",num);
                    printf("��Ϊ%d!\n", ListLong(ps[l_num]));
                }


            }

        }

    }

    free(ps);
    return 0;
}

bool InitList(List* head){//��������
    head->next=(List*) malloc(sizeof (List));
    if(!head->next){//δ�����ɹ�
        exit(OVERFLOW);
    }
    head->next->next=NULL;
    head->next->val=0;
    return true;
}
bool DestroyList(List*head){
    free(head->next);
    head->next=NULL;
    if(!head->next)return true;
    else return false;

}//�����б�

bool ClearList(List*head){
    if(head->next){
        head->next=NULL;
        head->val=0;
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
bool GetVal(List head,int i,int *e){
    if(head.val==0 | i<1 |i>head.val) return false;
    *e=head.next[i-1];
    return true;
};//���ر�Ԫ��
void print(bool *pr){
    if(!*pr){
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
    *pr=true;//��ӡһ��
}