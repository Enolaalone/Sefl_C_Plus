#ifndef TIMER_H
#define TIMER_H
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QTimer>

class Timer:public QWidget{
public:
    enum Nums{D0,D1,D2,D3,D4,D5,D6,D7,D8,D9};
    QMap<Nums,QPixmap>map;
    bool state;
    int time;
    int size;
    int Width;
    int Height;
    int g,s,b;
    QTimer *Time;
    Timer(QWidget *parent=nullptr):QWidget(parent),state(false),time(0),size(12),Height(25),g(0),s(0),b(0),Time(nullptr){
        this->Width = this->size*3;
        this->setFixedSize(this->Width,this->Height);
        this->SetMap();

        //定时器
        this->Time = new QTimer;
        this->Time->setInterval(1000);//间隔1秒
        connect(this->Time,&QTimer::timeout,this,&Timer::ShowTime);
        this->Time->start();

     }

    void SetMap(){
        map.insert(D0,QPixmap(":/Resources/download00.gif"));
        map.insert(D1,QPixmap(":/Resources/download01.gif"));
        map.insert(D2,QPixmap(":/Resources/download02.gif"));
        map.insert(D3,QPixmap(":/Resources/download03.gif"));
        map.insert(D4,QPixmap(":/Resources/download04.gif"));
        map.insert(D5,QPixmap(":/Resources/download05.gif"));
        map.insert(D6,QPixmap(":/Resources/download06.gif"));
        map.insert(D7,QPixmap(":/Resources/download07.gif"));
        map.insert(D8,QPixmap(":/Resources/download08.gif"));
        map.insert(D9,QPixmap(":/Resources/download09.gif"));

    }


    void ShowTime(){
        this->Time->stop();

        if(this->state){
            this->time++;
        }
        g=this->time%10;
        s=this->time/10%10;
        b=this->time/100;
        repaint();
        this->Time->start();
    }

    void paintEvent(QPaintEvent *event){
        Q_UNUSED(event);

        QPainter painter = QPainter(this);

        painter.drawPixmap(0,0,map[(Nums)b]);
        painter.drawPixmap(this->size*1,0,map[(Nums)s]);
        painter.drawPixmap(this->size*2,0,map[(Nums)g]);

    }

    void RE(){
        this->state = false;
        this->time = 0;
    }
};

#endif // TIMER_H
