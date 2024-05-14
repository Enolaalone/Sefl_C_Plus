#include "Sprite.h"

Sprite::Sprite(int x0,int y0,int r0,COLORREF c):x(x0),y(y0),r(r0),color(c){};//��ʼ����ʱ�������ٸ�ֵ

void Sprite::draw() const{
    setfillcolor(color);
    solidcircle(x,y,r);
}

bool Sprite::collision(const Sprite &another) const{//��ײ����
    return (int)sqrt(pow(x-another.x,2)+pow(y-another.y,2))<r+another.r;
}

void Sprite::SetPos(int px,int py){
    this->x = px;
    this->y = py;
}

pair<int,int> Sprite::GetPos(){
    return pair<int,int>(this->x,this->y);
}

int Sprite::GetR(){
    return this->r;
}
