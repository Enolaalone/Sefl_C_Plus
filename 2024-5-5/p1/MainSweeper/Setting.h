#ifndef SETTING_H
#define SETTING_H
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include<QColor>
#include "Emoji.h"
#include "Timer.h"
#include "Flag.h"
class Setting:public QWidget
{
public:
    int Width,Height;
    int flag;
    Emoji *emoji;
    Timer *timer;
    FlagRecord *flagrecord;
    Setting(QWidget *parent = nullptr,int w=100,int h=50,int f=0): QWidget(parent),Width(w),Height(h),flag(f){
        this->setFixedSize(this->Width,this->Height);

        //表情初始化
        this->emoji = new Emoji(this);
        this->emoji->setGeometry((this->Width-this->emoji->size)/2,5,this->emoji->size,this->emoji->size);

        //计时器初始化
        this->timer = new Timer(this);
        this->timer->setGeometry(this->Width-this->timer->Width-1,5,this->timer->Width,this->timer->Height);

        //计数器初始化
        this->flagrecord = new FlagRecord(this,this->flag);
        this->flagrecord->setGeometry(1,5,this->flagrecord->Width,this->flagrecord->Height);

    }


    void emojiSet(bool k,int s){
        this->emoji->press=k;//是否按下
        this->emoji->State(s);//事件状态
    }

    void timeSet(bool k){
        this->timer->state=k;
    }

    void flagSet(int k){
        this->flagrecord->state=k;
    }


    void paintEvent(QPaintEvent *event)override{
        Q_UNUSED(event);

        QPainter painter = QPainter(this);
        QColor color;

        color.setRgb(128,128,128);
        painter.setPen(color);
        painter.drawLine(1,1,this->Width,1);
        painter.drawLine(1,1,1,this->Height);

        color.setRgb(255,255,255);
        painter.setPen(color);
        painter.drawLine(1,this->Height-1,this->Width,this->Height-1);
        painter.drawLine(this->Width-1,1,this->Width-1,this->Height);
    }


};
#endif // SETTING_H
