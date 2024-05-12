#include"Timer.h"

Timer::Timer():l_now(chrono::system_clock::now()),state(false){}

void Timer::Set(){
    putimage(this->x,this->y,this->img+2);
    putimage(this->x+12,this->y,this->img+2);
    putimage(this->x+24,this->y,this->img+2);
    this->state= false;
}

void Timer::Show(){
    int g,s,b;

    chrono::duration<int,ratio<1,1000>> d = chrono::duration_cast<chrono::duration<int,ratio<1,1000>>>(chrono::system_clock::now()-this->l_now);//duration<int>类型 记录下差值
    if(this->state&& d>=(chrono::duration<int,ratio<1,1000>> )1000){//大于1000毫s
        this->n++;
        this->l_now = chrono::system_clock::now();
    }

    g = n % 10;
    s = (n / 10) % 10;
    b = n / 100;
    //时间粘贴
    putimage(this->x, this->y, this->img + 2 + b);
    putimage(this->x + 12, this->y, this->img + 2 + s);
    putimage(this->x + 24, this->y, this->img + 2 + g);

}
void Timer::SetState(bool s){
    this->state = s;
}