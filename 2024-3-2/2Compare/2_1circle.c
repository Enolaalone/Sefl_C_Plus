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
//--------------------------------------------
void Read(char *word,AL p[]){//�������飬���
    int i=1,k,in_num=0;//�ӵ�һ����ʼ���
    k=(int)(word[0]-'A');
    if(word[0]>='A' && word[0]<='Z' ){//����
        if( !is[word[0]]){
            p[k].name[0]=word[0];//����
            p[k].name[1]='\0';//����
            is[word[0]]=true;
        }
    } else return;//���ַ�����

    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){//����
                p[k].name[0]=word[i];//����
                p[k].name[1]='\0';//����
                is[word[i]]=true;
            }
            if(p[k].next==NULL) {
                p[k].next=(L) malloc(sizeof (struct aList));//�����ڴ�
                p[k].next->num=(int)(word[0]-'A');//����ַ
                p[k].next->next=NULL;
            } else {
                L L_p=p[k].next;
                while(1)  {
                    if(L_p->next!=NULL){
                        L_p=L_p->next;
                        continue;
                    } else{
                        L_p->next=(L) malloc(sizeof (struct aList));
                        L_p->next->num=(int)(word[0]-'A');
                        L_p->next->next=NULL;
                        break;
                    }
                }
            }
        }
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
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
ALP Compare(AL p[],int i){//�������� ���رջ�λ��
    //-----------------����-----------------
    ALP ap0,ap1;//�������ĵ�ַ
    int put_l=0;//�������
    list ps=(list) malloc(sizeof (Stack));//��ջ
    ps->pointer=-1;//��ʼ��ջָ��
    printf("��������\n");
    for (int j = 0; j < i; ++j) {
        if(p[j].num==0) push(ps,&p[j]);//��ջ
    }
    ap0= pop(ps);
    while (ap0!=NULL) {
        printf("%s\t",ap0->name);
        put_l++;
        for (L j = ap0->next; j != NULL; j = j->next) {
            p[j->num].num--;//�����-1
            if (p[j->num].num == 0) push(ps, &p[j->num]);//�����Ϊ0 ��ջ
        }
        ap1=ap0;//���бջ�ʱ��ȷ��λ��
        ap0= pop(ps);
    }
    //--------------�ջ�����---------------------
    if(put_l<i){
        printf("�бջ�");
        return ap1;
    } else return NULL;
    //-----------------------------------------
}
int main() {
    int i=0;//���鳤��
    char word[30];
    ALP p=(ALP) malloc(M*sizeof (AL));//�����ڴ�
    for (int j = 0; j < M; ++j) {
        p[j].next=NULL;
    }
    FILE *fp= fopen("./p01.txt","r");
    while(fgets(word,sizeof (word),fp)!=NULL){
        Read(word,p);
    }
    fclose(fp);
    //---------��ӡ���-------------------
    print(p,&i);
    //----------����-------------------
    Compare(p,i);


    free(p);//�ͷ��ڴ�
    return 0;
}