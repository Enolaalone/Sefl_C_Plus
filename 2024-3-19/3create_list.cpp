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
    char name[8];
    int weight;

    int parent;
    int l_kid;
    int r_kid;

    int num;
}Node;

Node* reading(Node *nodes,int* n){//数组 读取文件 长度
    char word[20],names[20]="s1.txt";//权重文件名称
    // scanf("%s",names);
    FILE *fp=fopen(names,"r");
    nodes=(Node*)malloc(sizeof(Node));
    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        nodes=(Node*)realloc(nodes,((*n)+1)*sizeof(Node));
        sscanf(word,"%s %d",nodes[*n].name,&nodes[*n].weight);
        (*n)++;
    }
    nodes=(Node*)realloc(nodes,((*n)+1)*sizeof(Node));
    strcpy(nodes[*n].name,"\n");
    nodes[*n].weight=1521;
    (*n)++;
    nodes=(Node*)realloc(nodes,(2*(*n)-1)*sizeof(Node));

    printf("%d",*n);
    fclose(fp);
    return nodes;

}

void create_list(Node nodes[],int n){//构建树 初始化
    int k=2*n-1;//节点数
    for (int i = 0; i < k; i++)
    {
        if (i>=n)
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
       if(nodes[i].weight<s[0] && nodes[i].parent==-1){//更小而且未访问过
            s[2]=s[0]; 
            s[0]=nodes[i].weight;
     
            //记录位置
            s[3]=s[1];
            s[1]=i;

            // printf("%s %d %d %d %d\n",nodes[i].name,s[0],s[1],s[2],s[3]);
       }
       else if (nodes[i].weight>=s[0] && nodes[i].weight<s[2]&&nodes[i].parent==-1)
       {
            s[2]=nodes[i].weight;
            s[3]=i;
       }
       
    }
}

void connect(Node nodes[],int n){//连接
    for (int i = n; i < 2*n-1; i++)//排除n个叶子节点外
    {
        int s[4]={0,0,0,0};//值 位置
        compare(nodes,s,i);

        nodes[i].l_kid=s[1];
        nodes[i].r_kid=s[3];
        nodes[i].weight=s[0]+s[2];

        nodes[s[1]].parent=i;
        nodes[s[3]].parent=i;
    }
}

void code(Node nodes[],int num,Stack *ps,FILE *pf){
    if(nodes[num].parent==-1){//code写入
        fprintf(pf,"%s\t",nodes[num].name);
        for ( ; ps->point!=-1; )
            fprintf(pf,"%d",pop(ps));
        fprintf(pf,"\n");
        return;
    }
    if(nodes[num].parent!=-1){
    if(num==nodes[nodes[num].parent].l_kid) push(ps,0);
    else if(num==nodes[nodes[num].parent].r_kid) push(ps,1);
    code(nodes,nodes[num].parent,ps,pf);
    }

}


void stack_code(Node nodes[],int n){
    Stack *ps=(Stack*)malloc(sizeof(Stack));
    ps->point=-1;
    
    char name[20]="code.txt";
    // gets(name);
    FILE*pf=fopen(name,"w");

    for (int i = 0; i < n; i++)
        code(nodes,i,ps,pf);
    fclose(pf);
}

int main(){

    int *n=(int*)malloc(sizeof(int));*n=0;
    Node *nodes;
    nodes=reading(nodes,n);
    // for (int i = 0; i < (*n); i++)
    // {
    //     printf("%s\t%d\t%d\n",nodes[i].name,nodes[i].weight,nodes[i].parent);
    // }
    

    create_list(nodes,*n);
    //     for (int i = 0; i < 2*(*n)-1; i++)
    // {
    //     printf("%s\t%d\t%d\n",nodes[i].name,nodes[i].weight,nodes[i].parent);
    // }

    
    connect(nodes,*n);

    FILE*pf=fopen("k.txt","w");

    //     for (int i = 0; i < 2*(*n)-1; i++)
    // {
    //     fprintf(pf,"%s\t%d\t%d\n",nodes[i].name,nodes[i].weight,nodes[i].parent);
    // }
    fclose(pf);
    stack_code(nodes,*n);


    free(n);
    

}