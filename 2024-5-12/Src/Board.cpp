#include "Board.h"

Board::Board():x(0),y(0),n(0),img(nullptr){}

void Board::Show() {
    int g,s,b;

    g = this->n % 10;
    s = (this->n / 10) % 10;
    b = this->n / 100;
    //Ê±¼äÕ³Ìù
    putimage(this->x, this->y, this->img + 2 + b);
    putimage(this->x + 12, this->y, this->img + 2 + s);
    putimage(this->x + 24, this->y, this->img + 2 + g);
}
void Board::SetN(int n0){
    this->n = n0;
}
void Board::SetImagine(IMAGE* i){
    this->img = i;
}

void  Board::SetPos(int px,int py){
    this->x = px;
    this->y = py;
}

pair<int,int> Board::GetPos(){
    return pair<int,int>(this->x,this->y);
}