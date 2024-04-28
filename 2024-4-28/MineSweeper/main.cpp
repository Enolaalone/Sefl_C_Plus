#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include <QPainter>
#include <QRandomGenerator>//随机数
#include <QMouseEvent>//鼠标点击事件

const int ROW_COUNT=9;
const int COL_COUNT=9;
int BLOCK_WIDTH=26;
int BLOCK_HEIGHT=26;
int WINDOW_WIDTH=COL_COUNT*BLOCK_WIDTH;
int WINDOW_HEIGHT=ROW_COUNT*BLOCK_HEIGHT;

int PaneNum=10;
enum Block{
    ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,BOOM,COOL,DEAD,
    D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,FLAG,RBOOM,SMILE,U0,U1
};

QMap<Block,QPixmap> map;//HASH

class Window:public QWidget{
    public:
        Block data[ROW_COUNT][COL_COUNT];
        Block view[ROW_COUNT][COL_COUNT];
         Window() {
             setWindowTitle("扫雷");
             setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);//窗口size

             for (int i = 0; i < ROW_COUNT; ++i) {
                 for (int j = 0; j < COL_COUNT; ++j) {
                     data[i][j]=U0;view[i][j]=U1;
                 }
             }

             for(int i=0;i<PaneNum;){
                 int r=QRandomGenerator::global()->generate()%(COL_COUNT*ROW_COUNT);
                 int x=r/ROW_COUNT,y=r%ROW_COUNT;
                 if(data[x][y] != BOOM ){
                    data[x][y] = BOOM;
                     ++i;
                 }

             }

             for (int i = 0; i < ROW_COUNT; ++i) {
                 for (int j = 0; j < COL_COUNT; ++j) {
                     if(data[i][j]==BOOM)continue;//如果是炸蛋

                     int sum = 0;
                     for (int dx = -1; dx <= 1; ++dx) {
                         for (int dy = -1; dy <= 1; ++dy) {
                             if(i+dx>=0&&i+dx<ROW_COUNT && j+dy>=0&&j+dy<COL_COUNT&&
                                 data[i+dx][j+dy]==BOOM){
                                 if(i+dx!=i||j+dy!=j)
                                 sum++;

                             }
                         }
                     }
                     switch(sum){
                        case 0:data[i][j] = U0;break;
                        case 1:data[i][j] = ONE;break;
                        case 2:data[i][j] = TWO;break;
                        case 3:data[i][j] = THREE;break;
                        case 4:data[i][j] = FOUR;break;
                        case 5:data[i][j] = FIVE;break;
                        case 6:data[i][j] = SIX;break;
                        case 7:data[i][j] = SEVEN;break;
                        case 8:data[i][j] = EIGHT;break;

                    }
                 }
             }
         };

         void paintEvent(QPaintEvent *event) override{//重载
             Q_UNUSED(event);

             QPainter qpainter = QPainter(this);
             for (int i = 0; i < ROW_COUNT; ++i) {
                 for (int j = 0; j < COL_COUNT; ++j) {
                     qpainter.drawPixmap(BLOCK_WIDTH*i-1,BLOCK_HEIGHT*j-1,map[view[i][j]]);
                 }
             }

         }

         void mousePressEvent(QMouseEvent *event)override{//鼠标点击事件
            int x=event->x()/BLOCK_WIDTH,y=event->y()/BLOCK_HEIGHT;
             if(event->button()==Qt::LeftButton){//左键
                 if(view[x][y]==FLAG)view[x][y]=U1;
                 else if(view[x][y]==U1){
                     if(data[x][y]==BOOM){
                         view[x][y]=data[x][y];//--------------EXtend
                     }
                     else{//递归
                         Extend(x,y);
                     }

                 }
             }else if(event->button()==Qt::RightButton){//右键
                 view[x][y]=FLAG;

             }
            repaint();//重新绘制图形
         }

         void Extend(int x,int y){
             if(view[x][y]!=U1)return;
             if(data[x][y]==ONE||data[x][y]==TWO||data[x][y]==THREE||data[x][y]==FOUR
                 ||data[x][y]==FIVE||data[x][y]==SIX||data[x][y]==SEVEN||data[x][y]==EIGHT){
                 view[x][y]=data[x][y];
                 repaint();//重新绘制图形
                 return;
             }
             if(data[x][y]==BOOM)return;
             view[x][y]=data[x][y];
             repaint();//重新绘制图形
             for (int dx = -1; dx <= 1; ++dx) {
                 for (int dy = -1; dy <= 1; ++dy) {
                     if(x+dx>=0&&x+dx<ROW_COUNT && y+dy>=0&&y+dy<COL_COUNT&&data[x+dx][y+dy]!=BOOM)
                         Extend(x+dx,y+dy);
                 }
             }
         }

} ;
void MapSet(){
    //图库构建
    map.insert(ONE,QPixmap(":/Resources/1.gif"));
    map.insert(TWO,QPixmap(":/Resources/2.gif"));
    map.insert(THREE,QPixmap(":/Resources/3.gif"));
    map.insert(FOUR,QPixmap(":/Resources/4.gif"));
    map.insert(FIVE,QPixmap(":/Resources/5.gif"));
    map.insert(SIX,QPixmap(":/Resources/6.gif"));
    map.insert(SEVEN,QPixmap(":/Resources/7.gif"));
    map.insert(EIGHT,QPixmap(":/Resources/8.gif"));
    map.insert(BOOM,QPixmap(":/Resources/boom.gif"));
    map.insert(U1,QPixmap(":/Resources/under0.gif"));
    map.insert(U0,QPixmap(":/Resources/under1.gif"));
    //COOL,DEAD,
    //D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,FLAG,RBOOM,SMILE,U0,U1

    map.insert(FLAG,QPixmap(":/Resources/flag.gif"));


}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MapSet();


    Window window;
    window.show();

    return a.exec();
}
