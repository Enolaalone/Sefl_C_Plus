#ifndef MINESWEEPEREX_FLAGS_H
#define MINESWEEPEREX_FLAGS_H

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

class Flags{
public:
    int x,y;
    int UpNum;
    int num;//侠士个数
    bool state;//计数器状态
    IMAGE *img;
    Flags():x(0),y(0),num(0),UpNum(0),state(true),img(nullptr){}


    void ShowNum(){
        int g,s,b;

        g = num % 10;
        s = (num / 10) % 10;
        b = num / 100;
        //时间粘贴
        putimage(this->x, this->y, this->img + 2 + b);
        putimage(this->x + 12, this->y, this->img + 2 + s);
        putimage(this->x + 24, this->y, this->img + 2 + g);
    };


    void Set(int n){
        this->num= this->UpNum=n;//数目初始化
        this->state=true;
        this->ShowNum();
    }
    

    void AddOrDes(bool s){
        if(s&&this->num<this->UpNum){//加
            if(!this->state)this->state= true;
            this->num++;
            this->ShowNum();//更新计数器
        }else if(!s&&this->num>0){//减
            this->num--;
            this->ShowNum();
            if(this->num==0)this->state = false;
        }
    }

};

#endif //MINESWEEPEREX_FLAGS_H
