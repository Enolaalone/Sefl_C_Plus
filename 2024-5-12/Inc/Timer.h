#ifndef MINESWEEPEREX_TIME_H
#define MINESWEEPEREX_TIME_H
#include "Board.h"
#include "graphics.h"
#include <conio.h>
#include <chrono>

using namespace std;
class Timer:public Board{
private:
    //int x,y;//λ��
    //int times;//��һ��ʱ��
    chrono::system_clock::time_point l_now;//��¼ϵͳʱ�� ��
    bool state;//��ʱ��״̬
    //IMAGE *img;//ͼƬ��ַ
public:
    //��ʼ��
    Timer();

    //����
    void Set();

    //��ʱ��ʾ,�ع��麯��
    void Show()override;

    //���ü�ʱ��״̬
    void SetState(bool s);

};

#endif //MINESWEEPEREX_TIME_H
