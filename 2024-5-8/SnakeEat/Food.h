#ifndef FOOD_H
#define FOOD_H

#include<QDebug>
#include<QRandomGenerator>
#include<QWidget>
#include<QPainter>

class Food:public QWidget
{
public:
    int x,y;
    int r;
    int Width,Height;
    Food(QWidget *parent=nullptr,int w=0,int h=0):QWidget(parent),x(0),y(0),r(10),Width(w),Height(h) {
        setFixedSize(2*this->r,2*this->r);
        this->setStyleSheet("background-color: rgb(255,255,255)");//设置背景颜色
        this->SetLocation();

    }


    void SetLocation(){
        this->x=QRandomGenerator::global()->bounded(this->Width);
        this->y=QRandomGenerator::global()->bounded(this->Height);
    }



};

#endif // FOOD_H
