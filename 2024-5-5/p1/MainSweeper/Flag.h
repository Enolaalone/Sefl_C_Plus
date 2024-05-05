#ifndef FLAG_H
#define FLAG_H
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class FlagRecord:public QWidget{
public:
    enum Nums{D0,D1,D2,D3,D4,D5,D6,D7,D8,D9};
    QMap<Nums,QPixmap>map;
    bool state;
    int num,l_num;
    int size;
    int Width;
    int Height;
    int g,s,b;
    QTimer *flagrecord;
    FlagRecord(QWidget *parent=nullptr,int n=0):QWidget(parent),state(false),num(n),size(12),Height(25),g(0),s(0),b(0),flagrecord(nullptr){
        this->l_num=this->num;
        this->Width = this->size*3;
        this->setFixedSize(this->Width,this->Height);
        this->SetMap();

        this->ShowNum(-1);

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


    void ShowNum(int k){

        if(k==1){
            this->num++;
            if(!this->state)this->state=true;
        }
        else if(!k){
            this->num--;
            if(!this->num){
                this->state=false;
            }
        }
        g=this->num%10;
        s=this->num/10%10;
        b=this->num/100;
        repaint();

    }

    void RE(){
        this->state = false;
        this->num = this->l_num;
        this->ShowNum(-1);

    }

    void paintEvent(QPaintEvent *event){
        Q_UNUSED(event);

        QPainter painter = QPainter(this);

        painter.drawPixmap(0,0,map[(Nums)b]);
        painter.drawPixmap(this->size*1,0,map[(Nums)s]);
        painter.drawPixmap(this->size*2,0,map[(Nums)g]);

    }


};
#endif // FLAG_H
