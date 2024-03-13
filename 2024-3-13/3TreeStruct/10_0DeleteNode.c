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
int BiTreeDepth(Tree *T);//����������
Tree *LocateNode(Tree *T,char e); //���ҽ��
bool Assign(Tree *T,char e,char value);//��㸳ֵ
Tree* parents(Tree *T,char e);
Tree* GetSibling(Tree *T,char e);//����ֵܽ��
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

                    else if(num==3){
                        if(M[t_num]){
                            if(ClearBiTree(&(M[t_num]->l_kid))){
                                printf("����������ɹ�!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==4){
                        if(M[t_num]){
                            if(!BiTreeEmpty(M[t_num]->l_kid)){
                                printf("�������ǿ�!/n");
                            } else{
                                printf("��������!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==5){
                        if(M[t_num]){
                            i= BiTreeDepth(M[t_num]->l_kid);
                            if(i){
                                printf("���������Ϊ%d!/n",i);
                            } else{
                                printf("��������!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==6){
                        if(M[t_num]){
                            printf("������Ҫ��ѯ��Ԫ��!\n");
                            scanf("%c",&e);
                            p= LocateNode(M[t_num],e);
                            if(p){
                                printf("�ڵ�Ϊ:%c %c!/n",p->data,p->key);
                            } else{
                                printf("�����ڸýڵ�!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==7){
                        if(M[t_num]){
                            printf("������Ҫ��ѯ��Ԫ�ؼ��丳ֵ!\n");
                            scanf("%c %c",&e,&value);
                            if(Assign(M[t_num],e,value)){
                                printf("�ڵ㸳ֵ�ɹ�!/n");
                            } else{
                                printf("�ڵ㸳ֵʧ��!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==8){
                        if(M[t_num]){
                            printf("������Ҫ��ѯ��Ԫ��!\n");
                            scanf("%c",&e);
                            p= GetSibling(M[t_num]->l_kid,e);
                            if(p){
                                printf("%c���ֵܽڵ�Ϊ��Ϊ:%c %c!/n",e,p->data,p->key);
                            } else{
                                printf("�����ڸýڵ���ֵܽڵ�!/n");
                            }
                        }else{
                            printf("�������ڣ�\n");
                        }
                    }

                    else if(num==9){
                        if(M[t_num]){
                            c=(Tree*) malloc(sizeof (Tree));
                            printf("������Ҫ֮ǰ�����Ԫ�أ�λ��,���ƣ���������!\n");
                            scanf("%c %d %c %d",&e,&LR,&c->key,&c->data);

                            if(InsertNode(M[t_num]->l_kid,e,LR,c)){
                                printf("Ԫ�ز���ɹ���/n");
                            } else{
                                printf("����ʧ��!/n");
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

bool ClearBiTree(Tree **T){
    if(!(*T)){
        return true;
    } else{
        if((*T)->l_kid) ClearBiTree(&((*T)->l_kid));//�ݹ鵽��ײ�
        if((*T)->r_kid) ClearBiTree(&((*T)->r_kid));
        free((*T));//�������
        (*T)=NULL;
        return true;
    }
}//���

bool BiTreeEmpty(Tree *T){
    if(T)return false;
    else return true;
}//�жϿձ�

int BiTreeDepth(Tree *T){
    int depth,l_depth,r_depth;
    if(!T){
        depth=0;
    } else{
        l_depth=BiTreeDepth(T->l_kid);//�ݹ鵽��ײ�
        r_depth=BiTreeDepth(T->r_kid);
        depth=1+(l_depth>=r_depth?l_depth:r_depth);
    }
    return depth;
}//����������

Tree *LocateNode(Tree *T,char e){
    Tree *p;
    if(!T){
        return NULL;//��ָ��
    } else{
        if((*T).key==e) return T;//�ҵ�����

        p=LocateNode(T->l_kid,e);//��������
        if(p) return p;//���û�ҵ����ͱ�������
        else return LocateNode(T->r_kid,e);
    }

}//���ҽ��

bool Assign(Tree *T,char e,char value){
    Tree *p;
    p= LocateNode(T,e);
    if(p){
        p->data=(int)value;
        return true;
    } else return false;

}//��㸳ֵ

Tree* parents(Tree *T,char e){
    Tree *p,*q=NULL;
    if(!T){
        return NULL;//��ָ��
    } else{
        if(T->l_kid!=NULL&&T->l_kid->key==e || T->r_kid!=NULL&&T->r_kid->key==e) return T;//�ҵ�����
        else{
            p=parents(T->l_kid,e);//��������
            if(p) return p;//���û�ҵ����ͱ�������
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
}//����ֵܽ��

bool InsertNode(Tree *T,char e,bool LR,Tree *c){
    if(T){
        if(T->key==e){
            if(LR){
                c->r_kid=T->r_kid;//����ڵ���Һ��ӵ���ԭ���ڵ���Һ���
                c->l_kid=NULL;//���ӵ���NULL
                T->r_kid=c;//ԭ���ڵ���Һ���Ϊc
            }
            else{
                c->l_kid=T->l_kid;
                c->r_kid=NULL;
                T->l_kid=c;
            }
        }else{
            InsertNode(T->l_kid,e,LR,c);//�ݹ��ҵ�e�ڵ�
            InsertNode(T->r_kid,e,LR,c);
        }
        return true;

    } else return false;
}//������
bool Delecel(Tree *T){//TΪɾ���ڵ�ĸ��ڵ�
    Tree *q,*p,*t;
    q=T;
    p=q->l_kid;
    t=p->l_kid;
    if(!p->l_kid){
        if(!p->r_kid){//p�޺���
            q->l_kid=NULL;
            return true;
        }
        else{//1�� p���Һ���
            p->l_kid=p->r_kid;
            q->l_kid=p->l_kid;
            return true;
        }
    }
    else{
        if(!p->r_kid){//1�� p������
            q->l_kid=p->l_kid;
            return true;
        }
        else{//˫��
            while(t->r_kid!=NULL)
                t=t->r_kid;
            t->r_kid=p->r_kid;//����p���Һ���
            q->l_kid=p->l_kid;
            return true;
        }
    }

}//ɾ�����

bool Delecer(Tree *T){
    Tree *q,*p,*t;
    q=T;
    p=q->r_kid;
    t=p->r_kid;
    if(!p->r_kid){
        if(!p->l_kid){//p�޺���
            q->r_kid=NULL;
            return true;
        }
        else{//1�� p������
            p->r_kid=p->l_kid;
            q->r_kid=p->r_kid;
            return true;
        }
    }
    else{
        if(!p->l_kid){//1�� p���Һ���
            q->r_kid=p->r_kid;
            return true;
        }
        else{//˫��
            while(t->l_kid!=NULL)
                t=t->l_kid;
            t->l_kid=p->l_kid;
            q->r_kid=p->r_kid;
            return true;
        }
    }
}//ɾ�����