#include "Flags.h"

//void Flags::ShowNum()const{
//    int g,s,b;
//
//    g = num % 10;
//    s = (num / 10) % 10;
//    b = num / 100;
//    //ʱ��ճ��
//    putimage(this->x, this->y, this->img + 2 + b);
//    putimage(this->x + 12, this->y, this->img + 2 + s);
//    putimage(this->x + 24, this->y, this->img + 2 + g);
//};


void Flags::Set(int n){
    this->n= this->UpNum=n;//��Ŀ��ʼ��
    this->state=true;
    this->Show();
}


void Flags::AddOrDes(bool s){
    if(s&&this->n<this->UpNum){//��
        if(!this->state)this->state= true;
        this->n++;
        this->Show();//���¼�����
    }else if(!s&&this->n>0){//��
        this->n--;
        this->Show();
        if(this->n==0)this->state = false;
    }
}

bool Flags::GetState(){
    return this->state;
}