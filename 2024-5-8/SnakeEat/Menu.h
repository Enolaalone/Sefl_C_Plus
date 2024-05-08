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

        this->ButtonStyle();

        //事件连接
        connect(this->easy,&QPushButton::clicked,this,&Menu::EasyTriggered);
        connect(this->medium,&QPushButton::clicked,this,&Menu::MediumTriggered);
        connect(this->hard,&QPushButton::clicked,this,&Menu::HardTriggered);
    }

    void ButtonStyle(){
        //设置按下样式
        easy->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}"
                            "QPushButton:hover {background-color: rgb(0,0,0);}"
                            );
        medium->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}"
                              "QPushButton:hover {background-color: rgb(0,0,0);}"
                              );
        hard->setStyleSheet("QPushButton:pressed {background-color: #F5F5F5;}"
                            "QPushButton:hover {background-color: rgb(0,0,0);}"
                            );

    }

    void EndEvent(){//重构重启界面
        //端口连接
        this->DeleteConnect();

        delete this->medium;
        this->medium=nullptr;
        this->easy->hide();
        this->hard->hide();
        //事件解绑

        //重启按钮设置
        medium =new QPushButton("失败了点击重新在开始吧！！",this);
        medium->setGeometry((Width/2)-100,300,200,100);
        connect(this->medium,&QPushButton::clicked,this,&Menu::MediumTriggered);
    }

    void DeleteConnect(){
        easy->disconnect();
        medium->disconnect();
        hard->disconnect();
    }

signals:
    void EasyTriggered();
    void MediumTriggered();
    void HardTriggered();

};


#endif // MENU_H
