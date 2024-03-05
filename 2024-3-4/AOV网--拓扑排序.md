## AOV网--拓扑排序：

### AOV网：

AOV代码：

```c
//Hash数据结构
typedef struct aList{//链
    int num;//数组位置
    struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//可入度
    char name[5];//项目名称
    int pass;//是否遍历--------------------------------------------------------
    int weight;//时间----------------------------------------------------------------------------------------------------
    L next;//链
}AL,*ALP;
```

![img](https://pic4.zhimg.com/80/v2-6a9542b1a3fb99a6e2726f0c3457e387_1440w.webp)

- 左侧为邻接数组`struct AOVList`
- 右侧为相邻的链`struct aList`



### 拓扑排序：

**广度优先BFS**

在图论中，拓扑排序（Topological Sorting）是一个有向无环图（DAG, Directed Acyclic Graph）的所有顶点的线性序列。且该序列必须满足下面两个条件：

- 每个顶点出现且只出现一次。

- 若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。

有向无环图（DAG）才有拓扑排序，非DAG图没有拓扑排序一说。

例如，下面这个图：

![img](https://img-blog.csdn.net/20150507001028284)

它是一个 DAG 图，那么如何写出它的拓扑排序呢？这里说一种比较常用的方法：

1. 从 DAG 图中选择一个 没有前驱（即入度为0）的顶点并输出。

2. 从图中删除该顶点和所有以它为起点的有向边。
3. 重复 1 和 2 直到当前的 DAG 图为空或当前图中不存在无前驱的顶点为止。后一种情况说明有向图中必然存在环。

![img](https://img-blog.csdn.net/20150507001759702)

于是，得到拓扑排序后的结果是 { 1, 2, 4, 3, 5 }。

通常，一个有向无环图可以有一个或多个拓扑排序序列。


*如果输出的顶点少于实际的顶点个位，必定有环*



#### 代码实现：

由栈实现：

1. 遍历邻接数组，找到可入度为0的入栈；
2. 弹出栈的元素，输出；
3. 遍历顶点的邻接链，可入度都-1，如果有可入度为0入栈；
4. 重复2，3直到清空栈；
5. 检测如果输出的少于实际顶点数，说明有环；



```c
bool Compare(AL p[],int i){//排序数组 
    //-----------------排序-----------------
    ALP ap0;//单个表单的地址
    int put_l=0;//输出长度
    
    list ps=(list) malloc(sizeof (Stack));//建栈
    ps->pointer=-1;//初始化栈指针
    
    for (int j = 0; j < i; ++j) {
        if(p[j].num==0) push(ps,&p[j]);//入栈
    }
    
    ap0= pop(ps);
    while (ap0!=NULL) {
        printf("%s\t",ap0->name);
        is[ap0->name[0]]= false;//节点已经输出---------------
        put_l++;
        
        for (L j = ap0->next; j != NULL; j = j->next) {
            p[j->num].num--;//可入度-1
            if (p[j->num].num == 0) push(ps, &p[j->num]);//可入度为0 入栈
        }
        ap0= pop(ps);
    }
    
    //--------------闭环处理---------------------
    if(put_l<i){
        printf("有闭环\n");
        return false;
    } else return true;
    //-----------------------------------------
}
```

