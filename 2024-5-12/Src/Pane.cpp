#include "Pane.h"
using namespace std;
Pane::Pane():x(0),y(0),i(0),j(0),AroundMineNum(0),IsMine(false),ClickMine(false),state(Closed){}

void Pane::Open(IMAGE *img){
    if(this->IsMine){
        if(this->ClickMine) {
            putimage(this->x, this->y, &img[RedMine]);//Õ³ÌùµØÀ×
        }
        else
            putimage(this->x,this->y,&img[WhiteMine]);//Õ³ÌùµØÀ×
    } else if(this->AroundMineNum){
        putimage(this->x,this->y,&img[this->AroundMineNum-1]);
    } else  putimage(this->x,this->y,&img[Zero]);

    this->state=Opened;
}

void Pane::Close(IMAGE *img){
    putimage(this->x,this->y,&img[Cover]);
    this->state=Closed;
};

void Pane::Mark(IMAGE *img){
    putimage(this->x,this->y,&img[Flag1]);
    this->state=Marked;
}


void Pane::SetPos(int px, int py) {
    this->x = px;
    this->y = py;
}

void Pane::SetNumPos(int pi, int pj) {
    this->i = pi;
    this->j = pj;
}

pair<int,int>Pane::GetNumPos(){
    return pair<int,int>(this->i,this->j);
}

void Pane::SetIsMine(bool s){
    this->IsMine = s;
}

bool Pane::GetIsMine(){
    return this->IsMine;
}

void Pane::AddAMN() {
    this->AroundMineNum++;
}

int Pane::GetAMN(){
    return this->AroundMineNum;
}

PaneStates Pane::GetState(){
    return  this->state;
}
void Pane::SetClick(bool s){
    this->ClickMine = s;

}
bool Pane::GetClick(){
    return  this->ClickMine;

}