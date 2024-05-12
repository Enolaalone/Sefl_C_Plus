#include "Form.h"

Form::Form():Width(225),Height(290),Running(true){
    Run(E,10);
}


void Form::Setting(int line,int num){//初始化
    //测试：
    this->field.SetPaneline(line);
    this->field.SetPanenum(num);
    //雷区
    this->field.ReFlied();
    this->field.Mines(this->Height);//雷区初始化
    this->field.MineSet();//设置地雷
    this->field.RecordAroundMines();//查询周围地雷数目
    this->field.Print();//打印
    //用户区域
    this->setting.setBack(this->Width);//区域框
    this->setting.emojiSet();//按钮
    this->setting.SetTimer();//计时器
    this->setting.SetFlags(this->field.GetPanenum());//计数器
    //难度
    this->menu.Set();

}

void Form::Run(int line,int num){//运行游戏
    initgraph(this->Width,this->Height);//窗口
    setbkcolor(RGB(204,204,204));//设置背景颜色
    cleardevice();
    this->Setting(line,num);

    while(this->Running){
        this->setting.timer.Show();//开始计时
        while(MouseHit()){//检测到鼠标点击
            MouseHandle();//鼠标事件处理
        }
    }
}


void Form::MouseHandle(){//处理鼠标点击
    MOUSEMSG m=GetMouseMsg();
    switch (m.uMsg) {
        case WM_LBUTTONDOWN://左键按下
            //cout<<m.x<<","<<m.y<< endl;//打印鼠标位置
            this->Mpos_L(m.x,m.y, true);//点击事件
            this->JudgeState(m.x,m.y);
            break;
        case WM_RBUTTONDOWN://右键按下
            this->Mpos_R(m.x,m.y);//左键插旗
            this->JudgeState(m.x,m.y);

            break;
        case WM_LBUTTONUP://模拟点击
            this->Resetting(m.x,m.y);
            if(this->Mpos_L(m.x,m.y, false))
                this->Setting(this->field.GetPaneline(), this->field.GetPanenum());
            break;
        case WM_MOUSEMOVE://检测菜单
            this->menu.ButtonChange(m.x,m.y);
            break;
        case WM_CLOSE://关闭
            this->Running= false;
            // 关闭绘图窗口
            closegraph();
            break;
    }

}


void Form::JudgeState(int mx,int my){//检测游戏状态
    if(!this->setting.flags.GetState()){//旗子插完,检测游戏是否结束
        if(this->field.JudgeWin2())this->field.SetGameState(win);
    }

    //游戏开始，点击雷区开始计时
    if(this->field.GetGameState()==gameStates::on && mx>=0&&mx<=this->Width&& my>= this->Height-(this->field.GetPaneline()*BLOCK))this->setting.timer.SetState(true);
    //胜利
    else if(this->field.GetGameState()==gameStates::win){
        this->setting.emoji.Unpress(States::Cool);
        this->setting.timer.SetState(false);//停止计时
    }
    //失败
    else if(this->field.GetGameState()==gameStates::end){
        this->setting.emoji.Unpress(States::Die);
        this->setting.timer.SetState(false);//停止计时
    }
}


bool Form::Mpos_L(int x,int y,bool press){//左键点击事件
    int Bx=this->setting.emoji.GetPos().first;
    int By=this->setting.emoji.GetPos().second;

    if(this->field.GetGameState()==on&&x>=0&&x<this->Width && y>=(Height-BLOCK* this->field.GetPaneline())&&y<=Height&&press) {//点击雷区
        //确定地雷的坐标
        int j=x/BLOCK;
        int i=(y-(Height-BLOCK * this->field.GetPaneline()))/BLOCK;

        //关闭状态
        if(this->field.GetPanes()[i][j].GetState()==Closed){
            if(this->field.GetPanes()[i][j].GetIsMine()){//点击到雷
                this->field.JudgeEnd(i,j);
            } else{//递归扩展
                this->field.ExtendingDP(pair<int,int>(i,j));
            }
        }

        //标记状态
        else if(this->field.GetPanes()[i][j].GetState()==Marked){
            this->field.GetPanes()[i][j].Close(this->field.GetImagine());
            this->setting.flags.AddOrDes(true);//旗子++
        }

    }
    //点击重启按钮
    else if(x>=Bx&&x<=Bx+BLOCK&&y>=By&&y<=By+BLOCK&&press){//按下动画
        this->setting.emoji.Press();
    }
    else if(x>=Bx&&x<=Bx+BLOCK&&y>=By&&y<=By+BLOCK&&!press){//弹起动画
        this->setting.emoji.Unpress(States::Happy);
        return true;
    }
    return false;
}


void Form::Mpos_R(int x,int y){
    if(this->field.GetGameState()==on&&x>=0&&x<this->Width && y>=(Height-25* this->field.GetPaneline())&&y<=Height) {//点击雷区
        int j=x/BLOCK;
        int i=(y-(Height-BLOCK * this->field.GetPaneline()))/BLOCK;
        if(this->field.GetPanes()[i][j].GetState()==Closed&&this->setting.flags.GetState()) {//雷块未翻开，而且还有旗子
            this->field.GetPanes()[i][j].Mark(this->field.GetImagine());
            this->setting.flags.AddOrDes(false);//旗子减1
        }
    }
}

void Form::Resetting(int x,int y){//从新开始游戏
    if(x>=this->menu.r1[0] && x<= this->menu.r1[2] && y>=this->menu.r1[1]  && y<=this->menu.r1[3] ){//简单
        closegraph();
        this->Width=BLOCK*E;
        this->Height=BLOCK*E+65;
        this->Run(E,10);
    };
    if(x>=this->menu.r2[0] && x<= this->menu.r2[2] && y>=this->menu.r2[1]  && y<=this->menu.r2[3] ){//中等
        closegraph();
        this->Width=BLOCK*M;
        this->Height=BLOCK*M+65;
        this->Run(M,40);
    };
    if(x>=this->menu.r3[0] && x<= this->menu.r3[2] && y>=this->menu.r3[1]  && y<=this->menu.r3[3] ){//困难
        closegraph();
        this->Width=BLOCK*H;
        this->Height=BLOCK*H+65;
        this->Run(H,100);
    };


}

