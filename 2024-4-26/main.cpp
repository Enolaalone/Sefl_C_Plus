#include <iostream>
#include "MineField.h"
using namespace std;

class MineSweeper{
public:
    MineField field;
    int location_l,location_r;//��¼ѡλ��

    void Running(){
        this->Setting();
        while(1){
            cout<<"���뷭����λ�ã�x,y"<<endl;
            //cin.clear();
            scanf("%d,%d",&this->location_l,&this->location_r);

            this->field.Extend(this->location_l-1,this->location_r-1);

            this->field.Print2();
            this->field.Print();
            if(this->field.state== on)continue;
            else if(this->field.state == win){
                cout<<"��ϲͨ�أ�";
                break;
            } else{
                cout<<"������Ϸʧ�ܣ�";
                break;
            }
        }


    }
    void Setting(){
        /*cout<<"���������߳���������"<<endl;
        scanf("%d",&this->field.paneLine);
        cout<<"����������������"<<endl;
        scanf("%d",&this->field.paneNum);*/

        //���ԣ�
        this->field.paneLine=10;
        this->field.paneNum=10;

        this->field.Mines();//������ʼ��
        this->field.MineSet();//���õ���
        this->field.Print2();//���Դ�ӡ

        this->field.RecordAroundMines();//��ѯ��Χ������Ŀ
        this->field.Print();//��ӡ

    }


    MineSweeper():location_l(0),location_r(0){}//��ʼ��
};




int main() {
    MineSweeper mineSweeper;
    mineSweeper.Running();



    return 0;
}
