#include <iostream>
#include "MineField.h"
using namespace std;

class MineSweeper{
public:
    MineField field;
    int location_l,location_r;//记录选位置

    void Running(){
        this->Setting();
        while(1){
            cout<<"输入翻开的位置：x,y"<<endl;
            //cin.clear();
            scanf("%d,%d",&this->location_l,&this->location_r);

            this->field.Extend(this->location_l-1,this->location_r-1);

            this->field.Print2();
            this->field.Print();
            if(this->field.state== on)continue;
            else if(this->field.state == win){
                cout<<"恭喜通关！";
                break;
            } else{
                cout<<"踩雷游戏失败！";
                break;
            }
        }


    }
    void Setting(){
        /*cout<<"输入雷区边长：（个）"<<endl;
        scanf("%d",&this->field.paneLine);
        cout<<"输入雷数：（个）"<<endl;
        scanf("%d",&this->field.paneNum);*/

        //测试：
        this->field.paneLine=10;
        this->field.paneNum=10;

        this->field.Mines();//雷区初始化
        this->field.MineSet();//设置地雷
        this->field.Print2();//测试打印

        this->field.RecordAroundMines();//查询周围地雷数目
        this->field.Print();//打印

    }


    MineSweeper():location_l(0),location_r(0){}//初始化
};




int main() {
    MineSweeper mineSweeper;
    mineSweeper.Running();



    return 0;
}
