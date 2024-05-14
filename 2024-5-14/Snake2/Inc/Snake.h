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
    bool state;//��Ϸ״̬
    int size;//����
    int speed;//�ٶ�
    int TSpeed;//ʱ���ٶ��ٶ�
    Dir direct;//����
    vector<Sprite> sprites;//����
public:
    //��ʼ��
    Snake();

    //�ع����ƺ���,�������
    void draw()const override;

    //��������
    void RenewBody();

    //�����ƶ�����
    void Move(int Width ,int Height);

    //����Ƿ�ҧ���Լ�
    bool Judge();

    //�������峤��
    void EnBody();

    //������������
    void ReSet();

    //��ȡ�ߵ�ǰ״̬
    bool GetState();

    //���÷���
    void SetDir(Dir d);

    //��ȡ����
    Dir GetDir();

    //��ȡ����ĳ����
    Sprite GetBody(int i);

    //�����ƶ��ٶ�
    void SetTspeed(int T);
};

#endif //SNAKE_SNAKE_H
