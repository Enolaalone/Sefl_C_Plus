#ifndef MINESWEEPEREX3_BOARD_H
#define MINESWEEPEREX3_BOARD_H
#include "graphics.h"
#include <conio.h>
#include <vector>
using namespace std;
class Board{
protected://��Ϊ��������
    int x,y;//λ��
    int n;//չʾ����
    IMAGE* img;//ͼƬ��ַ
public:

    //��ʼ��
    Board();

    //չʾ
    virtual void Show();
    //��������
    void SetN(int n0);

    //����ͼƬ
    void SetImagine(IMAGE* i);

    //����λ��
    void  SetPos(int px,int py);

    //��ȡλ��
    pair<int,int> GetPos();

};

#endif //MINESWEEPEREX3_BOARD_H
