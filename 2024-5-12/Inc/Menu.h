#ifndef MINESWEEPEREX_MENU_H
#define MINESWEEPEREX_MENU_H
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>


class Menu{
public:
    int event,last;//鼠标当前悬置的菜单，和上一个悬置的菜单
    int r1[4],r2[4],r3[4];//选框形状
    RECT R1,R2,R3;//选框
    LOGFONT f;//字体样式指针

    //初始化
    Menu();

    //菜单设置
    void Set();

    //鼠标悬置
    int button_judge(int x,int y);

    //按钮改变颜色
    void ButtonChange(int x,int y);

};
#endif //MINESWEEPEREX_MENU_H
