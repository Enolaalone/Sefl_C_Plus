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
bool InitList(List* head);//��������
bool DestroyList(List* head);//��������--2

int main() {//������
    char E[4] = "\0";
    int num, l_num;
    //��ʼ��-------------------------------
    List **ps = (List **) malloc(ListLength * sizeof(List *));//��������
    if (!ps)exit(OVERFLOW);//δ�����ɹ�
    for (int i = 0; i < ListLength; ++i) {//��ʼ����������
        ps[i] = (List *) malloc(sizeof(List));
        if (!ps[i])exit(OVERFLOW);
        ps[i]->next = NULL;
        ps[i]->val = 0;

    }
    while (1) {
        printf("ѡ��������ĸ�������в�����1-99������0�˳���:\n");
        gets(E);
        l_num = atoi(E);
        if (l_num == 0)break;
        else {
            while (1) {
                print(&pr);
                gets(E);
                num = atoi(E);
                if (num == 0) {
                    pr = false;
                    break;
                } else if (num == 1) {
                    if (InitList(ps[l_num]))
                        printf("�������ɹ�!\n");
                    else
                        printf("�����Ѿ�����!\n");
                }
                else if(num==2){
                    if (DestroyList(ps[l_num]))
                        printf("�������ٳɹ�!\n");
                    else
                        printf("��������!\n");
                }

            }
        }

    }
    free(ps);
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
    if(head->next)return false;
    head->next=(List*) malloc(sizeof(List));
    if(!head->next) exit(OVERFLOW);
    head->next->val=0;
    head->next->next=NULL;
    return true;
}//��������----1

bool DestroyList(List* head){
    if(!head->next)return false;
    head->next=NULL;
    head->val=0;
    return true;
}//��������--2