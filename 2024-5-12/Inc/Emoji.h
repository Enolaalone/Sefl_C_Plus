#ifndef MINESWEEPEREX_EMOJI_H
#define MINESWEEPEREX_EMOJI_H

#include "graphics.h"        // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <vector>
using namespace std;
enum States{Happy,Cool,Die};
class Emoji{
private:
    int x,y;//λ��
    States state;//״̬
    IMAGE *img;//ͼ��
public:
    //��ʼ��
    Emoji();

    //���Ʊ���
    void Judge() const;

    //��ť����
    void Press() const;

    //��ťδ����
    void Unpress(States s);

    //���õ�ǰͼƬ
    void SetImagine(IMAGE* i);

    //��������
    void SetPos(int px,int py);

    //��ȡ����
    pair<int,int> GetPos();

};

#endif //MINESWEEPEREX_EMOJI_H
