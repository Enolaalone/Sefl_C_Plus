#ifndef MINESWEEPEREX_EMOJI_H
#define MINESWEEPEREX_EMOJI_H

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

enum States{Happy,Cool,Die};
class Emoji{
public:
    int x,y;
    //bool press;
    States state;
    IMAGE *img;//图库
    Emoji():x(0),y(0),state(Happy),img(nullptr){}

/*    void set(const IMAGE *img){
        if(this->state==States::Happy){//游戏进行
            if(press)
                putimage(this->x, this->y,img+14);
            else    putimage(this->x, this->y,img+13);
            putimage(this->x+2, this->y+2,img+12);
        }
        else if(this->state==States::Cool){//胜利
            if(press)
                putimage(this->x, this->y,img+14);
            else    putimage(this->x, this->y,img+13);
            putimage(this->x+2, this->y+2,img);
        }
        else if(this->state==States::Die){//失败
            if(press)
                putimage(this->x, this->y,img+14);
            else    putimage(this->x, this->y,img+13);
            putimage(this->x+2, this->y+2,img+1);
        }
    }*/

    void Judge(){
        if(this->state==Happy)putimage(this->x+2, this->y+2,this->img+12);
        else if(this->state==Cool)putimage(this->x+2, this->y+2,this->img);
        else if(this->state==Die)putimage(this->x+2, this->y+2,this->img+1);
    }


    void Press(){
        putimage(this->x, this->y,this->img+14);
        Judge();
    }


    void Unpress(States s){
        this->state=s;
        putimage(this->x, this->y,img+13);
        Judge();
    }

};

#endif //MINESWEEPEREX_EMOJI_H
