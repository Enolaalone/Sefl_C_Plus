#include"Food.h"

void Food::Random(int width,int height){
    random_device rd;//����
    default_random_engine engine(rd());//����
    uniform_int_distribution<int> distribution(1,width/this->r);

    do{
        this->x=this->r*distribution(engine);
        this->y=this->r*distribution(engine);
    }while(this->x>width||this->y>height);

    //cout<<this->x<<" "<<this->y<<endl;

}

void Food::draw() const{
    BeginBatchDraw();
    solidrectangle(this->x,this->y,this->x+this->r,this->y+this->r);// ����ʳ��
    EndBatchDraw();
}

//void Food::ClearFood(){
//    clearrectangle(this->x,this->y,this->x+this->r,this->y+this->r);
//}