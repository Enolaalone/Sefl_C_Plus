#ifndef MINESWEEPEREX_TIME_H
#define MINESWEEPEREX_TIME_H
#include "Board.h"
#include "graphics.h"
#include <conio.h>
#include <chrono>

using namespace std;
class Timer:public Board{
private:
    //int x,y;//位置
    //int times;//上一次时间
    chrono::system_clock::time_point l_now;//记录系统时间 戳
    bool state;//计时器状态
    //IMAGE *img;//图片地址
public:
    //初始化
    Timer();

    //设置
    void Set();

    //计时显示,重构虚函数
    void Show()override;

    //设置计时器状态
    void SetState(bool s);

};

#endif //MINESWEEPEREX_TIME_H
