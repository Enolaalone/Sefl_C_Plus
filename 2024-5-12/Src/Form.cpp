#include "Form.h"

Form::Form():Width(225),Height(290),Running(true){
    Run(E,10);
}


void Form::Setting(int line,int num){//��ʼ��
    //���ԣ�
    this->field.SetPaneline(line);
    this->field.SetPanenum(num);
    //����
    this->field.ReFlied();
    this->field.Mines(this->Height);//������ʼ��
    this->field.MineSet();//���õ���
    this->field.RecordAroundMines();//��ѯ��Χ������Ŀ
    this->field.Print();//��ӡ
    //�û�����
    this->setting.setBack(this->Width);//�����
    this->setting.emojiSet();//��ť
    this->setting.SetTimer();//��ʱ��
    this->setting.SetFlags(this->field.GetPanenum());//������
    //�Ѷ�
    this->menu.Set();

}

void Form::Run(int line,int num){//������Ϸ
    initgraph(this->Width,this->Height);//����
    setbkcolor(RGB(204,204,204));//���ñ�����ɫ
    cleardevice();
    this->Setting(line,num);

    while(this->Running){
        this->setting.timer.Show();//��ʼ��ʱ
        while(MouseHit()){//��⵽�����
            MouseHandle();//����¼�����
        }
    }
}


void Form::MouseHandle(){//���������
    MOUSEMSG m=GetMouseMsg();
    switch (m.uMsg) {
        case WM_LBUTTONDOWN://�������
            //cout<<m.x<<","<<m.y<< endl;//��ӡ���λ��
            this->Mpos_L(m.x,m.y, true);//����¼�
            this->JudgeState(m.x,m.y);
            break;
        case WM_RBUTTONDOWN://�Ҽ�����
            this->Mpos_R(m.x,m.y);//�������
            this->JudgeState(m.x,m.y);

            break;
        case WM_LBUTTONUP://ģ����
            this->Resetting(m.x,m.y);
            if(this->Mpos_L(m.x,m.y, false))
                this->Setting(this->field.GetPaneline(), this->field.GetPanenum());
            break;
        case WM_MOUSEMOVE://���˵�
            this->menu.ButtonChange(m.x,m.y);
            break;
        case WM_CLOSE://�ر�
            this->Running= false;
            // �رջ�ͼ����
            closegraph();
            break;
    }

}


void Form::JudgeState(int mx,int my){//�����Ϸ״̬
    if(!this->setting.flags.GetState()){//���Ӳ���,�����Ϸ�Ƿ����
        if(this->field.JudgeWin2())this->field.SetGameState(win);
    }

    //��Ϸ��ʼ�����������ʼ��ʱ
    if(this->field.GetGameState()==gameStates::on && mx>=0&&mx<=this->Width&& my>= this->Height-(this->field.GetPaneline()*BLOCK))this->setting.timer.SetState(true);
    //ʤ��
    else if(this->field.GetGameState()==gameStates::win){
        this->setting.emoji.Unpress(States::Cool);
        this->setting.timer.SetState(false);//ֹͣ��ʱ
    }
    //ʧ��
    else if(this->field.GetGameState()==gameStates::end){
        this->setting.emoji.Unpress(States::Die);
        this->setting.timer.SetState(false);//ֹͣ��ʱ
    }
}


bool Form::Mpos_L(int x,int y,bool press){//�������¼�
    int Bx=this->setting.emoji.GetPos().first;
    int By=this->setting.emoji.GetPos().second;

    if(this->field.GetGameState()==on&&x>=0&&x<this->Width && y>=(Height-BLOCK* this->field.GetPaneline())&&y<=Height&&press) {//�������
        //ȷ�����׵�����
        int j=x/BLOCK;
        int i=(y-(Height-BLOCK * this->field.GetPaneline()))/BLOCK;

        //�ر�״̬
        if(this->field.GetPanes()[i][j].GetState()==Closed){
            if(this->field.GetPanes()[i][j].GetIsMine()){//�������
                this->field.JudgeEnd(i,j);
            } else{//�ݹ���չ
                this->field.ExtendingDP(pair<int,int>(i,j));
            }
        }

        //���״̬
        else if(this->field.GetPanes()[i][j].GetState()==Marked){
            this->field.GetPanes()[i][j].Close(this->field.GetImagine());
            this->setting.flags.AddOrDes(true);//����++
        }

    }
    //���������ť
    else if(x>=Bx&&x<=Bx+BLOCK&&y>=By&&y<=By+BLOCK&&press){//���¶���
        this->setting.emoji.Press();
    }
    else if(x>=Bx&&x<=Bx+BLOCK&&y>=By&&y<=By+BLOCK&&!press){//���𶯻�
        this->setting.emoji.Unpress(States::Happy);
        return true;
    }
    return false;
}


void Form::Mpos_R(int x,int y){
    if(this->field.GetGameState()==on&&x>=0&&x<this->Width && y>=(Height-25* this->field.GetPaneline())&&y<=Height) {//�������
        int j=x/BLOCK;
        int i=(y-(Height-BLOCK * this->field.GetPaneline()))/BLOCK;
        if(this->field.GetPanes()[i][j].GetState()==Closed&&this->setting.flags.GetState()) {//�׿�δ���������һ�������
            this->field.GetPanes()[i][j].Mark(this->field.GetImagine());
            this->setting.flags.AddOrDes(false);//���Ӽ�1
        }
    }
}

void Form::Resetting(int x,int y){//���¿�ʼ��Ϸ
    if(x>=this->menu.r1[0] && x<= this->menu.r1[2] && y>=this->menu.r1[1]  && y<=this->menu.r1[3] ){//��
        closegraph();
        this->Width=BLOCK*E;
        this->Height=BLOCK*E+65;
        this->Run(E,10);
    };
    if(x>=this->menu.r2[0] && x<= this->menu.r2[2] && y>=this->menu.r2[1]  && y<=this->menu.r2[3] ){//�е�
        closegraph();
        this->Width=BLOCK*M;
        this->Height=BLOCK*M+65;
        this->Run(M,40);
    };
    if(x>=this->menu.r3[0] && x<= this->menu.r3[2] && y>=this->menu.r3[1]  && y<=this->menu.r3[3] ){//����
        closegraph();
        this->Width=BLOCK*H;
        this->Height=BLOCK*H+65;
        this->Run(H,100);
    };


}

