#ifndef SNAKE_FORM_H
#define SNAKE_FORM_H
#include "Snake.h"
#include "Food.h"
#include "Memu.h"
#include <thread>//�ߵ����߳̿���

using namespace std;
class Form{
private:
    int Width,Height;//���ڴ�С
    bool running;//��Ϸ״̬
    Snake snake;//��
    Food food;//ʳ��
    Menu menu;//�˵�
public:
    //��ʼ��
    Form();

    //���ö���������ü�������
    void Set();

    //��Ϸ����
    void Run();

    //��ȡ���̣��ı䷽��
    void KeyBoard();

    //�������ʳ��
    void FoodSet();

    //�Ե�ʳ��
    void Eatting();

    //���������
    void Mops();

    //��Ϸ��������
    void GaneEnd();
};

#endif //SNAKE_FORM_H
