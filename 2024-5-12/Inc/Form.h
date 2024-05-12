#ifndef MINESWEEPEREX_FORM_H
#define MINESWEEPEREX_FORM_H
#include <iostream>
#include "graphics.h"        // ����ͼ�ο�ͷ�ļ�
#include "MinesField.h"
#include "Setting.h"
#include "Menu.h"

#define BLOCK 25
#define E 9
#define M 16
#define H 24
using namespace std;

class Form{
public:
    MinesField field;//����
    Setting setting;//��������
    Menu menu;//�˵�����
    int Width;//��
    int Height;//��
    bool Running;//����״̬
    //��ʼ��
    Form();

    //��ʼ��
    void Setting(int line,int num);

    //������Ϸ
    void Run(int line,int num);

    //���������
    void MouseHandle();

    //�����Ϸ״̬
    void JudgeState(int mx,int my);

    //�������¼�
    bool Mpos_L(int x,int y,bool press);

    //�Ҽ�����¼�
    void Mpos_R(int x,int y);

    //���¿�ʼ��Ϸ
    void Resetting(int x,int y);
};

#endif //MINESWEEPEREX_FORM_H
