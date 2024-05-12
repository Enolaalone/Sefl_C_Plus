#ifndef MINESWEEPEREX_SETTING_H
#define MINESWEEPEREX_SETTING_H
#include "graphics.h"        // 引用图形库头文件
#include <conio.h>
#include "Emoji.h"
#include "Timer.h"
#include "Flags.h"
using namespace std;
class Setting{
public:
    Emoji emoji;//表情按钮
    Timer timer;//计时器
    Flags flags;//计数器
    IMAGE img[15];//图库
    int x,y,w,h;//位置，长，宽
    //初始化
    Setting();

    //用户区域绘制边框
    void setBack(int Width);

    //设置表情
    void emojiSet();

    //设置时间
    void SetTimer();

    //设置旗子
    void SetFlags(int n);

};


#endif //MINESWEEPEREX_SETTING_H
