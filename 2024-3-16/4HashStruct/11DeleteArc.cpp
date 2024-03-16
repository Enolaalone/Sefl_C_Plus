#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define OVERFLOW -2
bool pr=false;

typedef struct ArcNode//��
{
    int val;//���
    struct ArcNode *next;//��һ�ڵ��ַ
}ArcNode;

typedef struct VNode//�ڵ�
{
    int num;//���
    int data;//����
    char key;//�ϼ��ڵ�
    ArcNode* next;//Edge
}VNode,AdjNode[100];

typedef struct 
{
    AdjNode vertices;//�ڽӱ�����
    int vernum,arcnum;//������Ŀ���ͱ���

}Graph;

//-------���нṹ-----------
typedef struct QNode//���нڵ�
{
    int val;
    struct QNode* next;
   
}QNode;

typedef struct QLNode
{
    struct QNode* first;//ͷ
    struct QNode* rear;//β��
}QList;
void print(bool *r);
//------------���к���------------

int InitQueue(QList *Q); //����һ���ն���
int QueueEmpty(QList Q); //�ж�һ�������Ƿ�Ϊ��
int EnQueue(QList *Q, int e); //�����
int DeQueue(QList *Q,int *e); //������
//------�ڽӱ���----------------------
int CreatGraph(Graph *G,char V[],char VR[][2]);//����ͼ
int DestroyGraph(Graph *G);//����
int DestroyList(ArcNode *arc);//���ٶ���Ļ�����
int LocateVex(Graph G,char u);//�ɹؼ��ֲ��Ҳ��Ҷ���λ��
int PutVex(Graph *G,char u,int value);//���㸳ֵ
int FirstAdjVex(Graph G,char u);//��õ�һ�ڽӵ�
int NextAdjVex(Graph G,char u,int w);//�����һ�ڽӵ�
int InsertVex(Graph *G,VNode vex);//���붥��
int DeleteVex(Graph *G,char u);//ɾ������
int InsertArc(Graph *G,char u,char z);//���뻡
int DeleteArc(Graph *G,char u,char z);//ɾ����
int DFSTraverse(Graph G,char u);//������ȱ���
char Locatekey(Graph G,int v);//��λ����ҹؼ���
int Locatekey2(Graph G,int v);//��λ��������
int Locatehao(Graph G,char u);//�ɹؼ��ֲ������
int BFSTraverse(Graph G, QList Q);//������ȱ���
int Write(Graph G);//д���ļ�
int Read(Graph *G);//��ȡ�ļ�

