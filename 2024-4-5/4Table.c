#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define OVERFLOW -2
#define OK 1
#define NO 0
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