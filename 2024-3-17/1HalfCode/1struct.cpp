#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x='/';
//int q=0;
typedef struct Stack{//ջ
    int point;
    int data[200];
}Stack;

void push(Stack* p,int s){//��ջ
    p->point++;
    p->data[p->point]=s;
}
int pop(Stack* p){//��ջ
    if(p->point==-1)return -1;
    else{
        p->point--;
        return p->data[p->point+1];
    }
}


typedef struct Node{
    char name;
    int weight;

    int parent;
    int l_kid;
    int r_kid;

    int nun;
}Node;



