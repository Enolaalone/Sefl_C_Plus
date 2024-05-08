#ifndef FORM_H
#define FORM_H
#include "Snake.h"
#include "Food.h"
#include "Menu.h"

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <math.h>

class Window:public QWidget{
public:
    bool f;
    int Width,Height;
    Snake *snake;
    Food *food;
    Menu *menu;
    Window():f(false),Width(1024),Height(2*1024/3){
        setWindowTitle("贪吃蛇");
        setFixedSize(Width,Height);
        this->Set(200);
        this->MenuSet();

    }
    void MenuSet(){
        this->menu = new Menu(this,this->Width,this->Height);
        connect(this->menu,&Menu::EasyTriggered,this,&Window::Easy);
        connect(this->menu,&Menu::MediumTriggered,this,&Window::Medium);
        connect(this->menu,&Menu::HardTriggered,this,&Window::Hard);

    }

    void EndMenu(){
        if (this->menu) {
            this->menu->disconnect();
            this->menu->deleteLater();
            this->menu = nullptr;
        }

        this->menu = new Menu(this,this->Width,this->Height);//结束界面
        this->menu->EndEvent();
        connect(this->menu,&Menu::MediumTriggered,this,&Window::NewMenu);
        this->menu->show();
    }

    void Set(int speed){
        //蛇
        this->snake = new Snake(this,Width,Height,speed);
        this->snake->state=true;

        //食物
        this->food = new Food(this->snake,Width,Height);
        this->food->setGeometry(this->food->x,this->food->y,this->food->r*2,this->food->r*2);//设置食物位置
    }
    void ReRun(int s){
        if (this->menu) {
            this->menu->disconnect();
            this->menu->deleteLater();
            this->menu = nullptr;
        }
        //蛇
        this->snake->ReSet(s);
        //重新设置食物位置
        this->food->SetLocation();
        this->food->move(this->food->x,this->food->y);

    }


    //键盘捕获事件
    void keyPressEvent(QKeyEvent *event)override{
        Q_UNUSED(event);
        switch((int)event->key()){

        case 0x01000012://L
            if(this->snake->dct!=Snake::Right)this->snake->dct=Snake::Left;
            break;
        case 0x01000013://U
            if(this->snake->dct!=Snake::Down)this->snake->dct=Snake::Up;
            break;
        case 0x01000014://R
            if(this->snake->dct!=Snake::Left)this->snake->dct=Snake::Right;
            break;
        case 0x01000015://D
            if(this->snake->dct!=Snake::Up)this->snake->dct=Snake::Down;
            //qDebug()<<"2222";
            break;
        default:
            break;

        }

    }

    void JudgeDtc(){//蛇吃到食物
        if(sqrt(pow(this->food->x+this->food->r-this->snake->body[0].first,2)
                 +pow(this->food->y+this->food->r-this->snake->body[0].second,2))<=this->food->r*2){//蛇头吃到食物
            //重新设置食物位置
            this->food->SetLocation();
            this->food->move(this->food->x,this->food->y);
            //从新设置body长度
            this->snake->size++;

        }
    }


    //游戏结束
    void JudgeEnd(){
        if(!this->snake->state){
            this->ReRun(85);
            this->EndMenu();
        }
    }



    //绘制蛇
    void paintEvent(QPaintEvent *event)override{
        Q_UNUSED(event);

        QPainter painter = QPainter(this);
        JudgeDtc();
        JudgeEnd();

        for (int i = this->snake->size-1; i >0 ; --i) {
            painter.drawEllipse(this->snake->body[i].first,this->snake->body[i].second,this->snake->r,this->snake->r);
        }

        //突出蛇头
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(this->snake->body[0].first,this->snake->body[0].second,this->snake->r,this->snake->r);
        painter.setBrush(QBrush(Qt::black));

        //qDebug()<<"HI";// 测试用

    }
public slots:
    void Easy(){
        //this->ReRun(85);
        this->EndMenu();
    }

    void Medium(){
        this->ReRun(55);
    }

    void Hard(){
        this->ReRun(25);
    }

    void NewMenu(){
        if (this->menu) {
            this->menu->disconnect();
            this->menu->deleteLater();
            this->menu = nullptr;
        }

        this->MenuSet();
        this->menu->show();//新的主界面显示；

    }

};

#endif // FORM_H
