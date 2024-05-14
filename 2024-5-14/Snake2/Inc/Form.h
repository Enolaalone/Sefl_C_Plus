#ifndef SNAKE_FORM_H
#define SNAKE_FORM_H
#include "Snake.h"
#include "Food.h"
#include "Memu.h"
#include <thread>//蛇单独线程控制

using namespace std;
class Form{
private:
    int Width,Height;//窗口大小
    bool running;//游戏状态
    Snake snake;//蛇
    Food food;//食物
    Menu menu;//菜单
public:
    //初始化
    Form();

    //设置对象参数设置及其生成
    void Set();

    //游戏主体
    void Run();

    //读取键盘，改变方向
    void KeyBoard();

    //随机设置食物
    void FoodSet();

    //吃到食物
    void Eatting();

    //鼠标点击按键
    void Mops();

    //游戏结束处理
    void GaneEnd();
};

#endif //SNAKE_FORM_H
