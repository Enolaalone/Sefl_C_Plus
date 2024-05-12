#ifndef MINESWEEPEREX_MINESFIELD_H
#define MINESWEEPEREX_MINESFIELD_H
#include "graphics.h"// 引用图形库头文件
#include <conio.h>
#include "Pane.h"
#include <random>
#include <vector>
#include <unordered_map>//hash表
using namespace std;
enum gameStates{on,end,win};
class MinesField{
private:
    int paneLine;//雷区边长
    int paneNum;//雷个数
    int Num;//记录翻开雷数目
    IMAGE img[26];//图库
    gameStates state;//状态
    vector<pair<int,int>>nums;//随机埋雷
    Pane **panes;//雷区
public:
    //初始化
    MinesField();

    //显示雷区
    void Print();

    //雷区初始化
    void Mines(int Height);

    //随机数生成；
    void Random();

    //随机埋雷
    void MineSet();

    //获取周围地雷
    Pane** GetAroundPanes(int x,int y);

    //计算周围雷数
    void RecordAroundMines();

    //递归函数
    void ExtendingDP(pair<int,int>Np);

    //展示所有地雷
    void ShowAllMine();

    //检测游戏胜利
    void JudgeWin();

    //检测游戏胜利2
    bool JudgeWin2();

    //检测游戏失败
    void JudgeEnd(int i,int j);

    //雷区重启
    void ReFlied();

    //设置边个数
    void SetPaneline(int n);

    //获取边个数
    int GetPaneline();

    //设置雷数
    void SetPanenum(int n);

    //获取雷数
    int GetPanenum();

    //设置游戏状态
    void SetGameState(gameStates s);

    //获取游戏状态
    gameStates GetGameState();

    //获取雷区地址
    Pane** GetPanes();

    //获取图片地址
    IMAGE* GetImagine();
};

#endif //MINESWEEPEREX_MINESFIELD_H
