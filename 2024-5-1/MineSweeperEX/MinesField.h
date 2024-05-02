#ifndef MINESWEEPEREX_MINESFIELD_H
#define MINESWEEPEREX_MINESFIELD_H
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include "Pane.h"
#include <random>
#include <vector>
#include <unordered_map>//hash表
using namespace std;
enum gameStates{on,end,win};
class MinesField{
public:
    int paneLine;//雷区边长
    int paneNum;//雷区边长
    int Num;//记录翻开雷数目
    IMAGE img[26];
    gameStates state;
    vector<pair<int,int>>nums;
    Pane **panes;

    MinesField():paneLine(0),paneNum(0),Num(0),panes(nullptr),state(on){
        //加载图库
        char filename[50];
        for (int k = 0; k < 26; k++)
        {
            sprintf(filename, "D:\\C\\MineSweeperEX\\Resources\\%d.gif", k + 1);
            loadimage(&this->img[k],filename);
        }
    };


    void Print(){
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                //if(!this->panes[i][j].IsMine)
                this->panes[i][j].Close(this->img);

                //查看地雷测试
                //else this->panes[i][j].Open(this->img);
            }
        }

    }


    void Mines(int Height){//雷区初始化
        this->panes=new Pane*[this->paneLine];//指针数组地址分配给 二维指针panes;
        for (int i = 0; i < this->paneLine; ++i) {
            panes[i]= new Pane[this->paneLine];//分配Pane组的内存，并将地址给 pane[i]
        }

        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                this->panes[i][j].i=i;
                this->panes[i][j].j=j;
                this->panes[i][j].x = j * 25;
                this->panes[i][j].y = Height - (this->paneLine - i) * 25;
            }
        }
    }


    void Random(){//随机数生成；
        unordered_map<int,int>map;
        random_device rd;//随机种子
        default_random_engine engine(rd());//随机数引擎
        uniform_int_distribution<int> distribution(0,this->paneLine-1);//生成随机数范围；

        nums=vector<pair<int,int>>(this->paneNum);//元组矢量,长度为雷数

        for (int i = 0; i < this->paneNum; ) {

            this->nums[i].first= distribution(engine);//first
            this->nums[i].second= distribution(engine);//second
            if(map.find(this->nums[i].first)==map.end()||map[this->nums[i].first]!=this->nums[i].second){
                map[this->nums[i].first]=this->nums[i].second;
                ++i;//防止重复
            }
            else continue;

        }
        //测试，打印地址
        for (int i = 0; i < this->paneLine; ++i) {
            cout<<nums[i].first+1<<" "<<nums[i].second+1<<endl;

        }


    }


    void MineSet(){//随机埋雷
        this->Random();//分配随机数
        for (int i = 0; i < this->paneNum; ++i) {
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
                this->panes[i][j].i=i;
                this->panes[i][j].j=j;

                for (int k = 0; k < 8; ++k) {
                    if(Blocks[k]&&Blocks[k]->IsMine)//Blocks[k]存在
                        this->panes[i][j].AroundMineNum++;//周围雷数加1
                }
                delete Blocks;
            }
        }
    }


    void ExtendingDP(int x,int y){//递归函数
        if(this->panes[x][y].state!=Closed)return;
        if(this->panes[x][y].AroundMineNum>0){
            this->panes[x][y].Open(this->img);
            this->JudgeWin();
            return;
        }
        if(this->panes[x][y].IsMine)return;
        this->panes[x][y].Open(this->img);
        this->JudgeWin();
        Pane**Blocks= GetAroundPanes(x,y);
        for (int i = 0; i < 8; ++i) {
            if(Blocks[i]&&!(Blocks[i]->IsMine))//Blocks[k]存在
                ExtendingDP(Blocks[i]->i,Blocks[i]->j);
            else break;
        }
        delete Blocks;
    }


    void ShowAllMine(){
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                if(this->panes[i][j].IsMine&&!this->panes[i][j].ClickMine)
                    this->panes[i][j].Open(this->img);
            }
        }
    }


    void JudgeWin(){
        this->Num++;
        //cout<<this->Num<<endl;//测试数目
        if(this->Num==this->paneLine*this->paneLine-this->paneNum){
            this->state = gameStates:: win;
        }
    }

    bool JudgeWin2(){
        int n=0;
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
              if(this->panes[i][j].IsMine&&this->panes[i][j].state==Marked)n++;
            }
        }
        return (n == this->paneNum);
    }


    void JudgeEnd(int i,int j){
        this->state = gameStates:: end;
        panes[i][j].ClickMine= true;
        this->panes[i][j].Open(this->img);
        ShowAllMine();
    }


    void ReFlied(){
        this->Num=0;
        this->state = gameStates:: on;
    }


};

#endif //MINESWEEPEREX_MINESFIELD_H
