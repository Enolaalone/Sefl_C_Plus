#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define M 100

bool is[256];

typedef struct alist
{
    int num;
    struct alist* next;
}*L;

typedef struct AOVList
{
    int num;
    char name[5];
    int weight;
    int pass;
    L next;
}AL,*ALP;

typedef struct Stack
{
    int pointer;
    ALP data[50];
}Stack,*list;

void push(list s,ALP c){
    s->pointer++;
    s->data[s->pointer]=c;
}

ALP pop(list s){
    if(s->pointer==-1) return NULL;
    else{
        s->pointer--;
        return s->data[s->pointer+1];
    }
}

void Read(char *word,AL p[]){
    int i=1,k,in_num=0;
    k=(int)(word[0]-'A');

    if(word[0]>='A' && word[0]<='Z'){
        if(!is[word[0]]){
            p[k].name[0]=word[0];
            p[k].name[1]='\0';
            is[word[0]]=true;
        }

    }    


    while (word[i]!='\0')
    {
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){
                p[k].name[0]=word[0];
                p[k].name[1]='\0';
                is[word[i]]=true;
            }

            if(p[k].next==NULL){
                p[k].next=(L)malloc(sizeof(struct alist));
                p[k].next->num=(int)(word[0]-'A');
                p[k].next->next=NULL;

            }else{
                L L_p=p[k].next;
                while(1){
                    if(L_p->next!=NULL) L_p=L_p->next;
                    else{
                        L_p->next=(L)malloc(sizeof(struct alist));
                        L_p->next->num=(int)(word[0]-'A');
                        L_p->next->next=NULL;
                        break;
                    }
                }
            }

        } 
        else if(word[i]>='0' && word[i]<='9'){
            p[(int)(word[0]-'A')].weight=p[(int)(word[0]-'A')].weight+(int)(word[0]-'A');
        }
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
}

void print(AL p[],int *i){
    printf("序号\t可入度\t名称\t时间权重\t后续链");
    while (p[*i].name[0]>='A' && p[*i].name[0]<='Z')
    {
        printf("%d\t%d\t%s\t%d",*i,p[*i].num,p[*i].name[0],p[*i].weight);
        for (L j = p[*i].next; j !=NULL; j=j->next)
        {
            printf("->%d",j->num);
        }
        printf("^\n");
        
    }
    
    
}
bool Compare(AL p[],int i){
    int put_l=0;
    ALP ap0;

    list ps=(list)malloc(sizeof(Stack));
    ps->pointer=-1;

    for (int j = 0; j < i; j++)
    {
        if(p[j].num==0)push(ps,&p[j]);
    }

    ap0=pop(ps);//---------------------

    while (ap0!=NULL)
    {
        printf("%s\t",ap0->name);
        is[ap0->name[0]]=false;
        put_l++;
        for (L j =ap0->next; j !=NULL; j=j->next)
        {
            j->num--;
            if(j->num==0){
                push(ps,&p[j->num]);
            }
        }
        
        ap0=pop(ps);
    }

    if(put_l<i){
        printf("有环\n");
        return false;
    }else return true;  
}

ALP Circle(int num,AL p[]){
    L ql;
    if(p[num].next==NULL){
        p[num].pass=-1;
        return NULL;
    }

    ql=p[num].next;
    do{
        if (p[ql->num].pass==-1)return &p[ql->num];
        if (p[ql->num].pass==0 && Circle(ql->num,p))return &p[ql->num];
        ql=ql->next;
    }while(ql!=NULL);

    p[num].pass==-1;
    return NULL;
}


void JudgeCircle(bool k,int i,AL p[]){
    if(k)printf("无环\n");
    else
    {
        printf("有环\n");

        for (int j = 0; j < i; j++)
        {
            ALP CL=Circle(j,p);
            if(is[CL->name[0]]&&CL){
                is[CL->name[0]]=false;
                printf("%s\n",CL->name);
            }
        }
        
    }
    
}

void dijkstra(AL p[],int pre[],int dtc[],int source,int i){
    bool visited[i];
    for (int j = 0; j < i; j++)
    {
        visited[j]=false;
        dtc[j]=INT_MAX;
        pre[j]=-1;
    }

    dtc[source]=0;
    int n;
    int min=INT_MAX;
    for (int j = 0; j < i-1; j++)
    {
        min=INT_MAX;
        for (int k = 0; k < i; k++)
        {
            if(!visited[k]&& dtc[k]<min){
                min=dtc[k];
                n=k;
            }
        }

        visited[n]=true;

        L ql=p[n].next;
        while (ql)
        {
            if(!visited[ql->num] && p[n].weight+dtc[n]<dtc[ql->num]&&dtc[ql->num]!=INT_MAX){
                dtc[ql->num]=p[n].weight+dtc[n];
                pre[ql->num]=n;
            }
            ql=ql->next;
        }
        
        
    }
    
    
    
}

void PrintWay(int pre[],AL p[],int n){
    if(pre[n]==-1){
        printf("%s",p[n].name);
        return;
    }

    PrintWay(pre,p,pre[n]);
    printf("->%s",p[n].name);
}

int main(){
    int i,source=0;
    char word[30];
    ALP p=(ALP)malloc(M*sizeof(AL));
    for (int j = 0; j < M; j++)
    {
        p[j].next=NULL;
        p[j].weight=0;
        p[j].pass=0;

    }
    
    FILE *fp=fopen("./p2.txt","r");
    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        Read(word,p);
    }
    print(p,&i);
    JudgeCircle(Compare(p,i),i,p);

    int pre[i],dtc[i];
    dijkstra(p,pre,dtc,source,i);

    for (int j = 0; j < i; j++)
    {
        PrintWay(pre,p,j);
    }
    free(p);
    return 0;

}