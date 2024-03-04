#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>//INT_MAX
#define M 100
bool is[256];//��¼����


//Hash���ݽṹ
typedef struct aList{//��
    int num;//����λ��
    struct aList*next;//��һ���ӵ�ַ
}*L;//ָ������

typedef struct AOVList{
    int num;//�����
    char name[5];//��Ŀ����
    int pass;//�Ƿ����--------------------------------------------------------
    int weight;//ʱ��----------------------------------------------------------------------------------------------------
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
            is[word[0]]=true;//��������Ӧ�ڽӱ�
        }
    } else return;//���ַ�����

    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){//����
                p[k].name[0]=word[i];//����
                p[k].name[1]='\0';//����
                is[word[i]]=true;//��������Ӧ�ڽӱ�
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
        else if(word[i]>='0' && word[i]<='9'){//------------------------------------------------------------------------
            p[(int)(word[0]-'A')].weight=10*p[(int)(word[0]-'A')].weight+(int)(word[i]-'0');
        }//-------------------------------------------------------------------------------------------------------------
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
}

void print(AL p[],int *i){
    //------------------��ӡ--------------------
    printf("���\t�����\t����\tʱ��Ȩ��\t������Ŀ\n");
    while(p[*i].name[0]>='A'&& p[*i].name[0]<='Z'){
        printf("%d\t%d\t%s\t%d\t",*i,p[*i].num,p[*i].name,p[*i].weight);//----------------------------------------------------
        for (L j =p[*i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("^\n");
        (*i)++;
    }
    printf("����������%d\n",*i);
    //---------------------------------------
}
bool Compare(AL p[],int i){//�������� ���رջ�λ��
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
        is[ap0->name[0]]= false;//�ڵ��Ѿ����----------------------------
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
        printf("�бջ�\n");
        return false;
    } else return true;
    //-----------------------------------------
}

ALP Circle(int num,AL p[]){
    L ql;
    p[num].pass=1;//���ڷ���
    if(p[num].next==NULL) {
        p[num].pass=-1;//��������
        return NULL;
    }
    ql=p[num].next;
    do{
        if(p[ql->num].pass==1) return &p[ql->num];//��
        if(p[ql->num].pass==0 && Circle(ql->num,p)!=NULL) return &p[ql->num];//��

        ql=ql->next;
    }while(ql!=NULL);
    p[num].pass=-1;//��������
    return NULL;

}

void JudgeCircle(bool k,int i,AL p[]){
    if(k) printf("�޻�·\n");//���رջ�ǰ��������
    else{
        printf("���ֻ���");
        for (int j = 0; j < i; ++j) {
            ALP CL=Circle(j,p);
            if(CL!=NULL && is[CL->name[0]]){//��ӡû������Ĳ���
                is[CL->name[0]]=false;//�൱���Ѿ����
                printf("%s\t",CL->name);
            }
        }

    }
}

void dijkstra(AL p[],int pre[],int dtc[],int source,int i){
    bool visited[i];//�Ƿ����
    for (int j = 0; j < i; ++j) {//��ʼ��
        visited[j]=false;
        pre[j]=-1;
        dtc[j]=INT_MAX;//�����
    }
    dtc[source]=0;//A���������Ϊ0
    int n;//��ԭ�������С�������
    for (int j = 0; j < i-1; ++j) {//����i-1��
        int min=INT_MAX;
        for (int k = 0; k < i; ++k) {//����dtc�ҵ�·�����
            if(!visited[k]&&dtc[k]<min){
                min=dtc[k];
                n=k;
            }
        }
        visited[n]=true;//�ڵ��ҵ�

        // ���µ�ǰ���·����ǰ������
        // ��������"δ��ȡ���·���Ķ�������·����ǰ������"��

        L ql=p[n].next;//���ڽڵ�����
        while(ql){
            if(!visited[ql->num]&&p[n].weight+dtc[n]<dtc[ql->num]&&dtc[n]!=INT_MAX){
                dtc[ql->num]=p[n].weight+dtc[n];//�������ڽڵ�·��
                pre[ql->num]=n;//ql->num��ǰ���ڵ�Ϊn
            }
            ql=ql->next;
        }
    }
}

void PrintWay(int pre[],AL p[],int n){
    if(pre[n]==-1){
        printf("%s",p[n].name);
        return;
    }
    PrintWay(pre,p,pre[n]);
    printf("->%s",p[n].name);
}

int main() {
    int i=0;//���鳤��
    char word[30];
    ALP p=(ALP) malloc(M*sizeof (AL));//�����ڴ�
    for (int j = 0; j < M; ++j) {//��ʼ��
        p[j].next=NULL;
        p[j].pass=0;
    }
    FILE *fp= fopen("./p2.txt","r");//----------------------------------�ı�
    while(fgets(word,sizeof (word),fp)!=NULL){
        Read(word,p);
    }
    fclose(fp);
    //---------��ӡ���-------------------
    print(p,&i);
    //----------����-----�ջ�-------------
    JudgeCircle(Compare(p,i),i,p);
    //---------�������----------------

    int dtc[i];//����
    int pre[i];//ǰ�ڵ�
    int source=0;//A�ڵ�
    dijkstra(p,pre,dtc,source,i);
    for (int j = 1; j < i; ++j) {
        printf("A To %s: ",p[j].name);
        PrintWay(pre,p,j);
        printf("\n");
    }

    free(p);//�ͷ��ڴ�
    return 0;
}