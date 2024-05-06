#ifndef MENU_H
#define MENU_H

#include <QPushButton>
#include <QWidget>

class Menu:public QWidget
{
    Q_OBJECT;//数据信号槽
public:
    int Width,Height;
    //三个选择按键
    QPushButton *easy;
    QPushButton *medium;
    QPushButton *hard;
    Menu(QWidget *parent = nullptr,int w=0,int h=0):QWidget(parent),Width(w),Height(h) {
        setFixedSize(this->Width,this->Height);//设置固定窗口大小

        easy = new QPushButton("鼻涕虫",this);
        medium =new QPushButton("蠕虫",this);
        hard =new QPushButton("巨蟒",this);

        //位置大小
        easy->setGeometry((Width/2)-100,150,200,100);
        medium->setGeometry((Width/2)-100,300,200,100);
        hard->setGeometry((Width/2)-100,450,200,100);
        //设置按下样式
        //easy->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}");
        //medium->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}");
        //hard->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}");

        //悬停样式
        easy->setStyleSheet("QPushButton:hover {"
                            "background-color: rgb(255, 255, 255);"
                            "}");
        //medium->setStyleSheet("QPushButton:hover {background-color: rgb(255, 255, 255);}");
        //hard->setStyleSheet("QPushButton:hover {background-color: rgb(255, 255, 255);}");



        //事件连接
        connect(this->easy,&QPushButton::pressed,this,&Menu::EasyTriggered);
        connect(this->medium,&QPushButton::pressed,this,&Menu::MediumTriggered);
        connect(this->hard,&QPushButton::pressed,this,&Menu::HardTriggered);
    }

signals:
    void EasyTriggered();
    void MediumTriggered();
    void HardTriggered();



};


#endif // MENU_H
