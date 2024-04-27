#ifndef MINESWEEPER_MINEFIELD_H
#define MINESWEEPER_MINEFIELD_H
#include "Pane.h"
#include <random>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>//hash��

using namespace std;
enum gameStates{on,end,win};
class MineField{
public:
    int paneLine;//�����߳�
    int paneNum;//�����߳�
    int Num;//��¼��������Ŀ
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
    void Print2(){//��ӡ����
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                panes[i][j].print2();
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void Mines(){//������ʼ��
         this->panes=new Pane*[this->paneLine];//ָ�������ַ����� ��άָ��panes;
        for (int i = 0; i < this->paneLine; ++i) {
            panes[i]= new Pane[this->paneLine];//����Pane����ڴ棬������ַ�� pane[i]
        }
    }

    void Random(){//��������ɣ�
        unordered_map<int,int>map;
        random_device rd;//�������
        default_random_engine engine(rd());//���������
        uniform_int_distribution<int> distribution(0,this->paneLine-1);//�����������Χ��

        nums=vector<pair<int,int>>(this->paneNum);//Ԫ��ʸ��,����Ϊ����

        for (int i = 0; i < this->paneLine; ) {

            this->nums[i].first= distribution(engine);//first
            this->nums[i].second= distribution(engine);//second
            if(map.find(this->nums[i].first)==map.end()||map[this->nums[i].first]!=this->nums[i].second)
                ++i;//��ֹ�ظ�
            map[this->nums[i].first]=this->nums[i].second;
            //cout<<nums[i].first<<" "<<nums[i].second<<endl;//��ӡ���
        }

    }
    void MineSet(){//�������
        this->Random();//���������
        for (int i = 0; i < this->paneLine; ++i) {
            panes[this->nums[i].first][this->nums[i].second].IsMine = true;//������
        }
    }

    Pane** GetAroundPanes(const int x,const int y){//��ȡ��Χ����
        int k[3]={-1,0,1},n=0;
        Pane**Blocks = new Pane*[8]{nullptr};
        //for (int i = 0; i < 8; ++i) Blocks[i]= nullptr;//��ֵȫΪnull

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if((x+k[i])> -1&&(x+k[i]< this->paneLine)
                && (y+k[j])> -1&&(y+k[j]< this->paneLine)){
                    if(x+k[i]!=x||y+k[j]!=y)//���ǵ�ǰ��
                    Blocks[n++] = &this->panes[x+k[i]][y+k[j]];//��¼�µ�ַ

                }
            }
        }
        return Blocks;
    }

    void RecordAroundMines(){//������Χ����
        for (int i = 0; i < this->paneLine; ++i) {
            for (int j = 0; j < this->paneLine; ++j) {
                Pane**Blocks= GetAroundPanes(i,j);
                // λ��
                this->panes[i][j].x=i;
                this->panes[i][j].y=j;

                for (int k = 0; k < 8; ++k) {
                    if(Blocks[k]&&Blocks[k]->IsMine)//Blocks[k]����
                        this->panes[i][j].AroundMineNum++;//��Χ������1
                }
                delete Blocks;
            }
        }
    }

    void ExtendingDP(int x,int y){//�ݹ麯��
        if(this->panes[x][y].status!=Closed)return;
        if(this->panes[x][y].AroundMineNum>0){
            this->panes[x][y].status=Opened;//��Χ���ף���������
            this->JudgeWin();
            return;
        }
        if(this->panes[x][y].IsMine)return;
        this->panes[x][y].status=Opened;
        this->JudgeWin();
        Pane**Blocks= GetAroundPanes(x,y);
        for (int i = 0; i < 8; ++i) {
            if(Blocks[i]&&!(Blocks[i]->IsMine))//Blocks[k]����
                ExtendingDP(Blocks[i]->x,Blocks[i]->y);
        }
        delete Blocks;
    }

    void Extend(int x,int y){//���׺���
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

    MineField():paneLine(0),paneNum(0),Num(0),panes(nullptr),state(on){};//��ʼ��
};


#endif //MINESWEEPER_MINEFIELD_H
