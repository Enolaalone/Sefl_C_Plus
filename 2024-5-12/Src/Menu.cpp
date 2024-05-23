#include "Menu.h"

Menu::Menu():r1(0,0,40,19),r2(40,0,80,19),r3(80,0,120,19), R1(0,0,0,0),
       R2(0,0,0,0),R3(0,0,0,0),last(0),event(0){}

void Menu::Set(){
    R1={r1[0],r1[1],r1[2],r1[3]};
    R2={r2[0],r2[1],r2[2],r2[3]};
    R3={r3[0],r3[1],r3[2],r3[3]};
    gettextstyle(&f);					//��ȡ������ʽ
    _tcscpy(f.lfFaceName,_T("����"));	//��������Ϊ����
    f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����
    settextstyle(&f);                     // ����������ʽ
    settextcolor(BLACK);
    drawtext("��",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
    drawtext("�е�",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("����",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    setlinecolor(BLACK);
    rectangle(r1[0],r1[1],r1[2],r1[3]);
    rectangle(r2[0],r2[1],r2[2],r2[3]);
    rectangle(r3[0],r3[1],r3[2],r3[3]);
    this->event=0;
}

int Menu::button_judge(int x,int y)
{
    if(x>r1[0] && x<r1[2] && y>r1[1] && y<r1[3])return 1;
    if(x>r2[0] && x<r2[2] && y>r2[1] && y<r2[3])return 2;
    if(x>r3[0] && x<r3[2] && y>r3[1] && y<r3[3])return 3;
    return 0;
}


void Menu::ButtonChange(int x,int y){
    setrop2(R2_XORPEN);//ȡ��ɫ
    if(event!= button_judge(x,y))
    {
        last=event;
        event = button_judge(x,y);

        switch (last) {
            case 1:
                fillrectangle(r1[0],r1[1],r1[2],r1[3]);//�п������Σ�X1,Y1,X2,Y2��
                break;
            case 2:
                fillrectangle(r2[0],r2[1],r2[2],r2[3]);
                break;
            case 3:
                fillrectangle(r3[0],r3[1],r3[2],r3[3]);
                break;
            default:
                break;
        }
        setfillcolor(WHITE);//�����ɫΪ��ɫ
        switch (event) {
            case 1:
                fillrectangle(r1[0],r1[1],r1[2],r1[3]);//�п������Σ�X1,Y1,X2,Y2��
                break;
            case 2:
                fillrectangle(r2[0],r2[1],r2[2],r2[3]);
                break;
            case 3:
                fillrectangle(r3[0],r3[1],r3[2],r3[3]);
                break;
            default:
                break;
        }

    }
    setrop2(R2_COPYPEN); // ����ͼģʽ���û������ĸ���ģʽ
}