#ifndef MINESWEEPEREX_MENU_H
#define MINESWEEPEREX_MENU_H
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>


class Menu{
public:
    int event,last;//��굱ǰ���õĲ˵�������һ�����õĲ˵�
    int r1[4],r2[4],r3[4];//ѡ����״
    RECT R1,R2,R3;//ѡ��
    LOGFONT f;//������ʽָ��

    //��ʼ��
    Menu();

    //�˵�����
    void Set();

    //�������
    int button_judge(int x,int y);

    //��ť�ı���ɫ
    void ButtonChange(int x,int y);

};
#endif //MINESWEEPEREX_MENU_H
