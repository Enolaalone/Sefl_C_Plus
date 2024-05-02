#ifndef MINESWEEPEREX_FORM_H
#define MINESWEEPEREX_FORM_H
#include <iostream>
#include <graphics.h>		// 引用图形库头文件
#include "MinesField.h"
#include "Setting.h"
#include "Menu.h"
using namespace std;

class Form{
public:
    MinesField field;
    Setting setting;
    Menu menu;
    int Width;
    int Height;
    bool Running;
    Form():Width(225),Height(290),Running(true){
        Run(9,10);

    }


    void Setting(int line,int num){//初始化

        //测试：
        this->field.paneLine=line;
        this->field.paneNum=num;
        //雷区
        this->field.ReFlied();
        this->field.Mines(this->Height);//雷区初始化
        this->field.MineSet();//设置地雷
        this->field.RecordAroundMines();//查询周围地雷数目
        this->field.Print();//打印
        //用户区域
        this->setting.setBack(this->Width);//区域框
        this->setting.emojiSet();//按钮
        this->setting.SetTimer();//计时器
        this->setting.SetFlags(this->field.paneNum);//计数器
        //难度
        this->menu.Set();

    }

    void Run(int line,int num){
        initgraph(this->Width,this->Height);//窗口
        setbkcolor(RGB(204,204,204));
        cleardevice();
        this->Setting(line,num);

        while(this->Running){
            this->setting.timer.RecordTime();
            while(MouseHit()){//检测到鼠标点击
                MouseHandle();
            }
        }
    }


    void MouseHandle(){//处理鼠标点击
        MOUSEMSG m=GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN://左键按下
                cout<<m.x<<","<<m.y<< endl;//打印鼠标位置
                this->Mpos_L(m.x,m.y, true);//点击事件
                this->JudgeState(m.x,m.y);
                break;
            case WM_RBUTTONDOWN://右键按下
                this->Mpos_R(m.x,m.y);//左键插旗
                this->JudgeState(m.x,m.y);

                break;
            case WM_LBUTTONUP://模拟点击
                this->Resetting(m.x,m.y);
                if(this->Mpos_L(m.x,m.y, false))
                    this->Setting(this->field.paneLine, this->field.paneNum);
                break;
            case WM_MOUSEMOVE://检测菜单
                this->menu.ButtonChange(m.x,m.y);
                break;
            case WM_CLOSE://关闭
                this->Running= false;
                // 关闭绘图窗口
                closegraph();
                break;
        }

    }


    void JudgeState(int mx,int my){
        if(!this->setting.flags.state){//旗子插完
            if(this->field.JudgeWin2())this->field.state=gameStates::win;
        }

        if(this->field.state==gameStates::on && mx>=0&&mx<=this->Width&& my>= this->Height-(this->field.paneLine*25))this->setting.timer.state= true;
        else if(this->field.state==gameStates::win){
            this->setting.emoji.Unpress(States::Cool);
            this->setting.timer.state= false;//停止计时
        }
        else if(this->field.state==gameStates::end){
            this->setting.emoji.Unpress(States::Die);
            this->setting.timer.state= false;//停止计时
        }
    }


    bool Mpos_L(int x,int y,bool press){//左键点击事件
        int Bx=this->setting.emoji.x;
        int By=this->setting.emoji.y;
        if(this->field.state==on&&x>=0&&x<this->Width && y>=(Height-25* this->field.paneLine)&&y<=Height&&press) {//点击雷区
            int j=x/25;
            int i=(y-(Height-25 * this->field.paneLine))/25;
            if(this->field.panes[i][j].state==Closed){
                if(this->field.panes[i][j].IsMine){
                    this->field.JudgeEnd(i,j);
                } else{
                    this->field.ExtendingDP(i,j);
                }
            }
            else if(this->field.panes[i][j].state==Marked){
                this->field.panes[i][j].Close(this->field.img);
                this->setting.flags.AddOrDes(true);
            }


        }
        else if(x>=Bx&&x<=Bx+25&&y>=By&&y<=By+25&&press){
            this->setting.emoji.Press();

        }
        else if(x>=Bx&&x<=Bx+25&&y>=By&&y<=By+25&&!press){
            this->setting.emoji.Unpress(States::Happy);
            return true;
        }
        return false;
    }


    void Mpos_R(int x,int y){
        if(this->field.state==on&&x>=0&&x<this->Width && y>=(Height-25* this->field.paneLine)&&y<=Height) {//点击雷区
            int j=x/25;
            int i=(y-(Height-25 * this->field.paneLine))/25;
            if(this->field.panes[i][j].state==Closed&&this->setting.flags.state) {//雷块未翻开，而且还有旗子
                this->field.panes[i][j].Mark(this->field.img);
                this->setting.flags.AddOrDes(false);//旗子减1
            }
        }
    }

    void Resetting(int x,int y){
        if(x>=this->menu.r1[0] && x<= this->menu.r1[2] && y>=this->menu.r1[1]  && y<=this->menu.r1[3] ){//简单
            closegraph();
            this->Width=225;
            this->Height=290;
            this->Run(9,10);
        };
        if(x>=this->menu.r2[0] && x<= this->menu.r2[2] && y>=this->menu.r2[1]  && y<=this->menu.r2[3] ){//中等
            closegraph();
            this->Width=25*16;
            this->Height=25*16+65;
            this->Run(16,40);
        };
        if(x>=this->menu.r3[0] && x<= this->menu.r3[2] && y>=this->menu.r3[1]  && y<=this->menu.r3[3] ){//困难
            closegraph();
            this->Width=25*24;
            this->Height=25*24+65;
            this->Run(24,100);
        };


    }
};

#endif //MINESWEEPEREX_FORM_H
