#ifndef MINESWEEPEREX_FLAGS_H
#define MINESWEEPEREX_FLAGS_H

#include "graphics.h"        // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include "Board.h"
class Flags:public Board{
private:
    int UpNum;//��ʼ����
    bool state;//������״̬
public:
    //��ʼ��
    Flags():UpNum(0),state(true){}

//    //��ʾ����
//    void ShowNum()const;

    //��Ŀ��ʼ��
    void Set(int n);
    
    //������Ŀ�Ӽ�
    void AddOrDes(bool s);

    //��ȡ״̬
    bool GetState();

};

#endif //MINESWEEPEREX_FLAGS_H
