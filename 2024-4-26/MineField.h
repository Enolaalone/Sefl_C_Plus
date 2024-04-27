#ifndef MINESWEEPER_MINEFIELD_H
#define MINESWEEPER_MINEFIELD_H
#include "Pane.h"
#include <random>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>//hash表

using namespace std;
enum gameStates{on,end,win};
class MineField{
public:
    int paneLine;//雷区边长
    int paneNum;//雷区边长
    int Num;//记录翻开雷数目
    gameStates state;
    vector<pair<int,int>>nums;
    Pane **panes;
    void Print(){
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                this->panes[i][j].print();
                //cout<< this->panes[i][j].x<<" "<<this->panes[i][j].y<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void Print2(){//打印地雷
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                panes[i][j].print2();
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void Mines(){//雷区初始化
         this->panes=new Pane*[this->paneLine];//指针数组地址分配给 二维指针panes;
        for (int i = 0; i < this->paneLine; ++i) {
            panes[i]= new Pane[this->paneLine];//分配Pane组的内存，并将地址给 pane[i]
        }
    }

    void Random(){//随机数生成；
        unordered_map<int,int>map;
        random_device rd;//随机种子
        default_random_engine engine(rd());//随机数引擎
        uniform_int_distribution<int> distribution(0,this->paneLine-1);//生成随机数范围；

        nums=vector<pair<int,int>>(this->paneNum);//元组矢量,长度为雷数

        for (int i = 0; i < this->paneLine; ) {

            this->nums[i].first= distribution(engine);//first
            this->nums[i].second= distribution(engine);//second
            if(map.find(this->nums[i].first)==map.end()||map[this->nums[i].first]!=this->nums[i].second)
                ++i;//防止重复
            map[this->nums[i].first]=this->nums[i].second;
            //cout<<nums[i].first<<" "<<nums[i].second<<endl;//打印输出
        }

    }
    void MineSet(){//随机埋雷
        this->Random();//分配随机数
        for (int i = 0; i < this->paneLine; ++i) {
            panes[this->nums[i].first][this->nums[i].second].IsMine = true;//设置雷
        }
    }

    Pane** GetAroundPanes(const int x,const int y){//获取周围地雷
        int k[3]={-1,0,1},n=0;
        Pane**Blocks = new Pane*[8]{nullptr};
        //for (int i = 0; i < 8; ++i) Blocks[i]= nullptr;//初值全为null

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if((x+k[i])> -1&&(x+k[i]< this->paneLine)
                && (y+k[j])> -1&&(y+k[j]< this->paneLine)){
                    if(x+k[i]!=x||y+k[j]!=y)//不是当前雷
                    Blocks[n++] = &this->panes[x+k[i]][y+k[j]];//记录下地址

                }
            }
        }
        return Blocks;
    }

    void RecordAroundMines(){//计算周围雷数
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                Pane**Blocks= GetAroundPanes(i,j);
                // 位置
                this->panes[i][j].x=i;
                this->panes[i][j].y=j;

                for (int k = 0; k < 8; ++k) {
                    if(Blocks[k]&&Blocks[k]->IsMine)//Blocks[k]存在
                        this->panes[i][j].AroundMineNum++;//周围雷数加1
                }
                delete Blocks;
            }
        }
    }

    void ExtendingDP(int x,int y){//递归函数
        if(this->panes[x][y].status!=Closed)return;
        if(this->panes[x][y].AroundMineNum>0){
            this->panes[x][y].status=Opened;//周围有雷，翻开结束
            this->JudgeWin();
            return;
        }
        if(this->panes[x][y].IsMine)return;
        this->panes[x][y].status=Opened;
        this->JudgeWin();
        Pane**Blocks= GetAroundPanes(x,y);
        for (int i = 0; i < 8; ++i) {
            if(Blocks[i]&&!(Blocks[i]->IsMine))//Blocks[k]存在
                ExtendingDP(Blocks[i]->x,Blocks[i]->y);
        }
        delete Blocks;
    }

    void Extend(int x,int y){//翻雷函数
        if(this->panes[x][y].IsMine){
            this->panes[x][y].status=Opened;
            this->state =gameStates:: end;
            return;
        } else{
            this->ExtendingDP(x,y);
        }

    }

    void JudgeWin(){
        this->Num++;
        if(this->Num==this->paneLine*this->paneLine-this->paneNum){
            this->state = gameStates:: win;
        }
    }

    MineField():paneLine(0),paneNum(0),Num(0),panes(nullptr),state(on){};//初始化
};


#endif //MINESWEEPER_MINEFIELD_H
