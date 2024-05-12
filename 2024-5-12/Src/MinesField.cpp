#include "MinesField.h"
#include <iostream>
using namespace std;

MinesField::MinesField():paneLine(0),paneNum(0),Num(0),panes(nullptr),state(on){
    //����ͼ��
    char filename[50];
    for (int k = 0; k < 26; k++)
    {
        sprintf(filename, "..\\Resources\\%d.gif", k + 1);
        loadimage(&this->img[k],filename);
    }
};


void MinesField::Print(){
    for (int i = 0; i < this->paneLine; ++i) {
        for (int j = 0; j < this->paneLine; ++j) {
            //if(!this->panes[i][j].IsMine)
            this->panes[i][j].Close(this->img);

            //�鿴���ײ���
            //else this->panes[i][j].Open(this->img);
        }
    }

}


void MinesField::Mines(int Height){//������ʼ��
    this->panes=new Pane*[this->paneLine];//ָ�������ַ����� ��άָ��panes;
    for (int i = 0; i < this->paneLine; ++i) {
        panes[i]= new Pane[this->paneLine];//����Pane����ڴ棬������ַ�� pane[i]
    }

    for (int i = 0; i < this->paneLine; ++i) {
        for (int j = 0; j < this->paneLine; ++j) {
            this->panes[i][j].SetNumPos(i,j);
            this->panes[i][j].SetPos(j * 25,Height - (this->paneLine - i) * 25);
        }
    }
}


void MinesField::Random(){//��������ɣ�
    unordered_map<int,int>map;
    random_device rd;//�������
    default_random_engine engine(rd());//���������
    uniform_int_distribution<int> distribution(0,this->paneLine-1);//�����������Χ��

    nums=vector<pair<int,int>>(this->paneNum);//Ԫ��ʸ��,����Ϊ����

    for (int i = 0; i < this->paneNum; ) {

        this->nums[i].first= distribution(engine);//first
        this->nums[i].second= distribution(engine);//second
        if(map.find(this->nums[i].first)==map.end()||map[this->nums[i].first]!=this->nums[i].second){
            map[this->nums[i].first]=this->nums[i].second;
            ++i;//��ֹ�ظ�
        }
        else continue;

    }
    //���ԣ���ӡ��ַ
    for (int i = 0; i < this->paneLine; ++i) {
        cout<<nums[i].first+1<<" "<<nums[i].second+1<<endl;

    }


}


void MinesField::MineSet(){//�������
    this->Random();//���������
    for (int i = 0; i < this->paneNum; ++i) {
        panes[this->nums[i].first][this->nums[i].second].SetIsMine(true);//������

    }
}


Pane** MinesField::GetAroundPanes(int x,int y){//��ȡ��Χ����
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


void MinesField::RecordAroundMines(){//������Χ����
    for (int i = 0; i < this->paneLine; ++i) {
        for (int j = 0; j < this->paneLine; ++j) {
            Pane**Blocks= GetAroundPanes(i,j);
            // λ��
            this->panes[i][j].SetNumPos(i,j);

            for (int k = 0; k < 8; ++k) {
                if(Blocks[k]&&Blocks[k]->GetIsMine())//Blocks[k]����
                    this->panes[i][j].AddAMN();//��Χ������1
            }
            delete Blocks;
        }
    }
}


void MinesField::ExtendingDP(pair<int,int> Np){//�ݹ麯��
    if(this->panes[Np.first][Np.second].GetState()!=Closed)return;
    if(this->panes[Np.first][Np.second].GetAMN()>0){
        this->panes[Np.first][Np.second].Open(this->img);
        this->JudgeWin();
        return;
    }
    if(this->panes[Np.first][Np.second].GetIsMine())return;
    this->panes[Np.first][Np.second].Open(this->img);
    this->JudgeWin();
    Pane**Blocks= GetAroundPanes(Np.first,Np.second);
    for (int i = 0; i < 8; ++i) {
        if(Blocks[i]&&!(Blocks[i]->GetIsMine()))//Blocks[k]����
            ExtendingDP(Blocks[i]->GetNumPos());
        else break;
    }
    delete Blocks;
}


void MinesField::ShowAllMine(){
    for (int i = 0; i < this->paneLine; ++i) {
        for (int j = 0; j < this->paneLine; ++j) {
            if(this->panes[i][j].GetIsMine()&&!this->panes[i][j].GetClick())
                this->panes[i][j].Open(this->img);
        }
    }
}


void MinesField::JudgeWin(){
    this->Num++;
    //cout<<this->Num<<endl;//������Ŀ
    if(this->Num==this->paneLine*this->paneLine-this->paneNum){
        this->state = gameStates:: win;
    }
}

bool MinesField::JudgeWin2(){
    int n=0;
    for (int i = 0; i < this->paneLine; ++i) {
        for (int j = 0; j < this->paneLine; ++j) {
            if(this->panes[i][j].GetIsMine()&&this->panes[i][j].GetState()==Marked)n++;
        }
    }
    return (n == this->paneNum);
}


void MinesField::JudgeEnd(int i,int j){
    this->state = gameStates:: end;
    panes[i][j].SetClick(true);
    this->panes[i][j].Open(this->img);
    ShowAllMine();
}


void MinesField::ReFlied(){
    this->Num=0;
    this->state = gameStates::on;
}

void MinesField::SetPaneline(int n){
    this->paneLine = n;
}
int MinesField::GetPaneline(){
    return this->paneLine;
}

void MinesField::SetPanenum(int n){
    this->paneNum = n;
}

int  MinesField::GetPanenum(){
    return this->paneNum;
}
void MinesField::SetGameState(gameStates s){
    this->state = s;
}
gameStates  MinesField::GetGameState(){
    return this->state;
}

Pane** MinesField::GetPanes(){
    return this->panes;
}

IMAGE* MinesField::GetImagine(){
    return this->img;
}