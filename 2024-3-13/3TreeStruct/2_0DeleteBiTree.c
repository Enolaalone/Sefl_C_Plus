#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define OVERFLOW -2
bool pr=false;
typedef struct Node{//���ṹ
    int data;
    char key;
    struct Node* l_kid;
    struct Node* r_kid;
}Tree;
void print(bool *r);
bool CreatBiTree(Tree **T,char **definition);//����
bool DestroyBiTree(Tree **T);//����
bool ClearBiTree(Tree **T);//���
bool BiTreeEmpty(Tree *T);//�жϿձ�
bool BiTreeDepth(Tree *T);//����������
Tree *LocateNode(Tree *T,char e); //���ҽ��
bool Assign(Tree *T,char e,char value);//��㸳ֵ
bool parents(Tree *T,char e);
bool GetSibling(Tree *T,char e);//����ֵܽ��
bool InsertNode(Tree *T,char e,bool LR,Tree *c);//������
bool DeleteNode(Tree *T,char e);//ɾ���ؼ���Ϊ e �Ľ��
bool Delecel(Tree *T);//ɾ�����
bool Delecer(Tree *T);//ɾ�����
bool PreOrderTraverse(Tree *T);//ǰ�����
bool InOrderTraverse(Tree *T);//�������
bool PostOrderTraverse(Tree *T);//�������
bool LevelOrderTraverse(Tree *T);//�������
bool Write(Tree *T);
bool TreeWrite(Tree *T,FILE *fp);
bool read(Tree**T);

bool TreeRead(Tree **T,char *definition);

int main() {
    Tree *M[100],*p,*c,*tree;//������
    char*definition,value,e,E[5];
    int i,LR;
    for (int j = 0; j < 100; ++j) {
        M[j]=NULL;
    }
    while(1){
        int t_num;
        printf("������Ҫ���ĸ����������в�����1-99����0�˳���\n");
        gets(E);
        t_num= atoi(E);
        if(!t_num)break;
        else{
            if(t_num>99 || t_num<0){
                printf("�����ڴ˶�����!\n");
            }else{
                pr=false;
                while(1){
                    print(&pr);
                    gets(E);
                    int num= atoi(E);
                    if(!num)break;
                    else if(num==1){
                        if(!M[t_num]){
                            printf("������ն�������ǰ�������");
                            fflush(stdin);
                            scanf("%[^\n]",definition);
                            M[t_num]=(Tree*) malloc(sizeof (Tree));
                            M[t_num]->r_kid=NULL;//������
                            M[t_num]->key=0;
                            if(CreatBiTree(&(M[t_num]->l_kid),&definition)){
                                printf("�����������ɹ�!/n");
                            } else printf("����������ʧ��!\n");
                        }else{
                            printf("���Ѿ�������\n");
                        }
                    }

                    else if(num==2){
                        if(M[t_num]){
                            if(DestroyBiTree(&M[t_num])){
                                printf("���������ٳɹ�!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
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
        printf("1.CreateBiTree\t9.InsertNode\n");
        printf("2.DestroyTree\t10.DeleteNode\n");
        printf("3.ClearTree\t11.PreOrderTraverse\n");
        printf("4.BiTreeEmpty\t12.InOrderTraverse\n");//----------------------------------4
        printf("5.BiTreeDepth\t13.PostTraverse\n");//----------------------------------5
        printf("6.LocalNode\t14.LevelOrderTraverse\n");//----------------------------------6
        printf("7.Assign\t15.Write\n");//----------------------------------7
        printf("8.GetSibling\t16.Read\n");//----------------------------------7
        printf("0.Exit\n");
        printf("------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0-16]:\n");
    }
    *r=true;//��ӡһ��
}

bool CreatBiTree(Tree **T,char **definition){//definitionΪǰ���ַ���
    if(**definition=='#'){
        (*T)=NULL;//�ݹ����
        (*definition)++;//��һ�ַ�
        return true;
    }else{
        (*T)=(Tree*) malloc(sizeof (Tree));//�����ڵ�
        if(!*T)exit(OVERFLOW);
        else{
            (*T)->key=**definition;
            (*T)->data='x';
            (*definition)++;//��һ�ַ�
            CreatBiTree(&(*T)->l_kid,definition);//����
            CreatBiTree(&(*T)->r_kid,definition);//����
        }
    }
    return true;
}//����
bool DestroyBiTree(Tree **T){
    Tree *p=*T;
    ClearBiTree(T);//�������нڵ�
    free(p);
    *T=NULL;
    return true;
}//����

