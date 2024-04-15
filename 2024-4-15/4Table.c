#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define OVERFLOW -2
#define OK 1
#define NO 0
#define False -1

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
void print( bool *r);

bool pr=false;
int visited[100];//遍历查重
int main() {
    Graph M[100],G;
    int g_num,num,locate,value;
    char E[5],V[100],VR[100][2];
    while(1){
        printf("输入需要操作的邻接表（1-99），or按0退出！");
        scanf("%d",&g_num);
        if(!g_num)break;
        else if(g_num<1||g_num>99){
            printf("错误！请重新输入");
            continue;
        } else{
            G=M[g_num];
            while(1){
                pr=false;
                print(&pr);
                gets(E);
                num= atoi(E);
                if(!num)break;
                else if(num<1||num>16){
                    printf("输入错误请重新输入！\n");
                    continue;
                }
                else if(num==1) {
                    if (G.vnodenum != 0) {
                        printf("邻接表已存在!\n");
                        break;
                    }
                    fflush(stdin);
                    printf("输入邻接表顶点个数以及边条数\n");
                    scanf("%d %d", &G.vnodenum, &G.arcnum);

                    for (int i = 0; i < G.vnodenum; ++i) {
                        printf("输入顶点名称\n");
                        scanf("%c", &V[i]);
                        G.vertices[i].data = 0;
                    }

                    for (int i = 0; i < G.arcnum; ++i) {
                        printf("输入边名称\n");
                        scanf("%c %c", &VR[i][0], &VR[i][1]);
                    }
                    if (CreatGraph(&G, V, VR)) {
                        printf("邻接表创建成功\n");
                    }
                }

                else if(num==2){
                    if (G.vnodenum==0){
                        printf("邻接表不存在或已经销毁！");
                        break;
                    }
                    if(DestroyGraph(&G)){
                        printf("邻接表销毁成功！\n");
                    }

                }

                else if(num==3){
                    if (G.vnodenum==0){
                        printf("邻接表不存在！");
                        break;
                    }
                    char *e=(char*) malloc(sizeof (char));
                    printf("输入需要查询的元素!!\n");
                    scanf("%c",e);
                    locate= LocateVex(G,*e);

                    if(locate!= false){
                        locate++;
                        printf("%c的位置在%d\n",*e,locate);
                    }
                    free(e);
                    e=NULL;
                }

                else if(num==4){
                    if (G.vnodenum==0){
                        printf("邻接表不存在！");
                        break;
                    }
                    char *e=(char*) malloc(sizeof (char));
                    printf("输入需要输入值的顶点以及对应的值\n");
                    scanf("%c %d",e,&value);
                    if(PutVex(&G,*e,value)) {
                        printf("值存入成功!!!\n");
                    }

                }
            }
        }

    }

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
        *r=true;
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
    if(!Q->first) {
        e=NULL;
        return NO;
    }
    else{
        QNode *q=Q->first->next;
        *e=Q->first->val;
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

int InsertVex(Graph *G,VNode vex){
    G->vertices[G->vnodenum].data=vex.data;
    G->vertices[G->vnodenum].key=vex.key;
    G->vertices[G->vnodenum].num=vex.num;
    G->vertices[G->vnodenum].next=vex.next;
    G->vnodenum++;
    return OK;

}

int DeleteVex(Graph *G,char u){
    int num= LocalVel(G,u);
    if(num== False)return False;


    for (int i = 0; i < G->vnodenum; ++i) {
        if(i==num){
            G->vertices[i].key='\0';
            G->vertices[i].data=0;
            G->vertices[i].num=0;
            DestroyList(G->vertices[num].next);
        } else{
            ArcNode *p=G->vertices[i].next,*q;
            if(p&&p->val==num){
                free(p);
                G->vertices[num].next=NULL;
                continue;
            }
            if(p){
                for (;p!=NULL; p=p->next) {
                    if(p->val==num){
                        q->next=p->next;
                        free(p);
                        break;
                    }
                    q=p;
                }
            }
        }
    }
    return OK;
}

int InsertArc(Graph *G,char u,char z){
    int begin= LocalVel(G,u);
    int end= LocalVel(G,z);
    if(begin!=False&&end!=False){
        ArcNode *p=G->vertices[begin].next;
        if(p){
            while (!p->next)p=p->next;
            p->next=(ArcNode*) malloc(sizeof (ArcNode));
            if(!p->next)return OVERFLOW;
            p=p->next;
            p->next=NULL;
            p->val=end;
        } else{
            p=(ArcNode*) malloc(sizeof (ArcNode));
            if(!p)return OVERFLOW;
            G->vertices[begin].next=p;
            p->next=NULL;
            p->val=end;
        }
        return OK;
    }return False;
}

int DeleteArc(Graph *G,char u,char z){
    int begin= LocalVel(G,u);
    int end= LocalVel(G,z);
    if(begin!=False&&end!=False){
        ArcNode *p=G->vertices[begin].next,*q;
        if(p&&p->val==end){
            free(p);
            G->vertices[begin].next=NULL;
            return OK;
        }

        else if(p){
            for (; p!=NULL ; q=p,p=p->next) {
                if(p->val==end){
                    q->next=p->next;
                    free(p);
                    return OK;
                }
            }
        } else return False;

    } return False;
}

int DFSTraverse(Graph G,char u){
    int start= LocalVel(&G,u);
    if(start!=False){
        if(!visited[start]){
            printf("%d %d %c \n",G.vertices[start].num,G.vertices[start].data,G.vertices[start].key);
            visited[start]=1;
            for (ArcNode *p=G.vertices[start].next; p!=NULL; p=p->next) {
                DFSTraverse(G,G.vertices[p->val].key);
            }
            return OK;

        } else return False;
    } return False;
}

char Locatekey(Graph G,int v){
    return G.vertices[v].key;
}//由位序查找关键字

int BFSTraverse(Graph G, QList Q){
    int num;

    for (int i = 0; i < G.vnodenum; ++i) {
        if(!visited[i]){
            EnQueue(&Q,i);

            while (!QueueEmpty(Q)){
                DeQueue(&Q,&num);
                printf("%d %d %c \n",G.vertices[num].num,G.vertices[num].data,G.vertices[num].key);
                visited[num]=1;

                for (ArcNode *p=G.vertices[num].next; p!=NULL ; p=p->next) {
                    if(!visited[p->val])
                        EnQueue(&Q,p->val);
                }
            }
        }
    }

    for (int i = 0; i < G.vnodenum; ++i) {
        visited[i]=0;
    }
    return OK;
}
int Write(Graph G){
    char name[20];
    printf("输入文件名字\n");
    scanf("%s",name);
    FILE *pf= fopen(name,"w");
    if(!pf)return OVERFLOW;
    fprintf(pf,"%d,%d\n",G.vnodenum,G.arcnum);

    for (int i = 0; i < G.vnodenum; ++i) {
        fprintf(pf,"%c,%d,%d\n",G.vertices[i].key,G.vertices[i].num,G.vertices[i].data);
    }

    for (int i = 0; i < G.arcnum; ++i) {
        ArcNode *p=G.vertices[i].next;
        while(p){
            fprintf(pf,"%c-%c\n",G.vertices[i].key,G.vertices[p->val].key);
            p=p->next;
        }
    }
    return OK;
}

int Read(Graph *G){
    char name[20],word[20],begin,end;
    printf("输入文件名称\n");
    scanf("%s",name);
    FILE*fp= fopen(name,"r");
    if(!fp)return OVERFLOW;

    fgets(word,sizeof (word),fp);
    sscanf(word,"%d,%d\n",&G->vnodenum,&G->arcnum);

    for (int i = 0; i < G->vnodenum; ++i) {
        fgets(word,sizeof (word),fp);
        sscanf(word,"%c,%d,%d\n",&G->vertices[i].key,&G->vertices[i].num,&G->vertices[i].data);
    }
    for (int i = 0; i < G->arcnum; ++i) {
        fgets(word,sizeof (word),fp);
        sscanf(word,"%c-%c\n",&begin,&end);
        InsertArc(G,begin,end);
    }
    return OK;
}