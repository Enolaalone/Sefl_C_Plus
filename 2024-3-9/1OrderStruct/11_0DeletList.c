#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ListLength 100//ָ�����鳤��
#define OVERFLOW -2//ָ�����鳤��
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
                    int i;
                    int *e=(int*) malloc(sizeof (int));
                    if(!e)exit(OVERFLOW);
                    printf("��ȡԪ�ص�λ�ã�\n");
                    scanf("%d",&i);
                    if(GetVal(ps[l_num],i,e)){
                        printf("%d��Ԫ��Ϊ%d\n",i,*e);
                    } else printf("Ԫ�ز�����!\n");
                    free(e);
                }
                else if(num==7){//---------7
                    printf("%d\n",num);
                    int q;
                    printf("������Ҫ��ѯԪ�أ�\n");
                    scanf("%d",&q);
                    int k=LocalNum(ps[l_num],q);
                    if(k){
                        printf("%dԪ�ص�λ��Ϊ%d\n",q,k);
                    } else printf("Ԫ�ز�����!\n");
                }
                else if(num==8){//---------8
                    printf("%d\n",num);
                    if(ps[l_num]->next!=NULL){
                        int q;
                        int *pre_e=(int*) malloc(sizeof (int));
                        if(!pre_e)exit(OVERFLOW);
                        printf("������Ҫ��ѯǰ����Ԫ�أ�\n");
                        scanf("%d",&q);

                        if(PreNum(ps[l_num],q,pre_e)){
                            printf("%dǰһ��Ԫ�ص�Ԫ��Ϊ%d\n",q,*pre_e);
                        } else printf("Ԫ��ǰ���ڵ㲻����!\n");
                        free(pre_e);
                    }else{
                        printf("���Ա�����!\n");
                    }
                }
                else if(num==9){//---------9
                    printf("%d\n",num);
                    if(ps[l_num]->next!=NULL){
                        int q;
                        int *pre_e=(int*) malloc(sizeof (int));
                        if(!pre_e)exit(OVERFLOW);
                        printf("������Ҫ��ѯ������Ԫ�أ�\n");
                        scanf("%d",&q);

                        if(LaterNum(ps[l_num],q,pre_e)){
                            printf("%d��һ��Ԫ�ص�Ԫ��Ϊ%d\n",q,*pre_e);
                        } else printf("Ԫ�غ����ڵ㲻����!\n");
                        free(pre_e);
                    }else{
                        printf("���Ա�����!\n");
                    }
                }
                else if(num==10){//---------10
                    printf("%d\n",num);
                    if(ps[l_num]->next!=NULL){
                        int i,e;
                        printf("�������Ԫ�ص�λ�úͲ����Ԫ�أ�\n");
                        scanf("%d %d",&i,&e);

                        if(AddList(ps[l_num],i,e)){
                            printf("����ɹ�\n");
                        } else printf("����ʧ��!\n");
                    }else{
                        printf("���Ա�����!\n");
                    }
                }
                else if(num==11){//---------11
                    printf("%d\n",num);
                    if(ps[l_num]->next!=NULL){
                        int i;
                        int *e=(int*) malloc(sizeof (int));
                        if(!e)exit(OVERFLOW);
                        printf("����ɾ��Ԫ�ص�λ�ã�\n");
                        scanf("%d",&i);

                        if(DeleteList(ps[l_num],i,e)){
                            printf("%d��Ԫ��%dɾ���ɹ�\n",i,*e);
                        } else printf("ɾ��ʧ��!\n");
                        free(e);
                    }else{
                        printf("���Ա�����!\n");
                    }
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
bool GetVal(List* head,int i,int*e){
    if(head->val==0 | i<1 |i>head->val) return false;
    *e=head->next[i-1];//����next������i��Ԫ��
    return true;
};//���ر�Ԫ��
int LocalNum(List *head,int q){//------7
    if(head->next!=NULL){//Ԫ���б�ǿ�
        for (int i = 0; i < head->val; ++i) {
            if(head->next[i]==q) return i+1;
        }
    }
    return 0;

}//����Ԫ��
bool PreNum(List *head,int q,int* pre_e){
    int local= LocalNum(head,q);
    if(local){
        *pre_e=head->next[local-1];
        return true;
    }else return false;
}//����ǰ��Ԫ��--8
bool LaterNum(List *head,int q,int* pre_e){
    int local= LocalNum(head,q);
    if(local){
        *pre_e=head->next[local+1];
        return true;
    }else return false;
}//���Һ���Ԫ��--9
bool AddList(List *head,int i,int e){
    int *new,*p;
    if(i<1||i>head->val+1) return false;
    if(head->val+1>head->list_size){
        new=(int*) realloc(head->next,head->list_size+Length_LIST_SIZE);
        if(!new) exit(OVERFLOW);//������Ϊ�����ɹ�
        head->next=new;
        head->list_size+=Length_LIST_SIZE;
    }
    p=&head->next[i-1];//i��Ԫ�صĵ�ַ
    for (int* j = &head->next[head->val-1]; j >=p; j--) {//β�
        *(j+1)=*j;
    }
    *p=e;//����Ԫ��e
    head->val++;
    return true;
}//��iλ�ò���e--10
bool DeleteList(List *head,int i,int* e){
    int *q;
    if(i<1||i>head->val) return false;
    *e=head->next[i-1];//����ɾ��Ԫ��
    q=&head->next[head->val-1];
    for (int* j = &head->next[i-1]; j < q ; ++j) {
        *j=*(j+1);
    }
    head->val--;
    return true;
}//ɾ��iλ��---11
void print(bool *r){
    if(!*r){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf("1.InisList\t8.PreNum\n");
        printf("2.DestroyList\t9.LaterNum\n");
        printf("3.ClearList\t10.AddList\n");
        printf("4.EmptyList\t11.DeleteList\n");//----------------------------------4
        printf("5.ListLong\t         \n");//----------------------------------5
        printf("6.GetVal\t         \n");//----------------------------------6
        printf("7.LocalNum\t         \n");//----------------------------------7
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("��ѡ����Ĳ���[1-14]:\n");
    }
    *r=true;//��ӡһ��
}