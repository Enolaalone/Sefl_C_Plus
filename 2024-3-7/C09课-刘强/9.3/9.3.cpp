#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int distance;           //·������
    char way[200];          //·��
}path;

typedef struct{
    int num;                //�������
    int in;                 //���
    char name;              //��������
    int come[10];           //�洢�ö���ǰ�򶥵�����
    int go[10];             //�洢�ö���ָ��Ķ������ź�Ȩ��
    int out;                //��ʾ�ýڵ��Ƿ��޳�
    int hour;               //��ʾ�ö���Ĺ���ʱ��
}vertex;


//////////////////�õ��������������(DFS),�����int distance �� int nov���˾����ǹؼ���һ��ʼ�õ���int* distance �� int* nov////////////////

void find_all_path(vertex* Vertex,path* paths,int j,int n,char* way,int distance,int* nop,int nov){
                    //�ڽӱ��� ·������ ����������� �ڽӱ����鳤�� ��ʱ����·������ ���� �ڼ���·�� ĳ��·���ĵڼ�������
    vertex* cur=Vertex+j;     //curָ��ǰ����
    //if (cur->num==n-1){strcpy(paths[(*nop)++].way,way);paths[(*nop)-1].distance=*distance+Vertex[n-1].hour;memset(way,'\0',100);*distance=0;}
    if (cur->num==n-1){way[nov]='\0';strcpy(paths[(*nop)++].way,way);paths[(*nop)-1].distance=distance+Vertex[n-1].hour;}//�����յ� ����ʱ·��way��·������path����
    for (int i=0;i<10;i++){
        if (cur->go[i]>0){//go[]ʹ�ö�Ϊ1-9��δ��ʹ��Ԫ�ؾ���0
            way[nov]=Vertex[cur->go[i]-1].name;//way��¼·����������
            int new_distance=distance+(cur->hour);//����·������
            find_all_path(Vertex,paths,cur->go[i]-1,n,way,new_distance,nop,nov+1);
        }
    }
}


path* find_min_path(path* paths,int* nop){//�ҵ����·��
    int min=0;    //min�����·�������
    for (int i=0;i<*nop;i++){
        if (paths[i].distance<paths[min].distance){//��̨ʽ�Ƚ�
            min=i;
        }
    }
    return paths+min;
}
//------------------------------------------------------------------------------
int find_in(vertex* Vertex,int n){
    for (int i=0;i<n;i++){
        if (Vertex[i].in==0 && Vertex[i].out==0){
            return i;
        }
    }
    return -1;    //��û�����Ϊ0�Ķ��㣬˵��ͼ�д��ڻ�·
}

int is_circle(vertex* Vertex,int n){
    int q,m;
    vertex* v,*vv;
    for (int i=0;i<n;i++){
        if ((q=find_in(Vertex,n))!=-1){
            v=Vertex+q;
            v->out=1;
            m=0;
            while (v->go[m++]!=0){
                vv=Vertex+v->go[m-1]-1;
                vv->in-=1;//���ڽ�����ת����һ���� �����-1
            }
        }
    }
    if (q==-1){
        printf("��ͼ���л����ɻ��Ķ���Ϊ:");
        for (int i=0;i<n;i++){
            if (!Vertex[i].out){printf("%c ",Vertex[i].name);}
        }
    }
    if (q==-1){return 1;}
    else{return 0;}
}

int main(){
    char name[20];
    printf("�������ļ�����(p02.txtΪ�Դ����޻��ļ�  p03.txtΪ���޸ĵ��л��ļ�)\n");
    scanf("%s",name);
    FILE* fp=fopen(name,"r");
    if (fp == NULL){printf("�ļ�p02.txt��ʧ��\n");}


    vertex Vertex[100];  //�ڽӱ�����
    int n=0,m;          //n�Ƕ�����ţ�m�Ƕ������
    char str[100];
    char* token;
    fgets(str,100,fp);
    while (fgets(str,100,fp)!=NULL){
        token=strtok(str,",");
        Vertex[n].name=token[0];    //Vertex�Ķ�������Ϊ���ص�һ���ַ�����ͷ��ĸ
        memset(Vertex[n].come,0,40);   //��ʼ��comeΪ0  come[]����Ϊ10 һ��utf-8����4 ��40
        m=0;  //��¼���
        while ((token=strtok(NULL,","))!=NULL){//����һ���������ַ���
            if (1<=atoi(token) && atoi(token)<=18){Vertex[n].hour=atoi(token);}//��ȡʱ��Ȩ��
            if ('A'<=token[0] && token[0]<='Z'){
                m++;//�ö������ȼ�1
                Vertex[n].come[m-1]=(token[0]-'A'+1);//int come[],����ǰ�����ǰ�����㣺 //��������1  �ڳ�ʼ�������ڵ��ʱ��� -1
                }//
        }
        Vertex[n].num=n;//��ǰ��������
        Vertex[n].in=m;//��ǰ�������m
        n++;//������һ���������Ϣ
    }

    char go_num[n];   //go_num�����¼ÿ������ָ��Ķ������,n��ʵ����AOV���ж����ܸ���
    memset(go_num,0,n);//��ʼ�� 

    for (int i=0;i<n;i++){memset(Vertex[i].go,0,40);}//��ʼ������comeΪ0  come[]����Ϊ10 һ��utf-8����4 ��40

    for (int i=0;i<n;i++){//�����ڽӱ�����
        for (int j=0;j<10;j++){//����come[]
            if (Vertex[i].come[j]!=0){//��Ϊ���Ϊ��Ķ���
                Vertex[Vertex[i].come[j]-1].go[go_num[Vertex[i].come[j]-1]++]=i+1;
                //go_num[Vertex[i].come[j]-1]++ ����Ӧ��ŵĶ����ָ�����+1��ͬʱָ�������Ϊgo[]���,i+1������ڽ���������Ȩ��
            }
        }
        Vertex[i].out=0;//��0 1��ʾ�����Ƿ񱻷��ʣ�
    }


    if (!is_circle(Vertex,n)){
        char way[200];              //��ʱ�洢ÿ�ε�·��
        int distance=0;             //��ʱ�洢ÿ��·���ĳ��Ⱥ�
        path paths[100];            //�������е�·�������浽paths��
        int nop=0;                  //num of path ��ʾ�ڼ���·��
        //int nov=0;                  //num of vertex ��ʾĳ��·���ĵڼ�������
        find_all_path(Vertex,paths,0,n,way,0,&nop,0);
        printf("\nͼ���޻�\n��A��W�����·��Ϊ��A --> ");
        for (int i=0;i<strlen(find_min_path(paths,&nop)->way)-1;i++){
            printf("%c --> ",find_min_path(paths,&nop)->way[i]);
        }
        printf("W\n");
        printf("���·��Ϊ��%d",find_min_path(paths,&nop)->distance);
    }

}

