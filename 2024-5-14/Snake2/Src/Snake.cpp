#include"Snake.h"

Snake::Snake():state(true),TSpeed(100),size(4),speed(10),direct(Right){//初始化
    this->sprites.emplace_back(20,20,5,RGB(138,43,226));
    this-> sprites.emplace_back(20,20,5,WHITE);
    this->sprites.emplace_back(20,20,5,WHITE);
    this->sprites.emplace_back(20,20,5,WHITE);
}

void Snake::draw()const{//画蛇
    BeginBatchDraw();
    //cleardevice();
    for (int i = 0; i < size; ++i) {
        this->sprites[i].draw();
    }
    EndBatchDraw();

}


void Snake::RenewBody(){
     //消除尾巴
        setfillcolor(BLACK);
        solidcircle(this->sprites[this->size-1].GetPos().first,this->sprites[this->size-1].GetPos().second,this->sprites[1].GetR());
    //更新身体
    for(int i=this->size-1;i>0 ;i--)
    {
        this->sprites[i].SetPos(this->sprites[i-1].GetPos().first,this->sprites[i-1].GetPos().second);
    }
}



void Snake::Move(int Width ,int Height){//移动
    while(this->state){
        //更新身体
        this->RenewBody();

        //更新头部
        switch (this->direct) {
            case Up:
                this->sprites[0].SetPos(this->sprites[0].GetPos().first,this->sprites[0].GetPos().second-this->speed);
                if(this->sprites[0].GetPos().second<=0){
                    this->sprites[0].SetPos(this->sprites[0].GetPos().first,Height);
                }
                break;
            case Down:
                this->sprites[0].SetPos(this->sprites[0].GetPos().first,this->sprites[0].GetPos().second+this->speed);
                if(this->sprites[0].GetPos().second>=Height){
                    this->sprites[0].SetPos(this->sprites[0].GetPos().first,0);
                }
                break;
            case Left:
                this->sprites[0].SetPos(this->sprites[0].GetPos().first-this->speed,this->sprites[0].GetPos().second);
                if(this->sprites[0].GetPos().first<=0){
                    this->sprites[0].SetPos(Width,this->sprites[0].GetPos().second);
                }
                break;
            case Right:
                this->sprites[0].SetPos(this->sprites[0].GetPos().first+this->speed,this->sprites[0].GetPos().second);
                if(this->sprites[0].GetPos().first>=Width){
                    this->sprites[0].SetPos(0,this->sprites[0].GetPos().second);
                }
                //cout<< this->sprites[0].x<<endl;测试
                break;
        }
        //画蛇
        this->draw();
        //结束
        this->state = !this->Judge();
        //蛇的更新频率
        this_thread::sleep_for(chrono::milliseconds(this->TSpeed));
    }

}

bool Snake::Judge(){//检测是否咬到自己
    for(int i=this->size-1;i>0 ;i--)
    {
        if(this->sprites[0].collision(this->sprites[i]))
            return true;
    }
    return false;
}

void Snake::EnBody(){
    this-> sprites.emplace_back(20,20,5,WHITE);
    this->size++;
}

void Snake::ReSet(){
    this->state= true;
    this->size = 4;
}

bool Snake::GetState(){
    return this->state;
}

void Snake::SetDir(Dir d){
    this->direct = d;
}

Dir Snake::GetDir(){
    return this->direct;
}


Sprite Snake::GetBody(int i){
    return this->sprites[i];
}

void Snake::SetTspeed(int T){
    this->TSpeed = T;
}