#ifndef SNAKE_H
#define SNAKE_H
#include <QTimer>
#include <QWidget>>
using namespace std;

class Snake:public QWidget
{
public:
    enum Direct{Up,Down,Left,Right};
    int size;
    int x,y;
    int speed;
    int r;
    int Width,Height;
    bool state;
    Direct dct;
    QTimer timer;
    pair<int,int> body[500];
    Snake(QWidget *parent=nullptr,int w=0,int h=0):QWidget(parent),size(4),x(0),y(10),speed(30),r(10),Width(w),Height(h),state(false),dct(Right){
        setFixedSize(this->Width,this->Height);
        this->timer.setInterval(this->speed);//设置调用时间间隔
        connect(&this->timer,&QTimer::timeout,this,&Snake::Move);//连接的都是地址
        this->timer.start();
    }

    void Move(){
        this->timer.stop();
        if(this->state){
            this->ReNewBody();

            switch (dct) {
            case Up:
                this->body[0].second-=this->r;
                if(this->body[0].second<=0)this->body[0].second=Height;
                break;
            case Down:
                this->body[0].second+=this->r;
                if(this->body[0].second>=Height)this->body[0].second=0;
                break;
            case Left:
                this->body[0].first-=this->r;
                if(this->body[0].first<=0)this->body[0].first=Width;
                break;
            case Right:
                this->body[0].first+=this->r;
                if(this->body[0].first>=Width)this->body[0].first=0;
                break;

            default:
                break;
            }
            repaint();
        }


        this->timer.start();
    }


    void ReNewBody(){

        for (int i = this->size-1; i>0; --i) {
            this->body[i] = this->body[i-1];
        }

    }



};
#endif // SNAKE_H
