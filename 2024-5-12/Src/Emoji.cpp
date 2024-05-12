#include "Emoji.h"
Emoji::Emoji():x(0),y(0),state(Happy),img(nullptr){}

void Emoji::Judge() const{
    if(this->state==Happy)putimage(this->x+2, this->y+2,this->img+12);
    else if(this->state==Cool)putimage(this->x+2, this->y+2,this->img);
    else if(this->state==Die)putimage(this->x+2, this->y+2,this->img+1);
}

void Emoji::Press()const{
    putimage(this->x, this->y,this->img+14);
    Judge();
}

void Emoji::Unpress(States s){
    this->state = s;
    putimage(this->x, this->y,img+13);
    Judge();
}

void Emoji::SetImagine(IMAGE* i){
    this->img = i;
}

void Emoji::SetPos(int px,int py){
    this->x = px;
    this->y = py;
}
pair<int,int> Emoji::GetPos(){
    return pair<int,int>(this->x,this->y);
}