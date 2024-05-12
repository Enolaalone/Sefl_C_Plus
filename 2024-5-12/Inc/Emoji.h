#ifndef MINESWEEPEREX_EMOJI_H
#define MINESWEEPEREX_EMOJI_H

#include "graphics.h"        // 引用图形库头文件
#include <conio.h>
#include <vector>
using namespace std;
enum States{Happy,Cool,Die};
class Emoji{
private:
    int x,y;//位置
    States state;//状态
    IMAGE *img;//图库
public:
    //初始化
    Emoji();

    //绘制表情
    void Judge() const;

    //按钮按下
    void Press() const;

    //按钮未按下
    void Unpress(States s);

    //设置当前图片
    void SetImagine(IMAGE* i);

    //设置坐标
    void SetPos(int px,int py);

    //获取坐标
    pair<int,int> GetPos();

};

#endif //MINESWEEPEREX_EMOJI_H
