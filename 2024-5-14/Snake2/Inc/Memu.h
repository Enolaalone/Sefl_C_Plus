#ifndef SNAKE_MEMU_H
#define SNAKE_MEMU_H
#include <graphics.h>
#include <conio.h>

class Menu{
private:
    int event,last;//鼠标当前选中按钮，上一个选中按钮
    int r1[4],r2[4],r3[4];//按钮框设置数据
    RECT R1,R2,R3,R4;//文本框
    LOGFONT f;//字体样式指针
public:
    //初始化位置，大小
    Menu();

    //设置字按钮属性
    void Set();

    //检测鼠标悬置按钮
    int button_judge(int x,int y);

    //初始界面按钮选择
    void ButtonChange(int x,int y);

    //结束界面设置
    void GameOVer();

    //结束界按钮
    void ButtonChange2(int x,int y);

    //返回选框位置
    int GetPos(int n,int k);

};


#endif //SNAKE_MEMU_H
