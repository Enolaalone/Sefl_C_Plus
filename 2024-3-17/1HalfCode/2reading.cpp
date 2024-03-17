#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int nun;
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




