#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H
#include "Sprite.h"
#include <random>
using namespace std;
class Food:public Sprite{
public:
    //��ʼ��
    Food():Sprite(0,0,10,BLUE){}

    //�趨 ���λ��
    void Random(int width,int height);

    //�ع�����
    void draw() const override ;

    //����ʳ��
//    void ClearFood();
};
#endif //SNAKE_FOOD_H
