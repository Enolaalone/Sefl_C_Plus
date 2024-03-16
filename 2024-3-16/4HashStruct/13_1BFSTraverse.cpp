#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define OVERFLOW -2

typedef struct ArcNode//边
{
    int val;//序号
    struct ArcNode *next;//下一节点地址
}ArcNode;

typedef struct VNode//节点
{
    int num;//序号
    int data;//数据
    char key;//上级节点
    ArcNode* next;//Edge
}VNode,AdjNode[100];

typedef struct 
{
    AdjNode vertices;//邻接表数组
    int vernum,arcnum;//顶点数目，和边数

}Graph;

//-------队列结构-----------
typedef struct QNode//队列节点
{
    int val;
    struct QNode* next;
   
}QNode;

typedef struct QLNode
{
    struct QNode* first;//头
    struct QNode* rear;//尾巴
}QList;
void print(bool *r);
//------------队列函数------------

int InitQueue(QList *Q); //构造一个空队列
int QueueEmpty(QList Q); //判断一个队列是否为空
int EnQueue(QList *Q, int e); //入队列
int DeQueue(QList *Q,int *e); //出队列
//------邻接表函数----------------------
int CreatGraph(Graph *G,char V[],char VR[][2]);//创建图
int DestroyGraph(Graph *G);//销毁
int DestroyList(ArcNode *arc);//销毁顶点的弧链表
int LocateVex(Graph G,char u);//由关键字查找查找顶点位序
int PutVex(Graph *G,char u,int value);//顶点赋值
int FirstAdjVex(Graph G,char u);//获得第一邻接点
int NextAdjVex(Graph G,char u,int w);//获得下一邻接点
int InsertVex(Graph *G,VNode vex);//插入顶点
int DeleteVex(Graph *G,char u);//删除顶点
int InsertArc(Graph *G,char u,char z);//插入弧
int DeleteArc(Graph *G,char u,char z);//删除弧
int DFSTraverse(Graph G,char u);//深度优先遍历
char Locatekey(Graph G,int v);//由位序查找关键字
//int Locatekey2(Graph G,int v);//由位序查找序号
//int Locatehao(Graph G,char u);//由关键字查找序号
int BFSTraverse(Graph G, QList Q);//广度优先遍历
int Write(Graph G);//写入文件
int Read(Graph *G);//读取文件


bool pr=false;
int visited[100];//遍历查重

