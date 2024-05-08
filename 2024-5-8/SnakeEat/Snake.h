#ifndef SNAKE_H
#define SNAKE_H
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include<QKeyEvent>

using namespace std;

class Snake:public QWidget
{
public:
    enum Direct{Up,Down,Left,Right};
    int size;//身体肥度
    int r;//半径
    int Width,Height;//sanke移动范围
    int speed;//时间更新速度
    bool state;//游戏状态
    Direct dct;//方向
    QTimer timer;
    pair<int,int> body[500];
    Snake(QWidget *parent=nullptr,int w=0,int h=0,int s=30):QWidget(parent),size(4),r(13),Width(w),Height(h),speed(s),state(false),dct(Right){
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
            this->JudgeBit();
            repaint();//更新
        }


        this->timer.start();
    }

    void JudgeBit(){
        for (int i = 1; i < this->size; ++i) {
            if(this->body[i]==this->body[0])
                this->state=false;
        }
    }

    void ReNewBody(){

        for (int i = this->size-1; i>0; --i) {
            this->body[i] = this->body[i-1];
        }

    }



    void ReSet(int sp){
        this->speed=sp;
        this->timer.setInterval(sp);

        this->size=4;
        this->body[0].first=20;
        this->body[0].second=40;

        this->state=true;//游戏在开始
    }




};
#endif // SNAKE_H
