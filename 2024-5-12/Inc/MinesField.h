#ifndef MINESWEEPEREX_MINESFIELD_H
#define MINESWEEPEREX_MINESFIELD_H
#include "graphics.h"// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include "Pane.h"
#include <random>
#include <vector>
#include <unordered_map>//hash��
using namespace std;
enum gameStates{on,end,win};
class MinesField{
private:
    int paneLine;//�����߳�
    int paneNum;//�׸���
    int Num;//��¼��������Ŀ
    IMAGE img[26];//ͼ��
    gameStates state;//״̬
    vector<pair<int,int>>nums;//�������
    Pane **panes;//����
public:
    //��ʼ��
    MinesField();

    //��ʾ����
    void Print();

    //������ʼ��
    void Mines(int Height);

    //��������ɣ�
    void Random();

    //�������
    void MineSet();

    //��ȡ��Χ����
    Pane** GetAroundPanes(int x,int y);

    //������Χ����
    void RecordAroundMines();

    //�ݹ麯��
    void ExtendingDP(pair<int,int>Np);

    //չʾ���е���
    void ShowAllMine();

    //�����Ϸʤ��
    void JudgeWin();

    //�����Ϸʤ��2
    bool JudgeWin2();

    //�����Ϸʧ��
    void JudgeEnd(int i,int j);

    //��������
    void ReFlied();

    //���ñ߸���
    void SetPaneline(int n);

    //��ȡ�߸���
    int GetPaneline();

    //��������
    void SetPanenum(int n);

    //��ȡ����
    int GetPanenum();

    //������Ϸ״̬
    void SetGameState(gameStates s);

    //��ȡ��Ϸ״̬
    gameStates GetGameState();

    //��ȡ������ַ
    Pane** GetPanes();

    //��ȡͼƬ��ַ
    IMAGE* GetImagine();
};

#endif //MINESWEEPEREX_MINESFIELD_H
