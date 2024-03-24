#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//ָ�����鳤��
#define OVERFLOW -2//ָ�����鳤��
#define ERROR -1//ָ�����鳤��
#define LIST_SIZE 100// int* next����
#define Length_LIST_SIZE 10// int* next���ӳ���
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
int LocalNum(List *head,int q);//����Ԫ��--7
bool PreNum(List *head,int q,int* pre_e);//����ǰ��Ԫ��--8
bool LaterNum(List *head,int q,int* pre_e);//���Һ���Ԫ��--9
bool AddList(List *head,int i,int e);//��iλ�ò���e--10
bool DeleteList(List *head,int i,int* e);//ɾ��iλ��---11
int RunList(List *head);//�����б�--12
bool Write(List *head);//д���ļ�--13
bool Read(List *head);//��ȡ�ļ�--14
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
        printf("��ѡ����Ĳ���[1-14]:\n");
    }
    *r=true;//��ӡһ��
}

bool InitList(List* head){
    int* p=(int*) malloc(LIST_SIZE*sizeof (List));
    if(!p) return false;
    head->next=p;
    head->list_size=LIST_SIZE;
    head->val=0;
    return true;
}//��������

bool DestroyList(List*head){
    free(head->next);
    head->next=NULL;

    head->list_size=0;
    head->val=0;
    return true;
}//�����б�

bool ClearList(List*head){
    head->val=0;
    return true;
}//����б�

bool EmptyList(List*head){
    if(head->val)return false;
    else return true;
}//�ⶨ���Ƿ�Ϊ��

int ListLong(List*head){
    return head->val;
}//�ⶨ��

bool GetVal(List *head,int i,int *e){
    if(i+1>head->val)return false;

    *e=head->next[i];
    return true;
}//���ر�Ԫ��

int LocalNum(List *head,int q){
    for (int i = 0; i < head->val; ++i) {
        if(head->next[i]==q) return i;
    }
    return ERROR;

}//����Ԫ��--7


bool PreNum(List *head,int q,int* pre_e){
    int pos= LocalNum(head,q);
    if(pos==-1||pos==0)return false;

    *pre_e=head->next[pos-1];
    return true;
}//����ǰ��Ԫ��--8

bool LaterNum(List *head,int q,int* pre_e){
    int pos= LocalNum(head,q);
    if(pos==-1||pos==head->val-1)return false;
    *pre_e=head->next[pos+1];
    return true;

}//���Һ���Ԫ��--9

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
}//��iλ�ò���e--10

bool DeleteList(List *head,int i,int* e){
    if(i<0||i>head->val-1) return false;
    *e=head->next[i];
    for (int j = i; j <head->val-1 ; ++j) {
        head->next[j]=head->next[j+1];
    }
    head->val--;
    return true;
}//ɾ��iλ��---11

int RunList(List *head){
    for (int i = 0; i < head->val; ++i) {
        printf("%d\t",head->next[i]);
        if(!(i+1)%10)printf("\n");
    }
    return head->val;

}//�����б�--12

bool Write(List *head){
    char name[20];
    printf("�����ļ�����\n");
    gets(name);
    FILE *pf= fopen(name,"w");
    if(!pf)return OVERFLOW;
    for (int i = 0; i < head->val; ++i) {
        fprintf(pf,"%d\n",head->next[i]);
    }
    fclose(pf);
    return true;
}//д���ļ�--13

bool Read(List *head){
    head->val=0;
    char name[20],word[20];
    printf("�����ļ�����\n");
    gets(name);
    FILE *fp= fopen(name,"r");
    while (fgets(word,sizeof (word),fp)!=NULL){
        if(sscanf(word,"%d",&head->next[head->val++])==1) printf("%d\n",head->val);
        else printf("%s\n",word);
    }

    return true;
}//��ȡ�ļ�--14