int main() {
    Graph M[100],G;
    char V[100],VR[100][2],E[5],u,z;
    int num,v_num,u_num,value,a_num;
    VNode vex;
    while (1)
    {
        pr=false;//�˵���ʼ��
        printf("������Ҫ���ĸ��ڽӱ������1-99������0�˳�\n");
        gets(E);
        v_num=atoi(E);
        if(!v_num)break;
        else if(v_num>99 || v_num<1)printf("�����ڸ��ڽӱ�!\n");
        else{
            G=M[v_num];
            while (1)
            {
                pr=false;//�˵���ʼ��
                print(&pr);
                scanf("%d",&num);//�˵�ѡ��
                if(!num)break;
                else if(num==1){
                    printf("�����ڽӱ�Ķ���������������\n");
                    scanf("%d %d",&G.vernum,&G.arcnum);
                    fflush(stdin);
                    printf("���붥�������:\n");
                
                    for (int i = 0; i < G.vernum; i++)
                    {
                        scanf("%c",&V[i]);
                    }
                    fflush(stdin);
                    printf("����ߵ�����:\n");
                    for (int i = 0; i < G.arcnum; i++)
                    {
                        scanf("%c",&VR[i][0]);
                        scanf("%c",&VR[i][1]);
                        getchar();
                    }

                    if(CreatGraph(&G,V,VR)){
                        printf("�ڽӱ����ɹ�!\n");
                    }else printf("����ʧ��!\n");
                    
                }
                else if(num==2)
                {
                    if(G.vernum){
                        if(DestroyGraph(&G))printf("�ڽӱ�����ɹ���\n");
                        else printf("ʧ�ܣ�\n");
                    }else printf("�ڽӱ����ڣ�\n");
                }

                else if(num==3)
                {
                    if(G.vernum){
                        printf("���붥��ؼ���!\n");
                        scanf("%c",&u);
                        u_num=LocateVex(G,u);
                        if(u_num)printf("��������Ϊ%d\n",u_num);
                        else printf("���㲻���ڣ�\n");
                    }else printf("�ڽӱ����ڣ�\n");
                }

                else if(num==4)
                {
                    if(G.vernum){
                        printf("���붥��ؼ����Լ���ֵ����!\n");
                        scanf("%c %d",&u,&value);

                        if(PutVex(&G,u,value))printf("���㸳ֵ�ɹ���\n");
                        else printf("��ֵʧ�ܣ�\n");
                    }else printf("�ڽӱ����ڣ�\n");
                }

                else if(num==5)
                {
                    if(G.vernum){
                        printf("���붥��ؼ���!\n");
                        scanf("%c",&u);
                        u_num=FirstAdjVex(G,u);
                        if(u_num=-1) printf("�����ڶ��㣡\n");
                        else if(u_num==-2) printf("%c���㲻�����ڽӶ��㣡\n",u);
                        else printf("�����һ�ڽӶ������Ϊ%d\n",u_num+1);
                    }else printf("�ڽӱ����ڣ�\n");
                }


                else if(num==6)
                {
                    if(G.vernum){
                        printf("���붥��ؼ��ּ����ڽӶ���λ����!\n");
                        scanf("%c %d",&u,&a_num);
                        u_num=NextAdjVex(G,u,a_num-1);
                        if(u_num=-1) printf("�����ڶ��㣡\n");
                        else if(u_num==-2) printf("%c���㲻����λ��Ϊ%d���ڽӶ��㣡\n",u,a_num);
                        else printf("����%d�ڽӶ������Ϊ%d\n",a_num,u_num+1);
                    }else printf("�ڽӱ����ڣ�\n");
                }

                
                else if(num==7)
                {
                    if(G.vernum){
                        printf("������붥��ؼ��ּ�������λ����!\n");
                        scanf("%c %d",&vex.key,&vex.data);

                        if(InsertVex(&G,vex))printf("�������ɹ���\n");
                        else printf("����ʧ�ܣ�\n");

                    }else printf("�ڽӱ����ڣ�\n");
                }

                
                else if(num==8)
                {
                    if(G.vernum){
                        printf("����ɾ������Ĺؼ���!\n");
                        scanf("%c",&u);
                        if(DeleteVex(&G,u)==-1) printf("�����ڶ��㣡\n");
                        else printf("����%cɾ���ɹ�\n",u);
                    }else printf("�ڽӱ����ڣ�\n");
                }

                else if(num==9)
                {
                    if(G.vernum){
                        printf("�������ߵ������ؼ���!\n");
                        fflush(stdin);
                        scanf("%c%c",&u,&z);
                        if(InsertArc(&G,u,z)==-1) printf("�����ڱߣ�\n");
                        else printf("��%c%c����ɹ�\n",u,z);
                    }else printf("�ڽӱ����ڣ�\n");
                }

                else if(num==9)
                {
                    if(G.vernum){
                        printf("���붥��ؼ��ּ����ڽӶ���λ����!\n");
                        scanf("%c %d",&u,&z);
                        u_num=DeleteArc(&G,u,z);
                        if(u_num=-1) printf("�����ڶ��㣡\n");
                        else if(u_num==-2) printf("%c���㲻����λ��Ϊ%c���ڽӶ��㣡\n",u,z);
                        else printf("��%c%cɾ���ɹ���\n",u,z);
                    }else printf("�ڽӱ����ڣ�\n");
                }
            }     

        }
    }
    
    return 0;
}

int InitQueue(QList *Q){
    Q->first=NULL;
    Q->rear=NULL;
    return 1;
} //����һ���ն���

int QueueEmpty(QList Q){
    if(Q.first)return 1;
    else return 0;
} //�ж�һ�������Ƿ�Ϊ��

int EnQueue(QList *Q, int e){
    QNode* cur = (QNode*)malloc(sizeof(QNode));
    if(!Q->first){//�ն���
        cur->val=e;
        cur->next=cur;
        Q->first=cur;
        Q->rear=cur;

    }else{
        cur->val=e;
        cur->next=NULL;
        Q->rear->next=cur;
        Q->rear=cur;
    }
    return 1;
} //�����

int DeQueue(QList *Q,int *e){
    if(!Q->first)return 0;//�ն���
    else{
        *e=Q->first->val;//��ֵ
        QNode* tmp=Q->first;
        if(Q->first->next){//���зǿ�
            Q->first=Q->first->next;
            free(tmp);
        }else {//����ֻ��1Ԫ��
            Q->first=NULL;
            Q->rear=NULL;
        }
        return 1;
    }
} //������

//-------------------------
void print(bool *r){
    if(!*r){
        printf("Menu for Linear Table on Sequence Structure\n");
        printf("------------------------------------------------\n");
        printf(" 1. CreatGraph 8. DeleteVex \n");
        printf(" 2. DestroyGraph 9. InsertArc\n");
        printf(" 3. LocateVex 10. DeleteArc\n");
        printf(" 4. PutVex 11. DFSTraverse\n");
        printf(" 5. FirstAdjVex 12. BFSTraverse\n");
        printf(" 6. NextAdjVex 13. Write\n");
        printf(" 7. InsertVex 14. Read\n");
        printf(" 0.EXit\n");
        printf("------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0-16]:\n");
    }
}
int LocalVex(Graph *G,char u){
    for (int i = 0; i < G->vernum; i++)
    {
        if(G->vertices[i].key==u)return G->vertices[i].num;//�ҵ�����λ��
    }
    return -1;
}
int CreatGraph(Graph *G,char V[],char VR[][2]){
    int begin,end;
    ArcNode *p;//��ָ��
    //VNode q;//����ṹ

    for (int i = 0; i < G->vernum; i++)//���㴴��
    {
        G->vertices[i].num=i;//��Ŵ�0��ʼ 
        G->vertices[i].key=V[i];
        G->vertices[i].next=NULL;
        // printf("%d %c\n",i,V[i]);
    }

    for (int i = 0; i < G->arcnum; i++)
    {
        begin=LocalVex(G,VR[i][0]);//��Ѱ�ߵ����
        end=LocalVex(G,VR[i][1]);//��Ѱ�ߵ��յ�
        // printf("%d %c %d %c \n",begin,VR[i][0],end,VR[i][1]);
        p=G->vertices[begin].next;
        if(!p){
            ArcNode* edge=(ArcNode*)malloc(sizeof(AdjNode));
            edge->next=NULL;
            edge->val=end;
            G->vertices[begin].next=edge;
        }else
        {
            while (p->next)//�ҵ��ߵĽ�β
            {   
                p=p->next;
            }
            ArcNode* edge=(ArcNode*)malloc(sizeof(AdjNode));//������
            edge->next=NULL;
            edge->val=end;
            p->next=edge;//���ӱ�
        }
    
    }

 return 1;
}   //����ͼ

