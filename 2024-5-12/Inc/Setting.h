#ifndef MINESWEEPEREX_SETTING_H
#define MINESWEEPEREX_SETTING_H
#include "graphics.h"        // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include "Emoji.h"
#include "Timer.h"
#include "Flags.h"
using namespace std;
class Setting{
public:
    Emoji emoji;//���鰴ť
    Timer timer;//��ʱ��
    Flags flags;//������
    IMAGE img[15];//ͼ��
    int x,y,w,h;//λ�ã�������
    //��ʼ��
    Setting();

    //�û�������Ʊ߿�
    void setBack(int Width);

    //���ñ���
    void emojiSet();

    //����ʱ��
    void SetTimer();

    //��������
    void SetFlags(int n);

};


#endif //MINESWEEPEREX_SETTING_H
