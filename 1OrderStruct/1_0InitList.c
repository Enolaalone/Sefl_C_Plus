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
void print(bool *pr);
//------------------------------------------------------------------------------------
int main() {//������
    char E[4]="\0";
    int num,l_num;

    List** ps=(List**) malloc(ListLength*sizeof (List*));//��������
    if(!ps)exit(OVERFLOW);//δ�����ɹ�
    for (int i = 0; i < ListLength; ++i) {
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

void print(bool *pr){
    if(!*pr){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf("1.InisList\n");
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("��ѡ����Ĳ���[1-14]:\n");
    }
    *pr=true;//��ӡһ��
}