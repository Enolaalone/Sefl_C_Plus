#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define OVERFLOW -2
#define def_length 100
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
    Tree* M[100],*T;
    int t_num,num,dp,LR;
    char E[5],e,value;
    char*definition=(char*)malloc(def_length*sizeof(char));
    while(1){
        printf("输入需要操作的树（1-99），或者按0退出！\n");
        gets(E);
        t_num=atoi(E);
        if(!t_num)break;
        else if(t_num<1||t_num>99)printf("请重新输入!\n");
        pr=false;
        while(1){
            print(&pr);
            gets(E);
            num=atoi(E);
            if(!num)break;
            else if(num<0||num>16)printf("重新输入！\n");
            else if(num==1){
                if(!M[t_num]){
                    T=(Tree*)malloc(sizeof(Tree));
                    T->r_kid=NULL;
                    M[t_num]=T;
                    printf("输入遍历序列！\n");
                    scanf("%[^\n]",definition);
                    if(CreatBiTree(&T->l_kid,&definition)){
                        printf("树创建成功!\n");
                    }else{
                        printf("树创建失败！\n");
                    }
                }else{
                    printf("树已经存在！\n");
                }
            }

            else if(num==2){
                if(M[t_num]){
                    if(DestroyBiTree(M[t_num])){
                        printf("树销毁成功！\n");
                    }else{
                        printf("树销毁失败！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==3){
                if(M[t_num]){
                    if(ClearBiTree(M[t_num]->l_kid)){
                        printf("树清理成功!\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==4){
                if(M[t_num]){
                    if(BiTreeEmpty(M[t_num]->l_kid)){
                        printf("树为空!\n");
                    }else{
                        printf("树不为空！\n");
                    }

                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==5){
                if(M[t_num]){
                    dp=BiTreeDepth(M[t_num]->l_kid);
                    if(dp){
                        printf("树深度为%d!\n",dp);
                    }else{
                        printf("树为空！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==6){
                if(M[t_num]){
                    printf("输入需要查询的节点名称!\n");
                    scanf("%c",&e);
                    T= LocateNode(M[t_num]->l_kid,e);
                    if(T){
                        printf("%c节点的值为%c",T->key,T->data);
                    } else{
                        printf("未找到节点");
                    }
                } else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==7){
                if(M[t_num]){
                    printf("输入需要查询的节点名称,以及赋值!\n");
                    scanf("%c %c",&e,&value);

                    if(Assign(M[t_num]->l_kid,e,value)){
                        printf("赋值成功！\n");
                    } else{
                        printf("未找到节点");
                    }
                } else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==8){
                if(M[t_num]){
                    printf("输入需要查询兄弟节点的节点名称!\n");
                    scanf("%c",&e);
                    T= LocateNode(M[t_num]->l_kid,e);
                    if(T){
                        printf("%c节点兄弟节点为%c",e,T->key);
                    } else{
                        printf("未找到该节点的兄弟节点");
                    }
                } else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==9){
                if(M[t_num]){
                    T=(Tree*) malloc(sizeof (Tree));
                    printf("输入需要被插入节点的名称，以及位置（ 左or右）!\n");
                    scanf("%c %d",&e,&LR);

                    if(InsertNode(M[t_num]->l_kid,e,LR,T)){
                        printf("插入成功！");
                    } else{
                        printf("未找到该节点的兄弟节点");
                    }
                } else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==10){
                if(M[t_num]){
                    printf("输入需要被删除节点的名称\n");
                    scanf("%c",&e);

                    if(DeleteNode(M[t_num]->l_kid,e)){
                        printf("删除成功！");
                    }
                } else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==11){
                if(M[t_num]){
                    if(PreOrderTraverse(M[t_num]->l_kid)){
                        printf("前序遍历成功！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==12){
                if(M[t_num]){
                    if(InOrderTraverse(M[t_num]->l_kid)){
                        printf("中序成功！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==13){
                if(M[t_num]){
                    if(PostOrderTraverse(M[t_num]->l_kid)){
                        printf("后序成功！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==14){
                if(M[t_num]){
                    if(LevelOrderTraverse(M[t_num]->l_kid)){
                        printf("按层遍历成功！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }

            else if(num==15){
                if(M[t_num]){
                    if(Write(M[t_num]->l_kid)){
                        printf("文件写入成功！\n");
                    }
                }else{
                    printf("树已经删除，或不存在！\n");
                }
            }
            else if(num==16){
                if(M[t_num]){
                    char*words=(char*) malloc(def_length* sizeof(char));
                    TreeRead(&M[t_num]->l_kid,words);
                    printf("文件读入成功！\n");

                }else{
                    printf("树已经删除，或不存在！\n");
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

bool TreeRead(Tree **T,char *definition){
    char name[20],word;
    printf("输入读入文件的名称!\n");
    gets(name);
    FILE *fp= fopen(name,"r");
    while (fread(&word,1,1,fp)){
        *definition=word;
        definition++;
    }
    return read(T,&definition);
}