int main() {
    Graph M[100],G;
    char V[100],VR[100][2],E[5],u,z;
    int num,v_num,u_num,value,a_num;
    VNode vex;
    QList QL;//队列
    for (int i = 0; i < G.vernum; i++)
    {
        visited[i]=0;
    }
    while (1)
    {
        pr=false;//菜单初始化
        printf("输入需要对哪个邻接表操作（1-99）输入0退出\n");
        gets(E);
        v_num=atoi(E);
        if(!v_num)break;
        else if(v_num>99 || v_num<1)printf("不存在该邻接表!\n");
        else{
            G=M[v_num];
            while (1)
            {
                pr=false;//菜单初始化
                print(&pr);
                scanf("%d",&num);//菜单选择
                if(!num)break;
                else if(num==1){
                    printf("输入邻接表的顶点个数，及其边数\n");
                    scanf("%d %d",&G.vernum,&G.arcnum);
                    fflush(stdin);
                    printf("输入顶点的名称:\n");
                
                    for (int i = 0; i < G.vernum; i++)
                    {
                        scanf("%c",&V[i]);
                    }
                    fflush(stdin);
                    printf("输入边的名称:\n");
                    for (int i = 0; i < G.arcnum; i++)
                    {
                        scanf("%c",&VR[i][0]);
                        scanf("%c",&VR[i][1]);
                        getchar();
                    }

                    if(CreatGraph(&G,V,VR)){
                        printf("邻接表创建成功!\n");
                    }else printf("创建失败!\n");
                    
                }
                else if(num==2)
                {
                    if(G.vernum){
                        if(DestroyGraph(&G))printf("邻接表清除成功！\n");
                        else printf("失败！\n");
                    }else printf("邻接表不存在！\n");
                }

                else if(num==3)
                {
                    if(G.vernum){
                        printf("输入顶点关键字!\n");
                        fflush(stdin);
                        scanf("%c",&u);
                        u_num=LocateVex(G,u);
                        if(u_num)printf("顶点的序号为%d\n",u_num);
                        else printf("顶点不存在！\n");
                    }else printf("邻接表不存在！\n");
                }

                else if(num==4)
                {
                    if(G.vernum){
                        printf("输入顶点关键字以及赋值数据!\n");
                        fflush(stdin);
                        scanf("%c %d",&u,&value);

                        if(PutVex(&G,u,value))printf("顶点赋值成功！\n");
                        else printf("赋值失败！\n");
                    }else printf("邻接表不存在！\n");
                }

                else if(num==5)
                {
                    if(G.vernum){
                        printf("输入顶点关键字!\n");
                        fflush(stdin);
                        scanf("%c",&u);
                        u_num=FirstAdjVex(G,u);
                        if(u_num=-1) printf("不存在顶点！\n");
                        else if(u_num==-2) printf("%c顶点不存在邻接顶点！\n",u);
                        else printf("顶点第一邻接顶点序号为%d\n",u_num+1);
                    }else printf("邻接表不存在！\n");
                }


                else if(num==6)
                {
                    if(G.vernum){
                        printf("输入顶点关键字及其邻接顶点位置序!\n");
                        fflush(stdin);
                        scanf("%c %d",&u,&a_num);
                        u_num=NextAdjVex(G,u,a_num-1);
                        if(u_num=-1) printf("不存在顶点！\n");
                        else if(u_num==-2) printf("%c顶点不存在位置为%d的邻接顶点！\n",u,a_num);
                        else printf("顶点%d邻接顶点序号为%d\n",a_num,u_num+1);
                    }else printf("邻接表不存在！\n");
                }

                
                else if(num==7)
                {
                    if(G.vernum){
                        printf("输入插入顶点关键字及其数据位置序!\n");
                        fflush(stdin);
                        scanf("%c %d",&vex.key,&vex.data);

                        if(InsertVex(&G,vex))printf("顶点插入成功！\n");
                        else printf("插入失败！\n");

                    }else printf("邻接表不存在！\n");
                }

                
                else if(num==8)
                {
                    if(G.vernum){
                        printf("输入删除顶点的关键字!\n");
                        fflush(stdin);
                        scanf("%c",&u);
                        if(DeleteVex(&G,u)==-1) printf("不存在顶点！\n");
                        else printf("顶点%c删除成功\n",u);
                    }else printf("邻接表不存在！\n");
                }

                else if(num==9)
                {
                    if(G.vernum){
                        printf("输入插入边的两个关键字!\n");
                        fflush(stdin);
                        scanf("%c%c",&u,&z);
                        if(InsertArc(&G,u,z)==-1) printf("不存在边！\n");
                        else printf("边%c%c插入成功\n",u,z);
                    }else printf("邻接表不存在！\n");
                }

                else if(num==10)
                {
                    if(G.vernum){
                        printf("输入顶点关键字及其邻接顶点位置序!\n");
                        fflush(stdin);
                        scanf("%c %d",&u,&z);
                        u_num=DeleteArc(&G,u,z);
                        if(u_num=-1) printf("不存在顶点！\n");
                        else if(u_num==-2) printf("%c顶点不存在位置为%c的邻接顶点！\n",u,z);
                        else printf("边%c%c删除成功！\n",u,z);
                    }else printf("邻接表不存在！\n");
                }

                else if(num==11)
                {
                    if(G.vernum){
                        printf("输入第一个遍历的关键字!\n");
                        fflush(stdin);
                        scanf("%c",&u);
                        if(DFSTraverse(G,u)==-1)printf("顶点不存在！\n");

                        for (int i = 0; i < G.vernum; i++)
                            DFSTraverse(G,G.vertices[i].key);
                        for(int i=0;i<G.vernum;++i)
                            visited[i]=0;

                    }else printf("邻接表不存在！\n");
                }

                else if(num==12)
                {
                    if(G.vernum){
                        BFSTraverse(G,QL);
                    }else printf("邻接表不存在！\n");
                }

                else if(num==13)
                {
                    if(G.vernum){
                        Write(G);
                    }else printf("邻接表不存在！\n");
                }

                else if(num==14)
                {
                    Read(&G);
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
} //构造一个空队列

int QueueEmpty(QList Q){
    if(Q.first)return 0;
    else return 1;
} //判断一个队列是否为空

int EnQueue(QList *Q, int e){
    QNode* cur = (QNode*)malloc(sizeof(QNode));
    if(!Q->first){//空队列
        cur->val=e;
        cur->next=NULL;

        Q->first=cur;
        Q->rear=cur;

    }else{
        cur->val=e;
        cur->next=NULL;
        Q->rear->next=cur;
        Q->rear=cur;
    }
    return 1;
} //入队列

int DeQueue(QList *Q,int *e){
    if(!Q->first)return 0;//空队列
    else{
        *e=Q->first->val;//赋值
        QNode* tmp=Q->first;
        if(!Q->first->next){//队列只有一圆
            Q->first=NULL;
            Q->rear=NULL;
        }else {//非空
            Q->first=Q->first->next;
            free(tmp);
        }
        return 1;
    }
} //出队列

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
        printf("请选择你的操作[0-16]:\n");
    }
}
int LocalVex(Graph *G,char u){
    for (int i = 0; i < G->vernum; i++)
    {
        if(G->vertices[i].key==u)return G->vertices[i].num;//找到返回位置
    }
    return -1;
}
int CreatGraph(Graph *G,char V[],char VR[][2]){
    int begin,end;
    ArcNode *p;//边指针
    //VNode q;//顶点结构

    for (int i = 0; i < G->vernum; i++)//顶点创建
    {
        G->vertices[i].num=i;//序号从0开始 
        G->vertices[i].key=V[i];
        G->vertices[i].next=NULL;
        // printf("%d %c\n",i,V[i]);
    }

    for (int i = 0; i < G->arcnum; i++)
    {
        begin=LocalVex(G,VR[i][0]);//找寻边的起点
        end=LocalVex(G,VR[i][1]);//找寻边的终点
        // printf("%d %c %d %c \n",begin,VR[i][0],end,VR[i][1]);
        p=G->vertices[begin].next;
        if(!p){
            ArcNode* edge=(ArcNode*)malloc(sizeof(AdjNode));
            edge->next=NULL;
            edge->val=end;
            G->vertices[begin].next=edge;
        }else
        {
            while (p->next)//找到边的结尾
            {   
                p=p->next;
            }
            ArcNode* edge=(ArcNode*)malloc(sizeof(AdjNode));//创建边
            edge->next=NULL;
            edge->val=end;
            p->next=edge;//连接边
        }
    
    }

 return 1;
}   //创建图

int DestroyList(ArcNode *arc){
    if(!arc->next){
        free(arc);
        arc=NULL;
    }
    else DestroyList(arc->next);

    return 1;

}//销毁顶点的弧链表

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
}//销毁


int LocateVex(Graph G,char u){//查找函数，找到会返回+1的值
    for (int i = 0; i < G.vernum; i++)
    {
        if(G.vertices[i].key==u)
        return G.vertices[i].num+1;
    }
    return 0;


}//由关键字查找查找顶点位序


int PutVex(Graph *G,char u,int value){

    int num=LocalVex(G,u);
    if(num){
        G->vertices[num].data=value;
        return 1;
    }else return 0;

}//顶点


int FirstAdjVex(Graph G,char u){
    int num=LocalVex(&G,u);

    if(num!=-1){
        if(G.vertices[num].next)return G.vertices[num].next->val;
        else return -2;
    }else{
        return -1;
    }


}//获得第一邻接点

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
}//获得下一邻接点


