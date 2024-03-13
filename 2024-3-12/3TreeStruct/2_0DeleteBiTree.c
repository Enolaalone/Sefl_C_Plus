#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define OVERFLOW -2
bool pr=false;
typedef struct Node{//树结构
    int data;
    char key;
    struct Node* l_kid;
    struct Node* r_kid;
}Tree;
void print(bool *r);
bool CreatBiTree(Tree **T,char **definition);//创建
bool DestroyBiTree(Tree **T);//销毁
bool ClearBiTree(Tree **T);//清空
bool BiTreeEmpty(Tree *T);//判断空表
bool BiTreeDepth(Tree *T);//求二叉树深度
Tree *LocateNode(Tree *T,char e); //查找结点
bool Assign(Tree *T,char e,char value);//结点赋值
bool parents(Tree *T,char e);
bool GetSibling(Tree *T,char e);//获得兄弟结点
bool InsertNode(Tree *T,char e,bool LR,Tree *c);//插入结点
bool DeleteNode(Tree *T,char e);//删除关键字为 e 的结点
bool Delecel(Tree *T);//删除结点
bool Delecer(Tree *T);//删除结点
bool PreOrderTraverse(Tree *T);//前序遍历
bool InOrderTraverse(Tree *T);//中序遍历
bool PostOrderTraverse(Tree *T);//后序遍历
bool LevelOrderTraverse(Tree *T);//按层遍历
bool Write(Tree *T);
bool TreeWrite(Tree *T,FILE *fp);
bool read(Tree**T);

bool TreeRead(Tree **T,char *definition);

int main() {
    Tree *M[100],*p,*c,*tree;//树数组
    char*definition,value,e,E[5];
    int i,LR;
    for (int j = 0; j < 100; ++j) {
        M[j]=NULL;
    }
    while(1){
        int t_num;
        printf("输入需要对哪个二叉树进行操作（1-99），0退出？\n");
        gets(E);
        t_num= atoi(E);
        if(!t_num)break;
        else{
            if(t_num>99 || t_num<0){
                printf("不存在此二叉树!\n");
            }else{
                pr=false;
                while(1){
                    print(&pr);
                    gets(E);
                    int num= atoi(E);
                    if(!num)break;
                    else if(num==1){
                        if(!M[t_num]){
                            printf("输入带空二叉树的前序遍历！");
                            fflush(stdin);
                            scanf("%[^\n]",definition);
                            M[t_num]=(Tree*) malloc(sizeof (Tree));
                            M[t_num]->r_kid=NULL;//无右子
                            M[t_num]->key=0;
                            if(CreatBiTree(&(M[t_num]->l_kid),&definition)){
                                printf("二叉树创建成功!/n");
                            } else printf("二叉树创建失败!\n");
                        }else{
                            printf("树已经创建！\n");
                        }
                    }

                    else if(num==2){
                        if(M[t_num]){
                            if(DestroyBiTree(&M[t_num])){
                                printf("二叉树销毁成功!/n");
                            }
                        }else{
                            printf("树不存在！\n");
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
        printf("请选择你的操作[0-16]:\n");
    }
    *r=true;//打印一次
}

bool CreatBiTree(Tree **T,char **definition){//definition为前序字符串
    if(**definition=='#'){
        (*T)=NULL;//递归结束
        (*definition)++;//下一字符
        return true;
    }else{
        (*T)=(Tree*) malloc(sizeof (Tree));//建立节点
        if(!*T)exit(OVERFLOW);
        else{
            (*T)->key=**definition;
            (*T)->data='x';
            (*definition)++;//下一字符
            CreatBiTree(&(*T)->l_kid,definition);//左子
            CreatBiTree(&(*T)->r_kid,definition);//右子
        }
    }
    return true;
}//创建
bool DestroyBiTree(Tree **T){
    Tree *p=*T;
    ClearBiTree(T);//清理所有节点
    free(p);
    *T=NULL;
    return true;
}//销毁

