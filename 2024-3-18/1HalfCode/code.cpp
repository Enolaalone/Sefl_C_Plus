#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x='/';
//int q=0;
typedef struct Stack{//ջ
    int point;
    int data[200];
}Stack;

void push(Stack* p,int s){//��ջ
    p->point++;
    p->data[p->point]=s;
}
int pop(Stack* p){//��ջ
    if(p->point==-1)return -1;
    else{
        p->point--;
        return p->data[p->point+1];
    }
}

typedef struct Node{//���ṹ��
    char name[3];//�����ֶ�ȡ
    int weight;
    int parent;
    int l_kid;
    int r_kid;
    int num;
}Node;

//\n 1520
int reading(Node nodes[],char names[],int n){//���� ��ȡ�ļ� ����
    char words[20];
    FILE *fp= fopen(names,"r");
    while (fgets(words,20,fp)!=NULL){
        sscanf(words,"%s\t%d",nodes[n].name,&nodes[n].weight);
        n++;
    }
    strcpy(nodes[n].name,"\n");
    nodes[n].weight=1521;
    n++;
    return n;
}

void create_list(Node nodes[],int n){//������
    int k=2*n-1;
    for (int i = 0; i < k ; ++i) {
        if(i<n){
            nodes[i].parent=-1;//���ڵ��������λ��
            nodes[i].l_kid=-1;//�ӽڵ�ָ���������λ��
            nodes[i].r_kid=-1;
        }else{
            strcpy(nodes[i].name,"\0");
            nodes[i].weight=0;//Ȩ��
            nodes[i].parent=-1;//���ڵ�ָ��������λ��
            nodes[i].l_kid=-1;//�ӽڵ�ָ���������λ��
            nodes[i].r_kid=-1;
        }
        nodes[i].num=i;
    }
}

void swap(int *s1,int *s2){//����
    int t;
    t=*s1;
    *s1=*s2;
    *s2=t;
}

void compare(Node nodes[],int s[],int k){//Ѱ����С�ʹ�С
    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1){
            s[0]=nodes[i].weight;//s[0]ΪȨ��
            s[1]=i;//λ��
            for (int j = i+1; j < k; ++j) {
                if(nodes[j].parent==-1){
                    s[2]=nodes[j].weight;//��СȨ��
                    s[3]=j;//λ��
                    break;
                }
            }
            break;
        }
    }
    if(s[0]>s[2]){//�����С���ڴ�С������λ��
        swap(&s[1],&s[3]);
        swap(&s[0],&s[2]);
    }

    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1 && i!=s[1] && i!=s[3]){
            if(nodes[i].weight<s[0]){//С����С�ỻ��С����С�Ƶ���С��
                s[2]=s[0];s[3]=s[1];
                s[0]=nodes[i].weight;s[1]=i;
            }
            else if(nodes[i].weight>=s[0] && nodes[i].weight<s[2]){//������С��С�ڴ�С�����������С
                s[2]=nodes[i].weight;s[3]=i;
            }
        }
    }
}
void connect(Node nodes[],int n){//����
    int k=2*n-1;//�ڵ���2n-1
    for (int i = 0; i < k-n; ++i) {
        int s[4];
        compare(nodes,s,n+i);

        nodes[n+i].weight=s[0]+s[2];//s[0] s[2]Ϊ�ӽڵ�Ȩ��
        //========λ��ȷ��========
        nodes[n+i].l_kid=s[1];
        nodes[n+i].r_kid=s[3];
        nodes[s[1]].parent=n+i;
        nodes[s[3]].parent=n+i;
    }
}

void stack_code(Node nodes[],int n){
    Stack *ps=(Stack*) malloc(sizeof (Stack));//��ջ
    ps->point=-1;

    FILE *pf= fopen("code.txt","w");//�����ļ�
    for (int i = 0; i < n; ++i) {
        Node y=nodes[i];
        while(y.parent!=-1){
            if(nodes[y.parent].l_kid==y.num){
                push(ps,0);
            } else push(ps,1);
            y=nodes[y.parent];
        }
        fprintf(pf,"%s\t",nodes[i].name);//��ӡ����
        while (ps->point!=-1) {
            fprintf(pf,"%d", pop(ps));//��ӡ����
        }
        fprintf(pf,"\n");
    }
    free(ps);
}
//========������==============
int main() {
    int n=0,k=4003*2-1;
    Node nodes[k];
    char names[]="s1.txt";//Ȩ���ļ�����
    n=reading(nodes,names,n);
    create_list(nodes,n);
    connect(nodes,n);
    stack_code(nodes,n);
    return 0;
}