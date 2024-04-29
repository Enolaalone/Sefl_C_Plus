#include <iostream>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>



int main()
{
    initgraph(640, 480);//窗口

    IMAGE img[26];
    char filename[50];
    for (int i = 0; i < 26; i++)
    {
        sprintf(filename, "D:\\C\\MineSweeperEX\\Resources\\%d.gif", i + 1);
        loadimage(&img[i],filename);
    }

    for (int i = 0; i < 26; i++)
        putimage(i * 25, 0, &img[i]);

    // 关闭绘图窗口
    _getch();
    closegraph();
    return 0;
}


