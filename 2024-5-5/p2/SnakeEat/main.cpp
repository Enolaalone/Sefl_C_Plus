
#include "Snake.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QDebug>

class Window:public QWidget{
public:
    int Width,Height;
    Snake *snake;
    Window():Width(640),Height(480){
        setWindowTitle("贪吃蛇");

        //蛇
        this->snake = new Snake(this,this->Width,this->Height);
        this->Run();
    }

    void Run(){
        this->snake->state=true;
    }

    void paintEvent(QPaintEvent *event)override{
        Q_UNUSED(event);

        QPainter painter = QPainter(this);
        for (int i = this->snake->size-1; i >=0 ; --i) {
            painter.drawEllipse(this->snake->body[i].first,this->snake->body[i].second,this->snake->r,this->snake->r);
        }

        qDebug()<<"HI";

    }


};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();
    return a.exec();
}
