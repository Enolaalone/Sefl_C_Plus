#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H


using namespace std;
enum States{Opened,Closed,Marked};//×´Ì¬
class Pane{
public:
    bool IsMine;
    int AroundMineNum;
    int x,y;
    States status;//×´Ì¬

    void print(){
        switch ((int)this->status) {
            case 0:
                if(!this->IsMine){
                    if(!this->AroundMineNum)
                        cout<<"¡õ  ";
                    else cout<<this->AroundMineNum<<"  ";
                }
                else cout<<"*  ";
                break;
            case 1:
                cout<<"¡ö  ";//À×¿é
                break;
            case 2:
                cout<<"¡ø  ";//Æì×Ó
                break;
        }
    }
    //²âÊÔ
    void print2(){
        if(this->IsMine)
            cout<<"*  ";
        else cout<<"¡ö  ";//À×¿é
    }
    Pane():IsMine(false),AroundMineNum(0),x(0),y(0),status(Closed){}//³õÊ¼»¯

};





#endif //MINESWEEPER_MINE_H
