#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 100
bool is[256];
//Hash���ݽṹ
typedef struct aList{//��
    int num;//����λ��
    struct aList*next;//��һ���ӵ�ַ
}*L;//ָ������

typedef struct AOVList{
    int num;//�����
    char name[25];//��Ŀ����
    L next;//��
}AL,*ALP;
//----------------ջ-------------------
typedef struct Stack{
    int pointer;//ָ��
    ALP data[50];//����
}Stack,*list;

void push(list s,ALP c){//��ַ��ջ
    s->pointer++;
    s->data[s->pointer]=c;
}

ALP pop(list s){//���ص�ַ
    if(s->pointer==-1) return NULL;
    else{
        s->pointer--;
        return s->data[s->pointer+1];
    }
}
void CreateEdge(int forward,int backward,AL p[]){
    //������
    L ls=(L)malloc(sizeof(aList));
    if(!ls) exit(-2);
    ls->num=backward;
    //ͷ�巨
    ls->next=p[forward].next;
    p[forward].next=ls;

}
void Read(AL p[]){
    char word[30];
    FILE*fp=fopen("p01.txt","r");
    if(!fp) exit(-1);
//------------------------
    char *pr=NULL,*token=NULL;
    char ltr[]=",",letter;//�ָ���ַ���
    while (fgets(word,sizeof(word),fp)!=NULL)
    {//��ȡ��һ���ַ�
        token=strtok_r(word,ltr,&pr);
        // printf("%s\n",token);
        int k=(int)(token[0]-'A');
        if(token[0]>='A' && token[0]<='Z' ){//����
                p[k].name[0]=token[0];//����
                p[k].name[1]='\0';//����
        } else continue;//���ַ�����
        letter=token[0];
        //��ȡʣ��ָ�Ԫ��
        token=strtok_r(NULL,ltr,&pr);
        while (token!=NULL)
        {
            // printf("%s\n",token);
            if(token[0]>='A' && token[0]<='Z')
            CreateEdge(token[0]-'A',letter-'A',p);
            p[letter-'A'].num++;
            token=strtok_r(NULL,ltr,&pr);
            }
        
    }
    fclose(fp); 
}

void print(AL p[],int *i){
    //------------------��ӡ--------------------
    printf("���\t�����\t����\t������Ŀ\n");
    while(p[*i].name[0]>='A'&& p[*i].name[0]<='Z'){
        printf("%d\t%d\t%s\t",*i,p[*i].num,p[*i].name);
        for (L j =p[*i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("^\n");
        (*i)++;
    }
    printf("����������%d\n",*i);
    //---------------------------------------
}
int main(){
    //�ڽӱ��ʼ��
    ALP p=(ALP)malloc(M*sizeof(AL));
    for (int i = 0; i < M; i++)
    {
        p[i].next=NULL;
        p[i].num=0;
    }
    //---------------------
    int i=0;
    Read(p);
    print(p,&i);
    
}