int InsertVex(Graph *G,VNode vex){
    G->vertices[G->vernum].key=vex.key;
    G->vertices[G->vernum].num=G->vernum;
    G->vertices[G->vernum].data=vex.data;
    G->vertices[G->vernum++].next=NULL;

    return 1;
    
}//插入顶点


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

    if (num!=--G->vernum)//移动位置
    {
       for (int i = num; i < G->vernum-num; i++)
       {
         G->vertices[i]=G->vertices[i+1];
       }
       
    }
    return 1;

}//删除顶点

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
}//插入弧(头插法)


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

}//删除弧


int DFSTraverse(Graph G,char u){
    char z;
    int start=LocalVex(&G,u);
    
    if(start!=-1){
        if(visited[start]) return 1;
        printf("%d %c %d\n",G.vertices[start].num,G.vertices[start].key,G.vertices[start].data);
        visited[start]=1;
        for (ArcNode *p=G.vertices[start].next; p!=NULL; p=p->next)
        {
            z=Locatekey(G,p->val);
            DFSTraverse(G,z);
        }
        return 1;

    }else return -1;
}//深度优先遍历

char Locatekey(Graph G,int v){
    return G.vertices[v].key;
}//由位序查找关键字

int BFSTraverse(Graph G, QList Q){
    int num;
    for (int i = 0; i < G.vernum; i++)
    {
        if(!visited[i]){
            EnQueue(&Q,i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q,&num);
                if(!visited[num]){
                    printf("%d %c %d\n",G.vertices[num].num,G.vertices[num].key,G.vertices[num].data);
                    visited[num]=1;
                    for (ArcNode* p = G.vertices[num].next; p!=NULL; p=p->next)
                    {
                        if(!visited[p->val])
                        EnQueue(&Q,p->val);       
                    }
                }
            }

        }
        
    }
    for (int i = 0; i < G.vernum; i++)
    {
        visited[i]=0;
    }
    return 1;

}//广度优先遍历


