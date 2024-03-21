#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct zip
{
    char ch[4];
    char code[25];
};


//	111001101
zip* Content(zip* nodes,int* n){
    nodes=(zip*)malloc(sizeof(zip));
    char word[40];
    FILE *fp=fopen("code.txt","r");
    while (fgets(word,sizeof(word),fp)!=NULL)
    {
        nodes=(zip*)realloc(nodes,(*n+1)*sizeof(zip));
        sscanf(word,"%s\t%s",nodes[*n].ch,nodes[*n].code);
        (*n)++;
    }
    nodes=(zip*)realloc(nodes,(*n+1)*sizeof(zip));
    strcpy(nodes[*n].ch,"\n");
    strcpy(nodes[*n].code,"111001101");
    (*n)++;
    fclose(fp);
    return nodes;
}


int main(){
    int *n=(int*)malloc(sizeof(int));*n=0;
    zip* nodes;

    nodes=Content(nodes,n);

    // for (int i = 0; i < (*n); i++)
    // {
    //     printf("%s\t%s\n",nodes[i].ch,nodes[i].code);
    // }
    

}