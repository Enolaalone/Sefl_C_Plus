#ifndef PANESFIELD_H
#define PANESFIELD_H
#include <QRandomGenerator>//随机数
#include <QMap>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class PanesField: public QWidget//继承自Weight才可以重构
{

public:
    enum Game{Begin,Process,Win,End};
    enum Block{
        ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,BOOM,
        D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,FLAG,RBOOM,U0,U1
    };
    QMap<Block,QPixmap> map;//HASH
    Game state;
    int PaneNum;
    int ROW_COUNT;
    int COL_COUNT;
    int BLOCK_WIDTH;

    int Num;//排雷数目

    Block **data;
    Block **view;
    //数据初始化
    PanesField(QWidget *parent = nullptr,int n=0,int cl=0,int rl=0):QWidget(parent),state(Begin),PaneNum(n),ROW_COUNT(rl),COL_COUNT(cl),BLOCK_WIDTH(25),Num(0),data(nullptr),view(nullptr){
        //数据 数组；
        this->data = new Block*[ROW_COUNT];
        for (int i = 0;   i< this->COL_COUNT; ++i ) {
            data[i] = new Block[this->COL_COUNT];
        }

        //绘图数组；
        this->view = new Block*[ROW_COUNT];
        for (int i = 0;   i< this->COL_COUNT; ++i ) {
            view[i] = new Block[this->COL_COUNT];
        }
        //导入图片
        this->MapSet();


        this->setFixedSize(this->BLOCK_WIDTH*this->COL_COUNT,this->BLOCK_WIDTH*this->ROW_COUNT);//设置固定窗口
    };
    void MapSet(){
        //图库构建
        this->map.insert(ONE,QPixmap(":/Resources/1.gif"));
        this->map.insert(TWO,QPixmap(":/Resources/2.gif"));
        this->map.insert(THREE,QPixmap(":/Resources/3.gif"));
        this->map.insert(FOUR,QPixmap(":/Resources/4.gif"));
        this->map.insert(FIVE,QPixmap(":/Resources/5.gif"));
        this->map.insert(SIX,QPixmap(":/Resources/6.gif"));
        this->map.insert(SEVEN,QPixmap(":/Resources/7.gif"));
        this->map.insert(EIGHT,QPixmap(":/Resources/8.gif"));

        this->map.insert(BOOM,QPixmap(":/Resources/boom.gif"));
        this->map.insert(RBOOM,QPixmap(":/Resources/red_boom.gif"));
        this->map.insert(U1,QPixmap(":/Resources/under0.gif"));
        this->map.insert(U0,QPixmap(":/Resources/under1.gif"));
        //COOL,DEAD,
        //D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,FLAG,RBOOM,SMILE,U0,U1

        this->map.insert(FLAG,QPixmap(":/Resources/flag.gif"));


    }
    void Re(){//重新设置状态
        for (int i = 0; i < ROW_COUNT; ++i) {
            for (int j = 0; j < COL_COUNT; ++j) {
                this->data[i][j]=U0;this->view[i][j]=U1;
            }
        }

        this->Num=0;//计数初始化
        this->state = Begin;//游戏状态初始化
    }


    void PaneRandom(){//随机设置地雷
        for(int i=0;i<this->PaneNum;){
            int r=QRandomGenerator::global()->generate()%(this->COL_COUNT*this->ROW_COUNT);
            int x=r/ROW_COUNT,y=r%ROW_COUNT;
            if(this->data[x][y] != BOOM ){
                this->data[x][y] = BOOM;
                ++i;

                //测试
               // this->view[x][y] = FLAG;
            }

        }
    }

    void GetArroundPaneNum(){
        for (int i = 0; i < this->ROW_COUNT; ++i) {
            for (int j = 0; j < COL_COUNT; ++j) {
                if(this->data[i][j]==BOOM)continue;//如果是炸蛋

                int sum = 0;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if(i+dx>=0&&i+dx<this->ROW_COUNT && j+dy>=0&&j+dy<this->COL_COUNT&&
                            this->data[i+dx][j+dy]==BOOM){
                            if(i+dx!=i||j+dy!=j)
                                sum++;

                        }
                    }
                }
                switch(sum){
                case 0:this->data[i][j] = U0;break;
                case 1:this->data[i][j] = ONE;break;
                case 2:this->data[i][j] = TWO;break;
                case 3:this->data[i][j] = THREE;break;
                case 4:this->data[i][j] = FOUR;break;
                case 5:this->data[i][j] = FIVE;break;
                case 6:this->data[i][j] = SIX;break;
                case 7:this->data[i][j] = SEVEN;break;
                case 8:this->data[i][j] = EIGHT;break;

                }
            }
        }

    }

    void Extend(int x,int y){
        if(this->view[x][y]!=U1)return;

        if(this->data[x][y]==ONE||this->data[x][y]==TWO||this->data[x][y]==THREE||this->data[x][y]==FOUR
            ||this->data[x][y]==FIVE||this->data[x][y]==SIX||this->data[x][y]==SEVEN||this->data[x][y]==EIGHT){
            this->view[x][y]=this->data[x][y];
            repaint();//重新绘制图形
            this->JudgeWin();
            return;
        }

        if(this->data[x][y]==BOOM)return;

        this->view[x][y]=this->data[x][y];
        repaint();//重新绘制图形
        this->JudgeWin();

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if(x+dx>=0&&x+dx<this->ROW_COUNT && y+dy>=0&&y+dy<this->COL_COUNT&&this->data[x+dx][y+dy]!=BOOM)
                    this->Extend(x+dx,y+dy);
            }
        }
    }

    void OverShowAllMines(){
        this->state=End;
        for (int i = 0; i < this->ROW_COUNT; ++i) {
            for (int j = 0; j < this->COL_COUNT; ++j) {
                if(this->data[i][j]==BOOM&&this->view[i][j]!=RBOOM){
                    this->view[i][j]=BOOM;
                }
            }
        }

        repaint();
    }
    void JudgeWin(){//检测是否胜利
        this->Num++;
        if(this->Num==this->COL_COUNT*this->ROW_COUNT-this->PaneNum){
            this->state=Win;
        }
    }

    void JudgeWin2(){//检测是否胜利2
        int n=0;
        for (int i = 0; i < this->ROW_COUNT; ++i) {
            for (int j = 0; j < this->COL_COUNT; ++j) {
                if(this->data[i][j]==BOOM&&this->view[i][j]==FLAG){
                    n++;
                }
            }
        }

        if(n==this->PaneNum)this->state=Win;
    }

    void paintEvent(QPaintEvent *event) override{//重载 绘图
        Q_UNUSED(event);

        QPainter qpainter = QPainter(this);
        //绘制雷区
        for (int i = 0; i < this->ROW_COUNT; ++i) {
            for (int j = 0; j < this->COL_COUNT; ++j) {
                qpainter.drawPixmap(this->BLOCK_WIDTH*i,this->BLOCK_WIDTH*j,this->map[this->view[i][j]]);
                // qpainter.drawPixmap(this->panesField.BLOCK_WIDTH*i,this->panesField.BLOCK_WIDTH*j+50,this->panesField.map[this->panesField.data[i][j]]);
            }
        }

    }





};

#endif // PANESFIELD_H
