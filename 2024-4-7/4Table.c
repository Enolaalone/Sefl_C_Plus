#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define OVERFLOW -2
#define OK 1
#define NO 0
#define False -1
bool pr=false;
//---------------------队列-------------------
typedef struct QNode {
    int val;
    struct QNode* next;
}QNode;

typedef struct QList{
    QNode* first;
    QNode* rear;
}QList;
//------------------邻接表-0---------------------------
typedef struct ArcNode{
    int val;
    struct ArcNode*next;
}ArcNode;

typedef struct VNode {
    int num;
    int data;
    char key;
    ArcNode *next;
}VNode,AdjNode[100];

typedef struct Graph {
    int arcnum;
    int vnodenum;
    AdjNode vertices;
}Graph;
//------------队列函数------------

int InitQueue(QList *Q); //构造一个空队列
int QueueEmpty(QList Q); //判断一个队列是否为空
int EnQueue(QList *Q, int e); //入队列
int DeQueue(QList *Q,int *e); //出队列

//------邻接表函数----------------------
int CreatGraph(Graph *G,const char V[],char VR[][2]);//创建图
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

int main() {
    return 0;
}
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
int InitQueue(QList *Q){
    Q->first=NULL;
    Q->rear=NULL;
    return OK;
} //构造一个空队列

int QueueEmpty(QList Q){
    if(Q.first)return NO;
    else{
        int count;
        QNode *q=Q.first;
        for ( count = 0; q !=NULL ; ++count,q=q->next){}
        return count;
    };
}//判断一个队列是否为空

int EnQueue(QList *Q, int e){
    if(!Q->first){
        Q->first=Q->rear=(QNode*) malloc(sizeof (QNode));
        Q->first->next=NULL;
        Q->first->val=e;
        return OK;
    }
    else{
        Q->rear->next=(QNode*) malloc(sizeof (QNode));
        Q->rear=Q->rear->next;
        Q->rear->next=NULL;
        Q->rear->val=e;
        return OK;
    }

} //入队列

int DeQueue(QList *Q,int *e){
    if(!Q->first)return NO;
    else{
        QNode *q=Q->first->next;
        free(Q->first);
        Q->first=q;
        return OK;
    }
} //出队列
//------------------------------------
int LocalVel(Graph *G,char u){
    if(G){
        for (int i = 0; i < G->vnodenum; ++i) {
            if(G->vertices[i].key==u)
                return G->vertices[i].num;
        }
        return False;
    }else return OVERFLOW;
    
}
int CreatGraph(Graph *G,const char V[],char VR[][2]){
    int begin,end;
    for (int i = 0; i < G->vnodenum; ++i) {
        G->vertices[i].num=i;
        G->vertices[i].key=V[i];
        G->vertices[i].next=NULL;
    }

    for (int i = 0; i < G->arcnum; ++i) {
        begin= LocalVel(G,VR[i][0]);
        end= LocalVel(G,VR[i][1]);

        if((begin||end)!=False ) {
            ArcNode *p = G->vertices[begin].next;
            if (!G->vertices[begin].next) {
                p = (ArcNode *) malloc((sizeof(ArcNode)));
                if (!p) return OVERFLOW;
                p->val = end;
                p->next = NULL;
                G->vertices[begin].next = p;
                return OK;
            } else {
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = (ArcNode *) malloc((sizeof(ArcNode)));
                if (!p->next) return OVERFLOW;
                p->val = end;
                p->next = NULL;
                return OK;
            }
        }
    }
    return OK;
    
}//创建图

int DestroyGraph(Graph *G){
    for (int i = 0; i < G->vnodenum; ++i) {
        G->vertices[i].key='\0';
        G->vertices[i].data=0;
        G->vertices[i].num=0;
        DestroyList(G->vertices[i].next);
    }

    G->vnodenum=0;
    G->arcnum=0;
    return OK;
}//销毁
int DestroyList(ArcNode *arc){
    if(arc){
        DestroyList(arc->next);
        free(arc);
        arc=NULL;
        return OK;
    } else{
        free(arc);
        arc=NULL;
        return OK;
    }

}//销毁顶点的弧链表

int LocateVex(Graph G,char u){
    for (int i = 0; i < G.vnodenum; ++i) {
        if(G.vertices[i].key==u)
            return G.vertices[i].num+1;
    }
    return False;

}//由关键字查找查找顶点位序
int PutVex(Graph *G,char u,int value){
    int num= LocalVel(G,u);
    if(num!=False){
        return G->vertices[num].data=value;
    } else return False;
}//顶点赋值
int FirstAdjVex(Graph G,char u){
    int num= LocalVel(&G,u);
    if(num!=False){
        if(G.vertices[num].next)
            return G.vertices[num].next->val;
        else return OVERFLOW;
    } else return False;
}//获得第一邻接点
int NextAdjVex(Graph G,char u,int w){
    int num= LocalVel(&G,u);
    if(num!=False){
        if(G.vertices[num].next){
            ArcNode *p=G.vertices[num].next;
            for (;p!=NULL;p=p->next) {
                if(p->val==w)
                    return p->val;
            }
            return False;
        }

        else return OVERFLOW;
    } else return False;
}//获得下一邻接点