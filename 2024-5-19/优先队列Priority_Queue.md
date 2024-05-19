# 优先队列Priority_Queue

## 队列基本操作:

- top 访问队头元素
- empty 队列是否为空
- size 返回队列内元素个数
- push 插入元素到队尾 (并排序)
- emplace 原地构造一个元素并插入队列
- pop 弹出队头元素
- swap 交换内容



![在这里插入图片描述](https://img-blog.csdnimg.cn/2019112221252138.png)

## **需要使用的头文件：**

```cpp
#include <queue>
```

## 优先队列定义：



`priority_queue<Type, Container, Functional>`

- Type 就是数据类型，
- Container 就是容器类型（Container必须是用数组实现的容器，比如vector,deque等等，但不能用 list。STL里面默认用的是vector），
- Functional 就是比较的方式，
- 当需要用自定义的数据类型时才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，默认是大顶堆
  

```c
//升序队列
priority_queue <int,vector<int>,greater<int> > q;
//降序队列
priority_queue <int,vector<int>,less<int> >q;

//greater和less是std实现的两个仿函数（就是使一个类的使用看上去像一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了）

```

### Type:

可以为`int double`等数据类型；

也可以为`vector<int>`类型；

### Container：

可以为`vector deque`等数据类型；

也可以为`vector<vector<int>>`特殊类型；

### Functional:

#### 固有排序方式：

##### **大根堆：less 表趋势**

它允许用户为队列中元素设置优先级，放置元素的时候不是直接放到队尾，而是放置到比它优先级低的元素前面，标准库默认使用`<`操作符来确定优先级关系。

注意：这里的`小于号<`规定了优先级，表示优先队列后面的元素都要小于优先队列前面的元素，**因为优先队列队首的元素优先级最高，优先队列队尾元素的优先级最低**，所以`小于号<`就规定了**优先队列后面的元素都要小于优先队列前面的元素**（尾部优先级小于首部优先级），也就是形成一个**大根堆**，**降序排序**，每次权值最大的会被弹出来。



##### **小根堆：greater** 表趋势

使用函数对象`greater<int>`来生成小根堆

注意：这里的`大于号>`规定了优先级，表示优先队列后面的元素都要大于优先队列前面的元素，因为优先队列队首的元素优先级最高，优先队列队尾元素的优先级最低，所以`大于号>`就规定了**优先队列后面的元素都要大于优先队列前面的元素**（尾部优先级小于首部优先级），也就是形成一个**小根堆**，**升序排序**，每次权值最小的会被弹出来。

## 自定义排序方式：

### 看排序方式：

> **参数输入顺序下`return` 中后者的值优先级别更高，排在队列前面**

- `return a>b;` 
- `return a<b;`

**构造函数需要实例**：当你声明一个 `priority_queue` 时，如果你使用了一个自定义的比较器类型（如 `decltype(cmp)`），则必须在构造 `priority_queue` 的时候提供一个该类型的实例。如果你只是声明了 `priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq;` 而没有提供 `cmp`，编译器不会知道如何初始化这个队列的内部比较逻辑。

 `priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp)`



在 C++ 中，可以通过指定自定义比较函数（或函数对象）来创建一个自定义排序的 `priority_queue`。标准库中的 `priority_queue` 默认是一个最大堆（最大元素在队列顶部），你可以通过传递自定义比较函数来改变这一行为。

这里有两个主要的方法来实现自定义排序：

1. **使用函数对象（仿函数）**
2. **使用函数指针或 lambda 表达式**

### 方法一：使用函数对象（仿函数）

首先，你需要定义一个函数对象，重载 `operator()` 来定义排序规则。然后在声明 `priority_queue` 时，将这个函数对象作为模板参数传递。

```cpp
#include <iostream>
#include <queue>
#include <vector>

// 自定义比较函数对象
struct CustomCompare {
    bool operator()(const int& lhs, const int& rhs) {
        // 定义排序规则，例如：最小堆
        return lhs > rhs;  // 返回 true 表示 lhs 应该排在 rhs 后面
    }
};

int main() {
    // 定义一个使用自定义比较函数的优先队列
    std::priority_queue<int, std::vector<int>, CustomCompare> pq;

    // 添加元素
    pq.push(10);
    pq.push(5);
    pq.push(20);

    // 输出优先队列中的元素
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    // 输出：5 10 20

    return 0;
}
```

```
 struct Compare//根据元组和排序
    {
        bool operator() (const vector<int>& a, const vector<int>& b) {
            return ((a[0] + a[1]) > (b[0] + b[1]));//返回bool值
        }
    };
```



### 方法二：使用函数指针或 lambda 表达式

可以直接使用 lambda 表达式来定义比较函数，并在声明 `priority_queue` 时传递它。

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <functional>  // std::greater

int main() {
    // 使用 lambda 表达式定义自定义比较函数
    auto cmp = [](int lhs, int rhs) {
        return lhs > rhs;  // 定义排序规则，例如：最小堆
    };

    // 定义一个使用自定义比较函数的优先队列
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

    // 添加元素
    pq.push(10);
    pq.push(5);
    pq.push(20);

    // 输出优先队列中的元素
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    // 输出：5 10 20

    return 0;
}
```



## EG:

-   priority_queue<> 需要指定数据类型，
- 排序方式为**大根堆**；

```c++
    priority_queue<int> q;
    q.push(2);
    q.push(3);
    for (size_t i = q.size(); i>0 ; i--)
    {
        cout<<q.top()<<endl;
        q.pop();
    }
//输出：
//3
//2
```



//注意后面两个“>”不要写在一起，“>>”是右移运算

```c++
    priority_queue< int,vector<int>,greater<int> > q;符
    q.push(3);
    q.push(2);

    for (size_t i = q.size(); i>0 ; i--){
        cout<<q.top()<<endl;
        q.pop();
    }

//输出：

// 2
// 3
```

