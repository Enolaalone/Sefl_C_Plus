#include <iostream>
#include <vector>
#include "Pane.h"
using namespace std;

Pane** MineSet(int num){
    Pane **panes=new Pane*[num];//指针数组地址分配给 二维指针panes;
    for (int i = 0; i < num; ++i) {
        panes[i]= new Pane[num];//Pane组的地址给 pane[i]
    }
    return panes;//返回生成的雷组
}

void Print(Pane**panes,int num){
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j) {

        }
    }

}

int main() {



    return 0;
}