int DestroyList(ArcNode *arc){
    if(!arc->next){
        free(arc);
        arc=NULL;
    }
    else DestroyList(arc->next);

    return 1;

}//���ٶ���Ļ�����

int DestroyGraph(Graph *G){
    for (int i = 0; i < G->vernum; i++)
    {
        G->vertices[i].key='\0';
        G->vertices[i].num=0;
        G->vertices[i].data=0;
        DestroyList(G->vertices[i].next);
    }

    G->arcnum=0;
    G->vernum=0;
    
    return 1;
}//����


int LocateVex(Graph G,char u){//���Һ������ҵ��᷵��+1��ֵ
    for (int i = 0; i < G.vernum; i++)
    {
        if(G.vertices[i].key==u)
        return G.vertices[i].num+1;
    }
    return 0;


}//�ɹؼ��ֲ��Ҳ��Ҷ���λ��


int PutVex(Graph *G,char u,int value){

    int num=LocalVex(G,u);
    if(num){
        G->vertices[num].data=value;
        return 1;
    }else return 0;

}//����


int FirstAdjVex(Graph G,char u){
    int num=LocalVex(&G,u);

    if(num!=-1){
        if(G.vertices[num].next)return G.vertices[num].next->val;
        else return -2;
    }else{
        return -1;
    }


}//��õ�һ�ڽӵ�

int NextAdjVex(Graph G,char u,int w){
    int num=LocalVex(&G,u);
    ArcNode *p;

    if(num!=-1){
        if(G.vertices[num].next){
            p=G.vertices[num].next;
            for ( ; p!=NULL; p=p->next)
            {
                if(p->val==w)return p->val;
            }
        
            return -2;
        }
        else return -2;
    }else{
        return -1;
    }
}//�����һ�ڽӵ�


int InsertVex(Graph *G,VNode vex){
    G->vertices[G->vernum].key=vex.key;
    G->vertices[G->vernum].num=G->vernum;
    G->vertices[G->vernum].data=vex.data;
    G->vertices[G->vernum++].next=NULL;

    return 1;
    
}//���붥��


int DeleteVex(Graph *G,char u){
    int num=LocalVex(G,u);
    if(num=-1)return -1;
    ArcNode *q;
    for (int i = 0; i < G->vernum; i++)
    {
        if(i==num){
            G->vertices[i].num=0;
            G->vertices[i].data=0;
            G->vertices[i].key='\0';
            DestroyList(G->vertices[i].next);
        }else{
            if(G->vertices[i].next){
                for (ArcNode *p =G->vertices[i].next; p->next!=NULL; p=p->next)
                {
                    if(p->next->val=num){
                        q=p;
                        p=p->next;
                        q->next=p->next;
                        free(p);
                        break;
                    }
                }
            }
            
        }
        
    }

    if (num!=--G->vernum)//�ƶ�λ��
    {
       for (int i = num; i < G->vernum-num; i++)
       {
         G->vertices[i]=G->vertices[i+1];
       }
       
    }
    return 1;

}//ɾ������

int InsertArc(Graph *G,char u,char z){
    int begin=LocalVex(G,u);
    int end=LocalVex(G,z);

    if(begin!=-1&& end!=-1){
        ArcNode* p=(ArcNode*)malloc(sizeof(ArcNode));
        p->val=end;p->next=NULL;
        ArcNode* q;
        q=G->vertices[begin].next;
        G->vertices[begin].next=p;
        p->next=q;
        return 1;
    }else return -1;
}//���뻡(ͷ�巨)


int DeleteArc(Graph *G,char u,char z){
    int begin=LocalVex(G,u);
    int end=LocalVex(G,z);

    if(begin!=-1&& end!=-1){
        ArcNode *q;

        if(G->vertices[begin].next){
            for ( ArcNode* p= G->vertices[begin].next; p->next!=NULL; p=p->next)
            {
                if(p->next->val==end){
                    q=p;
                    p=p->next;
                    q->next=p->next;
                    free(p);
                    return 1;
                }
            }
           
        }
        return -2;

    }else return -1;

}//ɾ����