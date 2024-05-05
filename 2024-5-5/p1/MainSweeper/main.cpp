#include "PanesField.h"
#include "Setting.h"
#include "Menu.h"

#include <QApplication>
#include <QLocale>
#include <QWidget>//窗体
#include <QMouseEvent>//鼠标点击事件



class Window:public QWidget{
    public:
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int dtc;//非雷区宽度
    PanesField *panesField;
    Setting *setting;
    Menu *menu;
    Window():WINDOW_WIDTH(0),WINDOW_HEIGHT(0),dtc(70),panesField(nullptr){
        setWindowTitle("扫雷");
        this->setStyleSheet("background-color: rgb(204,204,204)");//设置背景颜色

        this->Set(10,9,9);
     }

    void Set(int n,int w,int l){
        this->panesField = new PanesField(this,n,w,l);//创建控件

        //根据地雷数量，设置窗口大小
        this->WINDOW_WIDTH=this->panesField->BLOCK_WIDTH*this->panesField->COL_COUNT;
        this->WINDOW_HEIGHT=this->panesField->BLOCK_WIDTH*this->panesField->ROW_COUNT+this->dtc;


        this->setFixedSize(this->WINDOW_WIDTH,this->WINDOW_HEIGHT);//窗口size

        //设置区域
        this->setting = new Setting(this,this->WINDOW_WIDTH,35,this->panesField->PaneNum);
        this->setting->setGeometry(0,30,this->setting->Width,this->setting->Height);


        //雷区启动
        this->panesField->setGeometry(0,this->dtc,this->panesField->BLOCK_WIDTH*this->panesField->COL_COUNT,this->panesField->BLOCK_WIDTH*this->panesField->ROW_COUNT);
        this->Run();

        // 菜单区
        this->menu = new Menu(this);
        this->menu->setGeometry(1,1,70,23);
        connect(this->menu,&Menu::EasyTriggered,this,&Window::Easy);
        connect(this->menu,&Menu::MediumTriggered,this,&Window::Medium);
        connect(this->menu,&Menu::HardTriggered,this,&Window::Hard);

        this->menu->show();
        this->panesField->show();
        this->setting->show();
    }
     void Run(){
         //雷区
         this->panesField->Re();
         this->panesField->PaneRandom();
         this->panesField->GetArroundPaneNum();

     }

     void ReGame(){//重启游戏
         //雷区
         this->Run();

         //设置区
         this->setting->emojiSet(false,1);
         this->setting->timer->RE();
         this->setting->flagrecord->RE();
     }

     void GameState(){
         if(this->panesField->state==PanesField::Begin){
             this->panesField->state = PanesField::Process;
             this->setting->timeSet(true);
            this->setting->flagSet(1);
         }
        else if(this->panesField->state==PanesField::Win){
             this->setting->emojiSet(false,2);//胜利
             this->setting->timeSet(false);
             this->setting->flagSet(0);
         }

        else if(this->panesField->state==PanesField::End){
             this->setting->emojiSet(false,3);//失败
             this->setting->timeSet(false);
             this->setting->flagSet(0);
         }
     }


     void mousePressEvent(QMouseEvent *event)override{//鼠标点击事件

        const int x=event->x()/this->panesField->BLOCK_WIDTH,y=(event->y()-this->dtc)/this->panesField->BLOCK_WIDTH;
         //点击雷区事件处理
         if(event->x()>=0&&event->x()<=this->WINDOW_WIDTH&&event->y()>=this->dtc&&event->y()<=this->WINDOW_HEIGHT){
            if(this->panesField->state==PanesField::Win||this->panesField->state==PanesField::End)return;//非游戏进行中不检查
            else{
                this->GameState();
                if(event->button()==Qt::LeftButton){//左键
                    if(this->panesField->view[x][y]==this->panesField->FLAG){
                        this->panesField->view[x][y]=this->panesField->U1;
                        this->setting->flagrecord->ShowNum(true);
                    }
                    else if(this->panesField->view[x][y]==this->panesField->U1){
                        if(this->panesField->data[x][y]==this->panesField->BOOM){
                            this->panesField->view[x][y]=this->panesField->RBOOM;//--------------EXtend

                            this->panesField->OverShowAllMines();
                        }
                        else{//递归
                            this->panesField->Extend(x,y);
                        }

                    }

                }

                else if(event->button()==Qt::RightButton){//右键
                    this->panesField->view[x][y]=this->panesField->FLAG;
                    this->setting->flagrecord->ShowNum(false);
                    if(!this->setting->flagrecord->state){
                        this->panesField->JudgeWin2();
                    }

                }
            }

             //检测游戏是否结束
             this->GameState();
         }

         //按钮点击事件
         else if(event->x()>=(this->setting->Width-this->setting->emoji->size)/2
                    &&event->x()<=this->setting->emoji->size+(this->setting->Width-this->setting->emoji->size)/2
                    &&event->y()>=25&&event->y()<=25+this->setting->emoji->size){
             this->setting->emojiSet(true,0);
         }

        repaint();//重新绘制图形
     }



     void mouseReleaseEvent(QMouseEvent *event)override{//鼠标弹起事件，主要检测是否重启
         if(event->x()>=(this->setting->Width-this->setting->emoji->size)/2
             &&event->x()<=this->setting->emoji->size+(this->setting->Width-this->setting->emoji->size)/2
             &&event->y()>=25&&event->y()<=25+this->setting->emoji->size){


             this->ReGame();

         }
         repaint();//重新绘制图形
     }

     void Delete(){
         delete this->panesField;
         delete this->setting;
         delete this->menu;

         this->panesField = nullptr;
         this->setting = nullptr;
         this->menu = nullptr;
     }

 public slots:
     void Easy(){
         this->Delete();
         this->Set(10,9,9);
     };
     void Medium(){
        this->Delete();
         this->Set(40,16,16);
     };
     void Hard(){
         this->Delete();
         this->Set(100,24,24);
     };


} ;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window window;
    window.show();

    return a.exec();
}
