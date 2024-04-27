#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H


using namespace std;
enum States{Opened,Closed,Marked};//״̬
class Pane{
public:
    bool IsMine;
    int AroundMineNum;
    int x,y;
    States status;//״̬

    void print(){
        switch ((int)this->status) {
            case 0:
                if(!this->IsMine){
                    if(!this->AroundMineNum)
                        cout<<"��  ";
                    else cout<<this->AroundMineNum<<"  ";
                }
                else cout<<"*  ";
                break;
            case 1:
                cout<<"��  ";//�׿�
                break;
            case 2:
                cout<<"��  ";//����
                break;
        }
    }
    //����
    void print2(){
        if(this->IsMine)
            cout<<"*  ";
        else cout<<"��  ";//�׿�
    }
    Pane():IsMine(false),AroundMineNum(0),x(0),y(0),status(Closed){}//��ʼ��

};





#endif //MINESWEEPER_MINE_H
