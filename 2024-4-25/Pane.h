#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H


class Pane{
private:
    enum States{Opened,Marked,Closed};//状态
public:
    bool IsMine;
    int AroundMineNum;
    States status;//状态

    void print(){
        switch ((int)this->status) {
            case 0:
                if(!this->IsMine)
                std::cout<<"\u25A0";
                break;
            case 1:
                std::cout<<"\u25A1";
                break;
            case 2:
                std::cout<<"";
                break;
        }
    }
    Pane():IsMine(false),AroundMineNum(0),status(Closed){}//初始化

};





#endif //MINESWEEPER_MINE_H
