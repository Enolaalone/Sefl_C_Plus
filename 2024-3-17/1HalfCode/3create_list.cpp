#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>//INT_MAX

char x='/';
//int q=0;
typedef struct Stack{//栈
    int point;
    int data[200];
}Stack;

void push(Stack* p,int s){//入栈
    p->point++;
    p->data[p->point]=s;
}
int pop(Stack* p){//出栈
    if(p->point==-1)return -1;
    else{
        p->point--;
        return p->data[p->point+1];
    }
}


typedef struct Node{
    char name[5];
    int weight;

    int parent;
    int l_kid;
    int r_kid;

    int num;
}Node;

int reading(Node nodes[],char names[],int n){//数组 读取文件 长度
    char word[20];
    FILE *fp=fopen(names,"r");
    while (fgets(word,sizeof(word),fp))
    {
        sscanf(word,"%s %d",nodes[n].name,nodes[n].weight);
        n++;
    }
    strcpy(nodes[n].name,"\n");
    nodes[n].weight=1521;
    n++;
    fclose(fp);
    return n;
}

void create_list(Node nodes[],int n){//构建树 初始化
    int k=2*n-1;//节点数
    for (int i = 0; i < k; i++)
    {
        if (i>n)
        {
            strcpy(nodes[i].name,"\0");
            nodes[i].weight=0;
        }
        nodes[i].l_kid=-1;
        nodes[i].r_kid=-1;
        nodes[i].parent=-1;
        nodes[i].num=i;
    }
}


void swap(int *s1,int *s2){//交换
    int t;
    t=*s1;
    *s1=*s2;
    *s2=t;
}


void compare(Node nodes[],int s[],int n){//寻找最小和次小
     s[0]=INT_MAX,s[2]=INT_MAX;//最大
    for (int i = 0; i < n; i++)
    {
       if(nodes[i].weight<s[0]){
            s[0]=nodes[i].weight;
            s[2]=s[0]; 
            //记录位置
            s[3]=s[1];
            s[1]=nodes[i].num;
       }
    }
}
