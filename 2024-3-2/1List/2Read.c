#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 100
bool is[256];
//Hash���ݽṹ
typedef struct aList{//��
    int num;//����λ��
    struct aList*next;//��һ���ӵ�ַ
}*L;//ָ������

typedef struct AOVList{
    int num;//���
    char name[25];//��Ŀ����
    L next;//��
}AL,*ALP;

void Read(char *word,AL p[]){//�������飬���
    int i=1,k,in_num=0;//�ӵ�һ����ʼ���
    k=(int)(word[0]-'A');
    if(word[0]>='A' && word[0]<='Z' ){//����
        if( !is[word[0]]){
            p[k].name[0]=word[0];//����
            p[k].name[1]='\0';//����
            is[word[0]]=true;
        }
    } else return;//���ַ�����

    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){//����
                p[k].name[0]=word[i];//����
                p[k].name[1]='\0';//����
                is[word[i]]=true;
            }
            if(p[k].next==NULL) {
                p[k].next=(L) malloc(sizeof (struct aList));//�����ڴ�
                p[k].next->num=(int)(word[0]-'A');//����ַ
                p[k].next->next=NULL;
            } else {
                L L_p=p[k].next;
                while(1)  {
                    if(L_p->next!=NULL){
                        L_p=L_p->next;
                        continue;
                    } else{
                        L_p->next=(L) malloc(sizeof (struct aList));
                        L_p->next->num=(int)(word[0]-'A');
                        L_p->next->next=NULL;
                        break;
                    }
                }
            }
        }
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
}


int main() {
    int i=0;//���鳤��
    char word[30];
    ALP p=(ALP) malloc(M*sizeof (AL));//�����ڴ�
    for (int j = 0; j < M; ++j) {
        p[j].next=NULL;
    }
    FILE *fp= fopen("./p01.txt","r");
    while(fgets(word,sizeof (word),fp)!=NULL){
        Read(word,p);
    }

    //------------------��ӡ--------------------
    printf("���\t�����\t����\t������Ŀ\n");
    while(p[i].name[0]>='A'&& p[i].name[0]<='Z'){
        printf("%d\t%d\t%s\t",i,p[i].num,p[i].name);
        for (L j =p[i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("\n");
        i++;
    }
    printf("������%d",i);

    fclose(fp);
    free(p);
    return 0;
}