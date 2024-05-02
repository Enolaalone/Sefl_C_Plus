#ifndef MINESWEEPEREX_PANE_H
#define MINESWEEPEREX_PANE_H

#define Zero 25
#define RedMine 22
#define WhiteMine 8
#define Cover 24
#define Flag 21
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

enum PaneStates{
    Closed,
    Opened,
    Marked
};
class Pane{
public:
    int x,y;//界面地址
    int i,j;//数组坐标
    int AroundMineNum;
    bool IsMine;
    bool ClickMine;//点击的地雷

    PaneStates state;

    Pane():x(0),y(0),i(0),j(0),AroundMineNum(0),IsMine(false),ClickMine(false),state(Closed){

    }
    void Open(IMAGE img[]){
        if(this->IsMine){
            if(this->ClickMine) {
                putimage(this->x, this->y, &img[RedMine]);//粘贴地雷
            }
            else
                putimage(this->x,this->y,&img[WhiteMine]);//粘贴地雷
        } else if(this->AroundMineNum){
            putimage(this->x,this->y,&img[this->AroundMineNum-1]);
        } else  putimage(this->x,this->y,&img[Zero]);

        this->state=Opened;
    }

    void Close(IMAGE img[]){
        putimage(this->x,this->y,&img[Cover]);
        this->state=Closed;
    };

    void Mark(IMAGE img[]){
        putimage(this->x,this->y,&img[Flag]);
        this->state=Marked;

    }


};


#endif MINESWEEPEREX_PANE_H
