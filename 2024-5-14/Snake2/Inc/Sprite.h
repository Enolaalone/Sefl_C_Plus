#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H

#include "windef.h"
#include "cmath"
#include "graphics.h"
#include <conio.h>
#include <vector>
using namespace std;

class Sprite{
protected:
    int x,y;//λ��
    int r;//��С
    COLORREF color;//��ɫ
public:
    //��ʼ��
    explicit Sprite(int x0=0,int y0=0,int r0=5,COLORREF c=WHITE);

    //�麯��������
    virtual void draw() const;

    //��ײ����
    bool collision(const Sprite &another) const;

    //����λ��
    void SetPos(int px,int py);

    //��ȡλ��
    pair<int,int> GetPos();

    //��ȡ��С
    int GetR();
};

#endif //SNAKE_SPRITE_H
