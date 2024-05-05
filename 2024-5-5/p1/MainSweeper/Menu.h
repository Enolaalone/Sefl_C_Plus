#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QPushButton>
#include <QMenu>

class Menu:public QWidget{
    Q_OBJECT//使用Qt的信号和槽机制
public:
    Menu(QWidget *parent = nullptr):QWidget(parent){
        QPushButton * Button =new QPushButton("菜单",this);//菜单按钮
        QMenu *mn = new QMenu(this);//菜单

        QAction *easy = mn->addAction("简单");
        QAction *medium = mn->addAction("中等");
        QAction *hard = mn->addAction("困难");

        Button->setMenu(mn);

        connect(easy,&QAction::triggered,this,&Menu::EasyTriggered);//将点击活动关联到菜单发出的信号
        connect(medium,&QAction::triggered,this,&Menu::MediumTriggered);
        connect(hard,&QAction::triggered,this,&Menu::HardTriggered);
    }
signals://信号函数
    void EasyTriggered();
    void MediumTriggered();
    void HardTriggered();
};

#endif // MENU_H
