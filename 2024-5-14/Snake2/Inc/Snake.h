#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include "Sprite.h"
#include "Food.h"
#include<cstdlib>
#include <thread>
#include <vector>

using namespace std;
enum Dir{Up,Down,Left,Right};
class Snake:public Sprite{
private:
    bool state;//游戏状态
    int size;//长度
    int speed;//速度
    int TSpeed;//时间速度速度
    Dir direct;//方向
    vector<Sprite> sprites;//蛇身
public:
    //初始化
    Snake();

    //重构绘制函数,缓冲绘制
    void draw()const override;

    //更新身体
    void RenewBody();

    //身体移动方向
    void Move(int Width ,int Height);

    //检测是否咬到自己
    bool Judge();

    //增加身体长度
    void EnBody();

    //重启参数设置
    void ReSet();

    //获取蛇当前状态
    bool GetState();

    //设置方向
    void SetDir(Dir d);

    //获取方向
    Dir GetDir();

    //获取身体某部分
    Sprite GetBody(int i);

    //设置移动速度
    void SetTspeed(int T);
};

#endif //SNAKE_SNAKE_H
