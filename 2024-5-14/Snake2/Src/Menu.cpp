#include "Memu.h"

Menu::Menu():r1(320-100,100-50,320+100,200-50),r2(220,200-25,420,300-25),r3(220,300+2,420,400+2),
       R1(0,0,0,0),R2(0,0,0,0),R3(0,0,0,0),R4(0,0,0,0),last(0),event(0){}


void Menu::Set(){
    R1={r1[0],r1[1],r1[2],r1[3]};
    R2={r2[0],r2[1],r2[2],r2[3]};
    R3={r3[0],r3[1],r3[2],r3[3]};
    gettextstyle(&f);					//获取字体样式
    _tcscpy(f.lfFaceName,_T("宋体"));	//设置字体为宋体
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿
    f.lfHeight = 48;                        //设置高度
    settextstyle(&f);                     // 设置字体样式
    settextcolor(WHITE);
    drawtext("鼻涕虫",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
    drawtext("蠕虫",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext("巨蟒",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    setlinecolor(WHITE);
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
    setrop2(R2_XORPEN);//取反色
    if(event!= button_judge(x,y))
    {
        last=event;
        event = button_judge(x,y);

        switch (last) {
            case 1:
                fillrectangle(r1[0],r1[1],r1[2],r1[3]);//有框填充矩形（X1,Y1,X2,Y2）
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
        setfillcolor(WHITE);
        switch (event) {
            case 1:
                fillrectangle(r1[0],r1[1],r1[2],r1[3]);//有框填充矩形（X1,Y1,X2,Y2）
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
    setrop2(R2_COPYPEN); // 将绘图模式设置回正常的覆盖模式
}

void Menu::GameOVer(){
    R4={r2[0],r2[1],r2[2],r2[3]};

    gettextstyle(&f);					//获取字体样式
    _tcscpy(f.lfFaceName,_T("宋体"));	//设置字体为宋体
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿
    f.lfHeight = 48;                        //设置高度
    settextstyle(&f);                     // 设置字体样式
    settextcolor(WHITE);
    drawtext("再玩一次",&R4,DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
    setlinecolor(WHITE);
    rectangle(r2[0],r2[1],r2[2],r2[3]);
    this->event=0;

}

void Menu::ButtonChange2(int x,int y){//重启检测
    setrop2(R2_XORPEN);//取反色
    if(event!= button_judge(x,y))
    {
        last=event;
        event = button_judge(x,y);

        switch (last) {
            case 2:
                fillrectangle(r2[0],r2[1],r2[2],r2[3]);
                break;
            default:
                break;
        }
        setfillcolor(WHITE);
        switch (event) {
            case 2:
                fillrectangle(r2[0],r2[1],r2[2],r2[3]);
                break;
            default:
                break;
        }

    }
    setrop2(R2_COPYPEN); // 将绘图模式设置回正常的覆盖模式
}

int Menu::GetPos(int n,int k){
    if(n==1)return r1[k];
    else if(n==2)return r2[k];
    else if(n==3)return r3[k];
}