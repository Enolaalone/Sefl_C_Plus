#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>//INT_MAX

//Hash数据结构
typedef struct aList{//链
    int num;//数组位置
    struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//可入度
    char name[5];//项目名称
    int pass;//是否遍历--------------------------------------------------------
    int weight;//时间----------------------------------------------------------------------------------------------------
    L next;//链
}AL,*ALP;

//dijkstra求最短路径
void dijkstra(AL p[],int pre[],int dtc[],int source,int i){//邻接表，前驱数组，距离数组，源，邻接表数组长度
    bool visited[i];//是否访问节点
    for (int j = 0; j < i; j++)//初始化
    {
        visited[j]=false;//未访问
        pre[j]=-1;//无父节点
        dtc[j]=INT_MAX;//最大路径
    }
    dtc[source]=0;//源头A
    int n;//路径数组中 最小序号
    for (int j = 0; j < i-1; j++)
    {
        int min=INT_MAX;//寻找路径数组 源头出发最小路径长度
        for (int k = 0; k < i; k++)//遍历路径数组所有元素
        {
            if(dtc[k]<min && !visited[k]){//小于min路径长度 ，且未访问
                n=k;//找到序号
                min=dtc[n];//找到距离
            }

        }

        visited[n]=true;//标记访问

        L ql=p[n].next;//邻接链
        while (ql)
        {
            if(!visited[ql->num] && dtc[n]+p[n].weight<dtc[ql->num]){//如果未访问，且当前最短路径+时间权重小于节点对应路径长度
                dtc[ql->num]=dtc[n]+p[n].weight;//更新邻接路径
                pre[ql->num]=n;//标记前驱节点
            }
            ql=ql->next;//遍历下一邻接链
        }

    }

}

//路径打印
void PrintWay(int pre[],AL p[],int n){//前驱数组，邻接表，序号
    if (pre[n]==-1)//源结点
    {
        printf("%s",p[n].name);
        return;
    }

    PrintWay(pre,p,pre[n]);//递归打印路径,递归到源头A->...
    printf("->%s",p[n].name);
    
}