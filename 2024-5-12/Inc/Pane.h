#ifndef MINESWEEPEREX_PANE_H
#define MINESWEEPEREX_PANE_H

#define Zero 25
#define RedMine 22
#define WhiteMine 8
#define Cover 24
#define Flag1 21
#include "graphics.h"        // 引用图形库头文件
#include <conio.h>
#include <vector>
using namespace std;
enum PaneStates{
    Closed,
    Opened,
    Marked
};
class Pane{
private:
    int x,y;//界面地址
    int i,j;//数组坐标
    int AroundMineNum;//周围雷数
    bool IsMine;//是否是地雷
    bool ClickMine;//点击的地雷
    PaneStates state;//地雷状态
public:
    //初始化
    Pane();

    //翻开
    void Open(IMAGE *img);

    //关闭
    void Close(IMAGE *img);

    //标记状态
    void Mark(IMAGE *img);

    //设置 （x,y）
    void SetPos(int px,int py);

    //设置（i，j）
    void SetNumPos(int pi,int pj);

    //返回（i，j）
    pair<int,int> GetNumPos();

    //设置雷的状态
    void SetIsMine(bool s);

    //返回雷的状态
    bool GetIsMine();

    //增加周围雷数
    void AddAMN();

    //返回周围雷数
    int GetAMN();

    //返回状态
    PaneStates GetState();

    //设置点击状态
    void SetClick(bool s);

    //返回点击状态
    bool GetClick();

};


#endif MINESWEEPEREX_PANE_H
