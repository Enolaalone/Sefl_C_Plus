
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

//--------------------主函数----------------------

int main(){
    QList Q;//队列
    int visited[100];//记录访问的数组
    Graph G;//邻接表

    InitQueue(&Q);//空队列
    for (int i = 0; i < G.vernum; i++)//数组初始化
    {
        visited[i]=0;
    }
    

    //=========广度搜索==============
    int num;
    for (int i = 0; i < G.vernum; i++)//
    {
        if(!visited[i])
        EnQueue(&Q,i);

        while (!QueueEmpty(Q))//队列不为空
        {
            DeQueue(&Q,&num);//出队列（记得标记已经访问）
            if(!visited[num]){
                printf("%c\n",G.vertices[num].key);
                visited[num]=true;//-----------标记已经访问
                for (ArcNode* p = G.vertices[num].next; p!=NULL; p=p->next)
                {
                    if(visited[p->val])
                    EnQueue(&Q,p->val);//入队
                }
                
            }
        }
        
    }
    


}
