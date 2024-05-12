#ifndef MINESWEEPEREX3_BOARD_H
#define MINESWEEPEREX3_BOARD_H
#include "graphics.h"
#include <conio.h>
#include <vector>
using namespace std;
class Board{
protected://作为父类属性
    int x,y;//位置
    int n;//展示数据
    IMAGE* img;//图片地址
public:

    //初始化
    Board();

    //展示
    virtual void Show();
    //设置数据
    void SetN(int n0);

    //设置图片
    void SetImagine(IMAGE* i);

    //设置位置
    void  SetPos(int px,int py);

    //获取位置
    pair<int,int> GetPos();

};

#endif //MINESWEEPEREX3_BOARD_H
