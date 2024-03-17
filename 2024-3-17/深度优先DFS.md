### 深度优先DFS:



#### 邻接表的DFS:

> 无断点，无环
>
> 如果有断点不连续，可以在递归的外部加for循环，遍历Graph

```c
int DfS(Graph *G,int i){
    if(!visited[i])  return 0;

    printf("%d %c",G->vertices[i].data,G->vertices[i].key);
    visited[i]=1;//标记正在访问

    for (ArcNode* p = G->vertices[i].next; p!=NULL; p=p->next)
    {
        if (!visited[p->val]){//未访问
            DfS(G,p->val);
            visited[i]=-1;//访问结束
        }
        //else return p->val;//返回环的位置
    }
    return 1;
}

```

##### 原理：

visited数组记录，是否访问；

通过for循环遍历邻接链，不断访问下一节点；



#### 全排序（DFS）

##### 一、基本思想

1. 为了求得问题的解，先选择某一种可能情况向前探索；
2. 在探索过程中，一旦发现原来的选择是错误的，就退回一步重新选择，继续向前探索；
3. 如此反复进行，直至得到解或证明无解。

##### 二、操作步骤：

1. 初始原点为v0，使用深度优先搜索，首先访问 v0 -> v1 -> v2 -> v5，到 v5 后面没有结点，则回溯到 v1 ，即**最近的且连接有没访问结点的结点v1**；
2. 此次从 v1 出发，访问 v1 -> v4 -> v6 -> v3，此时与v3相连的两个结点 v0 与 v6 都已经访问过，回溯到 v6 (**v6 具有没访问过的结点**)；
3. 此次从 v6 出发，访问 v6 -> v7，到 v7 后面没有结点，回溯；
4. 一直回溯到**源点** v0 ，没有没访问过的结点，程序结束。

注：下面图中箭头为**回溯方向**
![在这里插入图片描述](https://img-blog.csdnimg.cn/30255bfd65604c058b65c0c009a00da5.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAMjHlsoHooqvov6vnp4PlpLQ=,size_10,color_FFFFFF,t_70,g_se,x_16#pic_center)

> C++:{1,2,3}

```c++
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    vector<vector<int>>a;//初始二维数组
    map<int,int> book;
    vector<int> b;

    void DFS(int cur, int n, vector<int>& nums){//遍历次数 去除数个数 数组
        if (cur==n){
            a.push_back(b);//排列完成加入数组a
            return;//结束
        }
        for (int i = 0; i < n; i++){
            if (!book[nums[i]])//未访问{
                b.push_back(nums[i]);
                book[nums[i]] = 1;//标记访问
                DFS(cur + 1, nums.size(), nums);
                book[nums[i]] = 0;//结束访问
                b.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {//返回值是二维数组
        DFS(0, nums.size(), nums);
        return a;
    }
};

int main() {
    vector<int> nums{ 1,2,3 };
    Solution solution;
    vector<vector <int>> k = solution.permute(nums);
    for (int i = 0; i < k.size(); i++)
    {
        for (int j = 0; j < 3; j++) {
            cout << k[i][j];
        }
        cout << endl;
    }

}
```

