#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct  zip
{
    char ch[4];
    char code[25];
}zip;


//	111001101
zip* Content(zip* nodes,int* n){
    nodes=(zip*)malloc(sizeof(zip));
    char word[40];
    FILE *fp=fopen("code.txt","r");
    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        nodes=(zip*)realloc(nodes,(*n+1)*sizeof(zip));
        if(sscanf(word,"%s\t%s",nodes[*n].ch,nodes[*n].code)==2)
        (*n)++;
        else    {
            printf("%s %s",nodes[*n].ch,nodes[*n].code);
        }
    }
 
    nodes=(zip*)realloc(nodes,(*n+1)*sizeof(zip));
    strcpy(nodes[*n].ch,"\n");
    strcpy(nodes[*n].code,"111001101");
    (*n)++;
    fclose(fp);
    return nodes;
}



// void Compare0(zip*nodes,int n){//二分查找排序
//     zip node;
//     char name[4],number[25];
//     setlocale(LC_COLLATE,"zh_CN.UTF-8");
//     for (int i = 0; i < n-1; i++)
//     {
//         for (int j = 0; j < n-1-i; j++)
//         {
//             if(strcoll(nodes[j].ch,nodes[j+1].ch)>0){//j>j+1
//                 strcpy(name,nodes[j].ch);
//                 strcpy(nodes[j].ch,nodes[j+1].ch);
//                 strcpy(nodes[j+1].ch,name);

//                 strcpy(number,nodes[j].code);
//                 strcpy(nodes[j].code,nodes[j+1].code);
//                 strcpy(nodes[j+1].code,number);
//             }
//         }
//     }
// }

int cmp(const void* a, const void* b){
    // setlocale(LC_COLLATE,"zh_CN.UTF-8");
    return strcmp(((struct zip*)a)->ch,((struct zip*)b)->ch);
}
void Compare(zip*nodes,int n){//二分查找排序
    qsort(nodes,n,sizeof(zip),cmp);
}

// 文件压缩写入
void BinString(char *codes,FILE*p,char *letter,int *bitCount){

    for (int i=0;codes[i]!='\0' ; i++)
    {
       (*letter)<<=1;//左移腾出最右0

       if(codes[i]=='1') (*letter)|=1;// |有1为1 一个字节 与 0000 0001进行运算
       (*bitCount)++;

       if((*bitCount)==8){//复原
            
            fwrite(letter,1,1,p);
            // printf("%c",*letter);
            (*letter)=0;
            (*bitCount)=0;
       }
    }
    
}

void BinSearch(zip*nodes,char *word,FILE*pf,int n1,int n2,char *letter,int *bitCount){
    // setlocale(LC_COLLATE,"zh_CN.UTF-8");
    int mid=(n1+n2)/2;
    zip node=nodes[mid];
    int result=strcmp(word,node.ch);

    // printf("%s %s\n",node.ch,word);

    if(strcmp(nodes[n1].ch,word)==0 || strcmp(nodes[n2].ch,word)==0){
        if(strcmp(nodes[n1].ch,word)==0 )
        BinString(nodes[n1].code,pf,letter,bitCount);
        else 
        BinString(nodes[n2].code,pf,letter,bitCount);
        // fprintf(pf,"%s",word);
        return;
    }

    if (n1==n2 ||n2==n1+1)return;
    if(result==0) {
        BinString(nodes[mid].code,pf,letter,bitCount);
        // fprintf(pf,"%s",word);
        return;
    }
    else if (result<0)
        n2=mid-1;
    else if (result>0)
        n1=mid+1;

    BinSearch(nodes,word,pf,n1,n2,letter,bitCount);

}



void CreateFile(zip* nodes,int n){//创建文件
    char w_name[20]="bin.txt",r_name[20]="sgY.txt",word[4];//;,name[10]="sg.txt"; 
    FILE*fp=fopen(r_name,"r");
    FILE*pf=fopen(w_name,"w");
    char *letter=(char*)malloc(sizeof(char));*letter=0;
    int *bitCount=(int*)malloc(sizeof(int));*bitCount=0;
    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        BinSearch(nodes,word,pf,0,n-1,letter,bitCount);
    }

    if (*bitCount > 0) {//剩下不足八位添零补位
    (*letter) <<= (8 - *bitCount); // 将剩余的位左移
    fwrite(letter, 1, 1, pf);
    }
    fclose(pf);
    fclose(fp);
}

int main(){
    int *n=(int*)malloc(sizeof(int));*n=0;
    zip* nodes;

    
    nodes=Content(nodes,n);
    FILE*pf=fopen("code2.txt","w");
    for (int i = 0; i < (*n); i++)
    {
        fprintf(pf,"%s\t%s\n",nodes[i].ch,nodes[i].code);
    }
    fclose(pf);
    


    Compare(nodes,*n);
    FILE *pff=fopen("A_code.txt","w");
    for (int i = 0; i < (*n); i++)
    {
        fprintf(pff,"%s\t%s\n",nodes[i].ch,nodes[i].code);
    }
    fclose(pff);

    

    CreateFile(nodes,*n);


    

}