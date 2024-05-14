#include"Form.h"

Form::Form():running(false),Width(640),Height(480){
    this->Run();
}

void Form::Set(){
    this->snake.ReSet();

    thread Thread1(&Snake::Move,&this->snake,this->Width,this->Height);//�����̣߳�������ĺ�����ָ�룬�����������Ķ���ָ�룬�������
    Thread1.detach();//�ȴ�����

    this->FoodSet();//ʳ������
}

void Form::Run(){//��Ϸ����
    initgraph(this->Width,this->Height);
    this->menu.Set();//�˵�

    //������
    while (!this->running){
        this->Mops();
    }

    //��Ϸ��ʼ��
    this->Set();

    //��Ϸ����
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
    if (_kbhit())//�ж����뻺�������Ƿ������ݣ�_kbhit()��������������
    {
        char ch = (char)_getch();//��������ݽ�����䣬getch��ȡ����������ֵȥ�ı��ٶȵ�ֵ��
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
    while(!this->running){//����
        this->Mops();//�ȴ�����
    }
}