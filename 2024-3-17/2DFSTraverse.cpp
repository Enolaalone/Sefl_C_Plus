
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

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


//--------------------主函数----------------------
int DfS(Graph *G,int i){
    if(!visited[i])  return 0;

    printf("%d %c",G->vertices[i].data,G->vertices[i].key);
    visited[i]=1;//标记正在访问

    for (ArcNode* p = G->vertices[i].next; p!=NULL; p=p->next)
    {
        if (!visited[p->val]){//未访问
            DfS(G,p->val);
            visited[i]=-1;//访问结束
        }
        //else return p->val;//返回环的位置
    }
    // visited[i]=-1;

    return 1;
}


int visited[100];//记录访问的数

int main(){

    Graph G;//邻接表

    for (int i = 0; i < G.vernum; i++)//数组初始化
    {
        visited[i]=0;
    }
    

    //=========深度搜索==============

    for (int i = 0; i < G.vernum; i++)//防止漏掉
    {
        DfS(&G,i);
    }
    



}
