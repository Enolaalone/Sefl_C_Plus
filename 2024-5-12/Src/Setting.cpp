#include"Setting.h"

Setting::Setting():x(1),y(20),w(0),h(30){//宽会在setBack中设置
    //加载图库,10数字，三表情，两个按键状态
    int k = 10;
    char filename[60];
    for (; k < 22; ++k) {
        sprintf(filename, "..\\Resources\\%d.gif", k );
        loadimage(&this->img[k-10],filename);
    }
    for (k=24; k < 27; ++k) {
        sprintf(filename, "..\\Resources\\%d.gif", k );
        loadimage(&this->img[k-12],filename);
    }

}

void Setting::setBack(int Width){//用户区域绘制边框
    this->w=Width;
    setlinecolor(RGB(128,128,128));
    line(this->x,this->y, this->w-2,this->y);
    line(this->x,this->y,this->x,this->y+this->h);
    setlinecolor(WHITE);
    line(this->x,this->y+this->h, this->w-2,this->y+this->h);
    line(this->w-2,this->y,this->w,this->y+this->h);
};


void Setting::emojiSet(){//设置表情
    this->emoji.SetPos(this->w/2-12,this->y+2);

    /*this->emoji.state=Happy;
    this->emoji.set(this->img);*/

    this->emoji.SetImagine(this->img);//图库交给Emoji
    this->emoji.Unpress(States::Happy);//初始化设置
}


void Setting::SetTimer(){//设置时间

    this->timer.SetPos(this->w-40,this->y+5);
    this->timer.SetN(0);
    this->timer.SetImagine(this->img);
    this->timer.Set();//快速显示

    //this->timer.state= true;//测试
}


void Setting::SetFlags(int n){
    this->flags.SetPos(2,this->y+5);
    this->flags.SetN(0);
    this->flags.SetImagine(this->img);
    this->flags.Set(n);
}