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
    int x,y;//位置
    int r;//大小
    COLORREF color;//颜色
public:
    //初始化
    explicit Sprite(int x0=0,int y0=0,int r0=5,COLORREF c=WHITE);

    //虚函数画精灵
    virtual void draw() const;

    //碰撞函数
    bool collision(const Sprite &another) const;

    //设置位置
    void SetPos(int px,int py);

    //获取位置
    pair<int,int> GetPos();

    //获取大小
    int GetR();
};

#endif //SNAKE_SPRITE_H
