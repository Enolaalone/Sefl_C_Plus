#ifndef MINESWEEPEREX_FORM_H
#define MINESWEEPEREX_FORM_H
#include <iostream>
#include "graphics.h"        // 引用图形库头文件
#include "MinesField.h"
#include "Setting.h"
#include "Menu.h"

#define BLOCK 25
#define E 9
#define M 16
#define H 24
using namespace std;

class Form{
public:
    MinesField field;//雷区
    Setting setting;//设置区域
    Menu menu;//菜单区域
    int Width;//宽
    int Height;//高
    bool Running;//运行状态
    //初始化
    Form();

    //初始化
    void Setting(int line,int num);

    //运行游戏
    void Run(int line,int num);

    //处理鼠标点击
    void MouseHandle();

    //检测游戏状态
    void JudgeState(int mx,int my);

    //左键点击事件
    bool Mpos_L(int x,int y,bool press);

    //右键点击事件
    void Mpos_R(int x,int y);

    //从新开始游戏
    void Resetting(int x,int y);
};

#endif //MINESWEEPEREX_FORM_H
