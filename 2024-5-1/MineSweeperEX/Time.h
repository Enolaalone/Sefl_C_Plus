#ifndef MINESWEEPEREX_TIME_H
#define MINESWEEPEREX_TIME_H
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <chrono>

using namespace std;
class Timer{
public:
    int x,y;
    int times;//显示的时间
    chrono::system_clock::time_point l_now;//记录系统时间 戳
    bool state;
    IMAGE *img;
    Timer():x(0),y(0),times(0),l_now(chrono::system_clock::now()),state(false),img(nullptr){}

    void Set(){
        putimage(this->x,this->y,this->img+2);
        putimage(this->x+12,this->y,this->img+2);
        putimage(this->x+24,this->y,this->img+2);
        this->state= false;
    }
    void RecordTime(){
        int g,s,b;

        chrono::duration<int,ratio<1,1000>> d = chrono::duration_cast<chrono::duration<int,ratio<1,1000>>>(chrono::system_clock::now()-this->l_now);//duration<int>类型 记录下差值
        if(this->state&& d>=(chrono::duration<int,ratio<1,1000>> )1000){//大于1000毫s
            this->times++;
            this->l_now = chrono::system_clock::now();
        }

        g = times % 10;
        s = (times / 10) % 10;
        b = times / 100;
        //时间粘贴
        putimage(this->x, this->y, this->img + 2 + b);
        putimage(this->x + 12, this->y, this->img + 2 + s);
        putimage(this->x + 24, this->y, this->img + 2 + g);


    }

};

#endif //MINESWEEPEREX_TIME_H
