#include <stdio.h>
//Hash���ݽṹ
typedef struct aList{//��
  int num;//����λ��
  struct aList*next;//��һ���ӵ�ַ
}*L;//ָ������

typedef struct AOVList{
    int num;//���
    char name[25];//��Ŀ����
    L *next;//��
}AL,*ALP;



int main() {
    return 0;
}