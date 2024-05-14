#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H
#include "Sprite.h"
#include <random>
using namespace std;
class Food:public Sprite{
public:
    //初始化
    Food():Sprite(0,0,10,BLUE){}

    //设定 随机位置
    void Random(int width,int height);

    //重构绘制
    void draw() const override ;

    //消除食物
//    void ClearFood();
};
#endif //SNAKE_FOOD_H
