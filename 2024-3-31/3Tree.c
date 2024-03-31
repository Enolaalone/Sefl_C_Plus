#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define OVERFLOW -2
bool pr=false;
typedef struct Node{//树结构 //ABC##DEF##G##H### //ABE#L###DHM##I##J##
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
bool read(Tree**T,char **definition);

bool TreeRead(Tree **T,char *definition);
int main() {
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

bool CreatBiTree(Tree **T,char **definition){
    if(**definition=='#'){
        (*definition)++;
        (*T)=NULL;
        return true;
    } else{
        (*T)=(Tree*) malloc(sizeof (Tree));
        if(!(*T))return OVERFLOW;
        else{
            (*T)->key=(**definition);
            (*T)->data='x';
            (*definition)++;
            CreatBiTree(&(*T)->l_kid,definition);
            CreatBiTree(&(*T)->r_kid,definition);
            return true;
        }

    }


}//创建

bool DestroyBiTree(Tree **T){
    if(!(*T))return false;
    else{
        ClearBiTree(T);
        free(*T);
        (*T)=NULL;
        return true;
    }

}//销毁

bool ClearBiTree(Tree **T){
    if(!(*T)){
        return true;
    } else{
        if((*T)->l_kid)ClearBiTree(&(*T)->l_kid);
        if((*T)->r_kid)ClearBiTree(&(*T)->r_kid);
        free(*T);
        (*T)=NULL;
        return true;
    }
}//清空

bool BiTreeEmpty(Tree *T){
    if(T)return true;
    else return false;
}

int BiTreeDepth(Tree *T){
    int dp,l_dp,r_dp;
    if(!T){
        dp=0;
    } else{
        l_dp=BiTreeDepth(T->l_kid);
        r_dp=BiTreeDepth(T->r_kid);

        dp=1+((l_dp>=r_dp)?l_dp:r_dp);
    }
    return dp;
}

Tree *LocateNode(Tree *T,char e){
    if(!T){
        return NULL;
    } else{
        if(T->key==e)return T;
        else{
            Tree *p= LocateNode(T->l_kid,e);
            if(p)return p;
            else return LocateNode(T->r_kid,e);
        }
    }

} //查找结点
bool Assign(Tree *T,char e,char value){
    Tree*p= LocateNode(T,e);
    if(p){
        p->data=(int )value;
        return true;
    } else return false;

}//结点赋值
Tree* parents(Tree *T,char e){
    if(!T){
        return NULL;
    } else{
        if(T->l_kid&&T->l_kid->key==e||T->r_kid&&T->r_kid->key==e){
            return T;
        } else{
            Tree *p= parents(T->l_kid,e);
            if(p)return p;
            else return parents(T->r_kid,e);
        }
    }
}
Tree* GetSibling(Tree *T,char e){
    Tree *p= parents(T,e);
    if(p){
        if(p->l_kid->key==e){
            p=p->r_kid;
            return p;
        }else if(p->r_kid->key==e){
            p=p->l_kid;
            return p;
        }
    } else return false;

}//获得兄弟结点
bool InsertNode(Tree *T,char e,bool LR,Tree *c){
    Tree *p= LocateNode(T,e);
    if(p){
        if(LR){
            c->l_kid=p->l_kid;
            c->r_kid=NULL;
            p->r_kid=c;
        } else{
            c->l_kid=p->l_kid;
            c->r_kid=p->r_kid;
            p->l_kid=c;
            p->r_kid=NULL;
        }
        return true;
    } else return false;

}//插入结点

bool Delecel(Tree *T){
    Tree *q=T,*p,*t;
    p=q->l_kid;
    t=p->l_kid;
    if(!p->l_kid){
        if(!p->r_kid){
            q->l_kid=NULL;
            return true;
        } else{
            q->l_kid=p->r_kid;
            return true;
        }
    } else{
        if(!p->r_kid){
            q->l_kid=p->l_kid;
            return true;
        } else{
            while(t->l_kid!=NULL){
                t=t->l_kid;
            }
            t->l_kid=p->r_kid;
            q->l_kid=p->l_kid;
            return  true;
        }
    }
}//T为删除节点的父节点

bool Delecer(Tree* T){
    Tree *q=T,*p,*t;
    p=q->r_kid;
    t=p->r_kid;
    if(!p->r_kid){
        if(!p->l_kid){
            q->r_kid=NULL;
            return true;
        } else{
            q->r_kid=p->l_kid;
            return true;
        }
    } else{
        if(!p->l_kid){
            q->r_kid=p->r_kid;
            return true;
        } else{
            while (t->r_kid!=NULL){
                t=t->r_kid;
            }
            t->r_kid=p->l_kid;
            q->r_kid=p->r_kid;
            return true;
        }
    }
}

bool DeleteNode(Tree *T,char e){
    if(T->l_kid&&T->l_kid->key==e)Delecel(T);
    if(T->r_kid&&T->r_kid->key==e)Delecer(T);
    else{
        DeleteNode(T->l_kid,e);
        DeleteNode(T->r_kid,e);
        return true;
    }
}
bool PreOrderTraverse(Tree *T){
    if(!T)return true;
    else{
        printf("%c %c\n",T->key,T->data);
        PreOrderTraverse(T->l_kid);
        PreOrderTraverse(T->r_kid);
        return true;
    }
}
bool InOrderTraverse(Tree *T){
    if(!T)return true;
    else{
        InOrderTraverse(T->l_kid);
        printf("%c %c\n",T->key,T->data);
        InOrderTraverse(T->r_kid);
        return true;
    }
}
bool PostOrderTraverse(Tree *T){
    if(!T)return true;
    else{
        PostOrderTraverse(T->l_kid);
        PostOrderTraverse(T->r_kid);
        printf("%c %c\n",T->key,T->data);
        return true;
    }
}

bool LevelOrderTraverse(Tree *T){
    Tree *pointers[1000];
    int in=0,out=0;
    pointers[in++]=T;
    while (in>out){
        if(pointers[out++]){
            printf("%c %c\n",pointers[out-1]->key,pointers[out-1]->data);
            pointers[in++]=pointers[out-1]->l_kid;
            pointers[in++]=pointers[out-1]->r_kid;
        }
    }
    return true;
}

bool TreeWrite(Tree *T,FILE *fp){
    if(!T){
        fprintf(fp,"#");
        return true;
    } else{
        fprintf(fp,"%c",T->key);
        TreeWrite(T->l_kid,fp);
        TreeWrite(T->r_kid,fp);
        return true;
    }
}
bool Write(Tree *T){
    char name[20];
    printf("输入文件名称!\n");
    gets(name);
    FILE *pf= fopen(name,"w");
    if(!pf)return OVERFLOW;
    TreeWrite(T,pf);
    fclose(pf);
    return true;
}
bool read(Tree**T,char **definition){
    if((**definition)=='\0')return true;
    if((**definition)=='#'){
        *T=NULL;
        (*definition)++;
        return true;
    } else{
        (*T)=(Tree*) malloc(sizeof (Tree));
        (*T)->key=(**definition);
        (*T)->data='x';
        (*definition)++;
        read(&(*T)->l_kid,definition);
        read(&(*T)->r_kid,definition);
        return true;
    }

}




