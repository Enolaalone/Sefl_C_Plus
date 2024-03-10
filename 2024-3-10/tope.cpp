#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 100
bool is[256];
//Hash数据结构
typedef struct aList{//链
    int num;//数组位置
    struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//可入度
    char name[25];//项目名称
    L next;//链
}AL,*ALP;
//----------------栈-------------------
typedef struct Stack{
    int pointer;//指针
    ALP data[50];//数据
}Stack,*list;

void push(list s,ALP c){//地址入栈
    s->pointer++;
    s->data[s->pointer]=c;
}

ALP pop(list s){//返回地址
    if(s->pointer==-1) return NULL;
    else{
        s->pointer--;
        return s->data[s->pointer+1];
    }
}
void CreateEdge(int forward,int backward,AL p[]){
    //建立表单
    L ls=(L)malloc(sizeof(aList));
    if(!ls) exit(-2);
    ls->num=backward;
    //头插法
    ls->next=p[forward].next;
    p[forward].next=ls;

}
void Read(AL p[]){
    char word[30];
    FILE*fp=fopen("p01.txt","r");
    if(!fp) exit(-1);
//------------------------
    char *pr=NULL,*token=NULL;
    char ltr[]=",",letter;//分割的字符串
    while (fgets(word,sizeof(word),fp)!=NULL)
    {//读取第一个字符
        token=strtok_r(word,ltr,&pr);
        // printf("%s\n",token);
        int k=(int)(token[0]-'A');
        if(token[0]>='A' && token[0]<='Z' ){//命名
                p[k].name[0]=token[0];//名称
                p[k].name[1]='\0';//结束
        } else continue;//非字符结束
        letter=token[0];
        //读取剩余分割元素
        token=strtok_r(NULL,ltr,&pr);
        while (token!=NULL)
        {
            // printf("%s\n",token);
            if(token[0]>='A' && token[0]<='Z')
            CreateEdge(token[0]-'A',letter-'A',p);
            p[letter-'A'].num++;
            token=strtok_r(NULL,ltr,&pr);
            }
        
    }
    fclose(fp); 
}

void print(AL p[],int *i){
    //------------------打印--------------------
    printf("序号\t可入度\t名称\t后续项目\n");
    while(p[*i].name[0]>='A'&& p[*i].name[0]<='Z'){
        printf("%d\t%d\t%s\t",*i,p[*i].num,p[*i].name);
        for (L j =p[*i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("^\n");
        (*i)++;
    }
    printf("顶点数量：%d\n",*i);
    //---------------------------------------
}
int main(){
    //邻接表初始化
    ALP p=(ALP)malloc(M*sizeof(AL));
    for (int i = 0; i < M; i++)
    {
        p[i].next=NULL;
        p[i].num=0;
    }
    //---------------------
    int i=0;
    Read(p);
    print(p,&i);
    
}