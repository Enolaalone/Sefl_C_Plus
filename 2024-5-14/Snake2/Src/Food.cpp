#include"Food.h"

void Food::Random(int width,int height){
    random_device rd;//种子
    default_random_engine engine(rd());//引擎
    uniform_int_distribution<int> distribution(1,width/this->r);

    do{
        this->x=this->r*distribution(engine);
        this->y=this->r*distribution(engine);
    }while(this->x>width||this->y>height);

    //cout<<this->x<<" "<<this->y<<endl;

}

void Food::draw() const{
    BeginBatchDraw();
    solidrectangle(this->x,this->y,this->x+this->r,this->y+this->r);// 绘制食物
    EndBatchDraw();
}

//void Food::ClearFood(){
//    clearrectangle(this->x,this->y,this->x+this->r,this->y+this->r);
//}