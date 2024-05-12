#ifndef MINESWEEPEREX_FLAGS_H
#define MINESWEEPEREX_FLAGS_H

#include "graphics.h"        // 引用图形库头文件
#include <conio.h>
#include "Board.h"
class Flags:public Board{
private:
    int UpNum;//初始个数
    bool state;//计数器状态
public:
    //初始化
    Flags():UpNum(0),state(true){}

//    //显示数字
//    void ShowNum()const;

    //数目初始化
    void Set(int n);
    
    //旗子数目加减
    void AddOrDes(bool s);

    //获取状态
    bool GetState();

};

#endif //MINESWEEPEREX_FLAGS_H
