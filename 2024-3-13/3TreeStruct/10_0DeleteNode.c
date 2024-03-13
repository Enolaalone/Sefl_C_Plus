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
int BiTreeDepth(Tree *T);//求二叉树深度
Tree *LocateNode(Tree *T,char e); //查找结点
bool Assign(Tree *T,char e,char value);//结点赋值
Tree* parents(Tree *T,char e);
Tree* GetSibling(Tree *T,char e);//获得兄弟结点
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

                    else if(num==3){
                        if(M[t_num]){
                            if(ClearBiTree(&(M[t_num]->l_kid))){
                                printf("二叉树清理成功!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==4){
                        if(M[t_num]){
                            if(!BiTreeEmpty(M[t_num]->l_kid)){
                                printf("二叉树非空!/n");
                            } else{
                                printf("二叉树空!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==5){
                        if(M[t_num]){
                            i= BiTreeDepth(M[t_num]->l_kid);
                            if(i){
                                printf("二叉树深度为%d!/n",i);
                            } else{
                                printf("二叉树空!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==6){
                        if(M[t_num]){
                            printf("输入需要查询的元素!\n");
                            scanf("%c",&e);
                            p= LocateNode(M[t_num],e);
                            if(p){
                                printf("节点为:%c %c!/n",p->data,p->key);
                            } else{
                                printf("不存在该节点!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==7){
                        if(M[t_num]){
                            printf("输入需要查询的元素及其赋值!\n");
                            scanf("%c %c",&e,&value);
                            if(Assign(M[t_num],e,value)){
                                printf("节点赋值成功!/n");
                            } else{
                                printf("节点赋值失败!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==8){
                        if(M[t_num]){
                            printf("输入需要查询的元素!\n");
                            scanf("%c",&e);
                            p= GetSibling(M[t_num]->l_kid,e);
                            if(p){
                                printf("%c的兄弟节点为点为:%c %c!/n",e,p->data,p->key);
                            } else{
                                printf("不存在该节点的兄弟节点!/n");
                            }
                        }else{
                            printf("树不存在！\n");
                        }
                    }

                    else if(num==9){
                        if(M[t_num]){
                            c=(Tree*) malloc(sizeof (Tree));
                            printf("输入需要之前插入的元素，位置,名称，及其数据!\n");
                            scanf("%c %d %c %d",&e,&LR,&c->key,&c->data);

                            if(InsertNode(M[t_num]->l_kid,e,LR,c)){
                                printf("元素插入成功！/n");
                            } else{
                                printf("插入失败!/n");
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

bool ClearBiTree(Tree **T){
    if(!(*T)){
        return true;
    } else{
        if((*T)->l_kid) ClearBiTree(&((*T)->l_kid));//递归到最底层
        if((*T)->r_kid) ClearBiTree(&((*T)->r_kid));
        free((*T));//向上清除
        (*T)=NULL;
        return true;
    }
}//清空

bool BiTreeEmpty(Tree *T){
    if(T)return false;
    else return true;
}//判断空表

int BiTreeDepth(Tree *T){
    int depth,l_depth,r_depth;
    if(!T){
        depth=0;
    } else{
        l_depth=BiTreeDepth(T->l_kid);//递归到最底层
        r_depth=BiTreeDepth(T->r_kid);
        depth=1+(l_depth>=r_depth?l_depth:r_depth);
    }
    return depth;
}//求二叉树深度

Tree *LocateNode(Tree *T,char e){
    Tree *p;
    if(!T){
        return NULL;//空指针
    } else{
        if((*T).key==e) return T;//找到返回

        p=LocateNode(T->l_kid,e);//左树遍历
        if(p) return p;//如果没找到，就遍历右树
        else return LocateNode(T->r_kid,e);
    }

}//查找结点

bool Assign(Tree *T,char e,char value){
    Tree *p;
    p= LocateNode(T,e);
    if(p){
        p->data=(int)value;
        return true;
    } else return false;

}//结点赋值

Tree* parents(Tree *T,char e){
    Tree *p,*q=NULL;
    if(!T){
        return NULL;//空指针
    } else{
        if(T->l_kid!=NULL&&T->l_kid->key==e || T->r_kid!=NULL&&T->r_kid->key==e) return T;//找到返回
        else{
            p=parents(T->l_kid,e);//左树遍历
            if(p) return p;//如果没找到，就遍历右树
            else return parents(T->r_kid,e);
        }
    }
}

Tree* GetSibling(Tree *T,char e){
    Tree *p;
    p= parents(T,e);
    if(!p) return false;
    else if(p->l_kid!=NULL&&p->l_kid->key==e){
        p=p->r_kid;
        return p;

    }else {
        if(p->r_kid!=NULL&&p->r_kid->key==e){
            p=p->l_kid;
            return p;
        }
    }
}//获得兄弟结点

bool InsertNode(Tree *T,char e,bool LR,Tree *c){
    if(T){
        if(T->key==e){
            if(LR){
                c->r_kid=T->r_kid;//插入节点的右孩子等于原来节点的右孩子
                c->l_kid=NULL;//左孩子等于NULL
                T->r_kid=c;//原来节点的右孩子为c
            }
            else{
                c->l_kid=T->l_kid;
                c->r_kid=NULL;
                T->l_kid=c;
            }
        }else{
            InsertNode(T->l_kid,e,LR,c);//递归找到e节点
            InsertNode(T->r_kid,e,LR,c);
        }
        return true;

    } else return false;
}//插入结点
bool Delecel(Tree *T){//T为删除节点的父节点
    Tree *q,*p,*t;
    q=T;
    p=q->l_kid;
    t=p->l_kid;
    if(!p->l_kid){
        if(!p->r_kid){//p无孩子
            q->l_kid=NULL;
            return true;
        }
        else{//1度 p有右孩子
            p->l_kid=p->r_kid;
            q->l_kid=p->l_kid;
            return true;
        }
    }
    else{
        if(!p->r_kid){//1度 p有左孩子
            q->l_kid=p->l_kid;
            return true;
        }
        else{//双子
            while(t->r_kid!=NULL)
                t=t->r_kid;
            t->r_kid=p->r_kid;//移走p的右孩子
            q->l_kid=p->l_kid;
            return true;
        }
    }

}//删除结点

bool Delecer(Tree *T){
    Tree *q,*p,*t;
    q=T;
    p=q->r_kid;
    t=p->r_kid;
    if(!p->r_kid){
        if(!p->l_kid){//p无孩子
            q->r_kid=NULL;
            return true;
        }
        else{//1度 p有左孩子
            p->r_kid=p->l_kid;
            q->r_kid=p->r_kid;
            return true;
        }
    }
    else{
        if(!p->l_kid){//1度 p有右孩子
            q->r_kid=p->r_kid;
            return true;
        }
        else{//双子
            while(t->l_kid!=NULL)
                t=t->l_kid;
            t->l_kid=p->l_kid;
            q->r_kid=p->r_kid;
            return true;
        }
    }
}//删除结点