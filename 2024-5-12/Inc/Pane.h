#ifndef MINESWEEPEREX_PANE_H
#define MINESWEEPEREX_PANE_H

#define Zero 25
#define RedMine 22
#define WhiteMine 8
#define Cover 24
#define Flag1 21
#include "graphics.h"        // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <vector>
using namespace std;
enum PaneStates{
    Closed,
    Opened,
    Marked
};
class Pane{
private:
    int x,y;//�����ַ
    int i,j;//��������
    int AroundMineNum;//��Χ����
    bool IsMine;//�Ƿ��ǵ���
    bool ClickMine;//����ĵ���
    PaneStates state;//����״̬
public:
    //��ʼ��
    Pane();

    //����
    void Open(IMAGE *img);

    //�ر�
    void Close(IMAGE *img);

    //���״̬
    void Mark(IMAGE *img);

    //���� ��x,y��
    void SetPos(int px,int py);

    //���ã�i��j��
    void SetNumPos(int pi,int pj);

    //���أ�i��j��
    pair<int,int> GetNumPos();

    //�����׵�״̬
    void SetIsMine(bool s);

    //�����׵�״̬
    bool GetIsMine();

    //������Χ����
    void AddAMN();

    //������Χ����
    int GetAMN();

    //����״̬
    PaneStates GetState();

    //���õ��״̬
    void SetClick(bool s);

    //���ص��״̬
    bool GetClick();

};


#endif MINESWEEPEREX_PANE_H
