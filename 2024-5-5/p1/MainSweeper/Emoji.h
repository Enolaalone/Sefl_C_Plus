#ifndef EMOJI_H
#define EMOJI_H
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class Emoji:public QWidget
{

public:
    enum Block{
        COOL,DEAD,SMILE,U0,U1
    };
    int size;
    bool press;
    Block data[2];
    QMap<Block,QPixmap>map;
    Emoji(QWidget *parent = nullptr):QWidget(parent),size(25),press(false){
        this->SetMap();
        this->setFixedSize(this->size,this->size);//设置固定大小
        this->State(1);
    }

    void SetMap(){

        this->map.insert(COOL,QPixmap(":/Resources/cool1.gif"));
        this->map.insert(DEAD,QPixmap(":/Resources/dead1.gif"));
        this->map.insert(SMILE,QPixmap(":/Resources/smile1.gif"));
        this->map.insert(U0,QPixmap(":/Resources/under0.gif"));
        this->map.insert(U1,QPixmap(":/Resources/under1.gif"));
    }

    void Press(){//按下状态
        if(this->press)this->data[0]=U1;
        else this->data[0]=U0;
    }

    void State(int s){
        this->Press();
        switch (s) {
        case 1:
            this->data[1]=SMILE;
            break;
        case 2:
            this->data[1]=COOL;
            break;
        case 3:
            this->data[1]=DEAD;
            break;
        default:
            break;
        }

        repaint();
    }


    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event);

        QPainter painter = QPainter(this);

        painter.drawPixmap(0,0,this->map[this->data[0]]);
        painter.drawPixmap(2,2,this->map[this->data[1]]);

    }
};
#endif // EMOJI_H
