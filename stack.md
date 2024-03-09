### stack

栈是基本的数据结构之一,特点是先进后出,就如开进死胡同的车队,先进去的只能最后出来.

在c++ 中,stack的头文件是#include<stack>

stack常用操作

```c++
stack<int> q;	//以int型为例
int x;
q.push(x);		//将x压入栈顶
q.top();		//返回栈顶的元素
q.pop();		//删除栈顶的元素
q.size();		//返回栈中元素的个数
q.empty();		//检查栈是否为空,若为空返回true,否则返回false
```



```c++
#include<iostream>
#include<stack>
using namespace std;
int main()
{
	stack<int>  q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	
cout<<"q.size "<<q.size()<<endl;
cout<<"q.top "<<q.top()<<endl;   //输出栈顶元素 

q.pop();	//删除栈顶元素
		
cout<<"q.size "<<q.size()<<endl;  
cout<<"q.top "<<q.top()<<endl;

return 0; 
```

}

#### 栈顶弹出：

```c++
stack<int> s;
int a = s.top();
s.pop();
```

