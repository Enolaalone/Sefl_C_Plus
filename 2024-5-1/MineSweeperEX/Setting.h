#ifndef MINESWEEPEREX_SETTING_H
#define MINESWEEPEREX_SETTING_H
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include "Emoji.h"
#include "Time.h"
#include "Flags.h"

class Setting{
public:
    Emoji emoji;
    Timer timer;
    Flags flags;
    IMAGE img[15];
    int x,y,w,h;
    Setting():x(1),y(20),w(0),h(30){//宽会在setBack中设置
        //加载图库,10数字，三表情，两个按键状态
        int k = 10;
        char filename[60];
        for (; k < 22; ++k) {
            sprintf(filename, "D:\\C\\MineSweeperEX\\Resources\\%d.gif", k );
            loadimage(&this->img[k-10],filename);
        }
        for (k=24; k < 27; ++k) {
            sprintf(filename, "D:\\C\\MineSweeperEX\\Resources\\%d.gif", k );
            loadimage(&this->img[k-12],filename);
        }

    }


    void setBack(int Width){//用户区域绘制边框
        this->w=Width;
        setlinecolor(RGB(128,128,128));
        line(this->x,this->y, this->w-2,this->y);
        line(this->x,this->y,this->x,this->y+this->h);
        setlinecolor(WHITE);
        line(this->x,this->y+this->h, this->w-2,this->y+this->h);
        line(this->w-2,this->y,this->w,this->y+this->h);
    };


    void emojiSet(){//设置表情
        this->emoji.y= this->y+2;
        this->emoji.x= this->w/2-12;

        /*this->emoji.state=Happy;
        this->emoji.set(this->img);*/

        this->emoji.img = this->img;//图库交给Emoji
        this->emoji.Unpress(States::Happy);//初始化设置
    }


    void SetTimer(){//设置时间
        this->timer.x = this->w-40;
        this->timer.y = this->y+5;
        this->timer.times=0;
        this->timer.img = this->img;
        this->timer.Set();//快速显示

        //this->timer.state= true;//测试
    }


    void SetFlags(int n){
        this->flags.x=2;
        this->flags.y = this->y+5;
        this->flags.num = 0;
        this->flags.img = this->img;
        this->flags.Set(n);
    }

};


#endif //MINESWEEPEREX_SETTING_H
