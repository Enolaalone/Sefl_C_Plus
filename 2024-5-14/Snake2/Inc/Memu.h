#ifndef SNAKE_MEMU_H
#define SNAKE_MEMU_H
#include <graphics.h>
#include <conio.h>

class Menu{
private:
    int event,last;//��굱ǰѡ�а�ť����һ��ѡ�а�ť
    int r1[4],r2[4],r3[4];//��ť����������
    RECT R1,R2,R3,R4;//�ı���
    LOGFONT f;//������ʽָ��
public:
    //��ʼ��λ�ã���С
    Menu();

    //�����ְ�ť����
    void Set();

    //���������ð�ť
    int button_judge(int x,int y);

    //��ʼ���水ťѡ��
    void ButtonChange(int x,int y);

    //������������
    void GameOVer();

    //�����簴ť
    void ButtonChange2(int x,int y);

    //����ѡ��λ��
    int GetPos(int n,int k);

};


#endif //SNAKE_MEMU_H
