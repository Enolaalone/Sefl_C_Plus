#include"Form.h"

Form::Form():running(false),Width(640),Height(480){
    this->Run();
}

void Form::Set(){
    this->snake.ReSet();

    thread Thread1(&Snake::Move,&this->snake,this->Width,this->Height);//创建线程，传入类的函数的指针，传入类衍生的对象指针，传入参数
    Thread1.detach();//等待结束

    this->FoodSet();//食物设置
}

void Form::Run(){//游戏主体
    initgraph(this->Width,this->Height);
    this->menu.Set();//菜单

    //主界面
    while (!this->running){
        this->Mops();
    }

    //游戏初始化
    this->Set();

    //游戏进行
    while(this->running){
        this->KeyBoard();
        this->Eatting();
        if(!this->snake.GetState())this->running = false;
    }

    this->GaneEnd();

    _getch();
    closegraph();
}

void Form::KeyBoard(){
    if (_kbhit())//判断输入缓冲区中是否有内容，_kbhit()不会阻塞函数。
    {
        char ch = (char)_getch();//如果有内容进入语句，getch获取缓冲区的数值去改变速度的值。
        switch (ch)
        {
            case'A':
            case'a':
                if(this->snake.GetDir()!=Right)this->snake.SetDir(Left);
                break;
            case'S':
            case's':
                if(this->snake.GetDir()!=Up)this->snake.SetDir(Down);
                break;
            case'W':
            case'w':
                if(this->snake.GetDir()!=Down)this->snake.SetDir(Up);
                break;
            case'D':
            case'd':
                if(this->snake.GetDir()!=Left)this->snake.SetDir(Right);
                break;
            default:
                break;
        }
    }

}

void Form::FoodSet(){
    this->food.Random(this->Width,this->Height);
    this->food.draw();
}

void Form::Eatting(){
    if(this->food.collision(this->snake.GetBody(0))){
        this->snake.EnBody();

        cleardevice();
        this->FoodSet();
    }
}

void Form::Mops(){
    while(MouseHit()){
        MOUSEMSG m=GetMouseMsg();
        if(this->snake.GetState())
            this->menu.ButtonChange(m.x,m.y);
        else{
            this->menu.ButtonChange2(m.x,m.y);
        }
        if(m.uMsg==WM_LBUTTONDOWN&&this->snake.GetState()){
            if(m.x>this->menu.GetPos(1,0)&&m.x<this->menu.GetPos(1,2)&&m.y>this->menu.GetPos(1,1)&&m.y<this->menu.GetPos(1,3)){
                cleardevice();
                this->snake.SetTspeed(90);
                this->running= true;
            }
            else if(m.x>this->menu.GetPos(2,0)&&m.x<this->menu.GetPos(2,2)&&m.y>this->menu.GetPos(2,1)&&m.y<this->menu.GetPos(2,3)){
                    cleardevice();
                    this->snake.SetTspeed(60);
                    this->running= true;
            }
            else if(m.x>this->menu.GetPos(3,0)&&m.x<this->menu.GetPos(3,2)&&m.y>this->menu.GetPos(3,1)&&m.y<this->menu.GetPos(3,3)){
                cleardevice();
                this->snake.SetTspeed(30);
                this->running= true;
            }

        }
        else if(m.uMsg==WM_LBUTTONDOWN&&!this->snake.GetState()){
            cleardevice();
            this->Run();
        }

    }
}

void Form::GaneEnd(){
    this->menu.GameOVer();
    while(!this->running){//结束
        this->Mops();//等待重启
    }
}