int Write(Graph G){
  
    char name[20];
    fflush(stdin);
    printf("输入文件名称！\n");
    scanf("%s",name);
    FILE *pf=fopen(name,"w");

    fprintf(pf,"%d,%d\n",G.vernum,G.arcnum);

    for (int i = 0; i < G.vernum; i++)
    {
        fprintf(pf,"%c,%d,%d\n",G.vertices[i].key,G.vertices[i].num,G.vertices[i].data);


    }
    for (int i = 0; i < G.vernum; i++)
    {
        for (  ArcNode*p=G.vertices[i].next; p!=NULL; p=p->next)
        {
            fprintf(pf,"%d-%d",G.vertices[i].num,p->val);
            fprintf(pf,"\n");
        }
    }
    
    fclose(pf);
    return 1;
}//写入文件

int Read(Graph *G){
    int n1,n2;
    char name[20],word[30];
    fflush(stdin);
    printf("输入文件名称！\n");
    scanf("%s",name);
    FILE *fp=fopen(name,"r");
    fgets(word,sizeof(word),fp);
    sscanf(word,"%d,%d",&G->vernum,&G->arcnum);

    for (int i = 0; i < G->vernum; i++)
    {
        fgets(word,sizeof(word),fp);
        sscanf(word,"%c,%d,%d",&G->vertices[i].key,&G->vertices[i].num,&G->vertices[i].data);
    }

    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        sscanf(word,"%d-%d",&n1,&n2);
        n1+=49;n2+=49;
        InsertArc(G,(char)n1,(char)n2);
    }
    fclose(fp);
    return 1;


}//读取文件