## 顶层const和底层const

首先顶层const和底层const的说法和指针有很大的关系。指针本身是一个对象，但它又指向另一个对象，这就是指针的两种属性。

- 对于指针本身是一个常量，即指针的指向是一个常量，也就说不能改变指针的指向，称其为顶层const属性；
- 对于指针指向的对象是一个常量，即指针指向的地址的值是一个常量，也就是说不能改变指针指向内存的值，称其为底层 const属性。

在代码表现上是：



```c++
int* cosnt p1 = &a;//p1是顶层const
cosnt int* p2 = &a;//p2是底层const
```



### 区分：

区分很简单，看const修饰的是哪个。前者修饰的是p1，即指针本身，所以为顶层属性；后者修饰的*p2，即指针的指向地址的值，所以为底层属性。p1又称为常量指针，p2又称为指向常量的指针。

### 总结：

1. 顶层const在赋值给其他变量时，可以忽略顶层属性；
2. 底层const在赋值给其他变量时，不能忽略底层属性；
3. int*类型可以转换为顶层和底层const，所以它可以给顶层和底层的const赋值；
4. 底层const无法转换为顶层const。





# auto的用法

上面举的这个例子很简单，在真正编程的时候也不建议这样来使用auto，直接写出变量的类型更加清晰易懂。下面列举auto关键字的正确用法。

### 用于代替冗长复杂、变量使用范围专一的变量声明。

想象一下在没有auto的时候，我们操作标准库时经常需要这样：

```cpp
#include<string>
#include<vector>
int main()
{
    std::vector<std::string> vs;
    for (std::vector<std::string>::iterator i = vs.begin(); i != vs.end(); i++)
    {
        //...
    }
}
```

这样看代码写代码实在烦得很。有人可能会说为何不直接使用using namespace std，这样代码可以短一点。实际上这不是该建议的方法（C++Primer对此有相关叙述）。使用auto能简化代码：

```cpp
#include<string>
#include<vector>
int main()
{
    std::vector<std::string> vs;
    for (auto i = vs.begin(); i != vs.end(); i++)
    {
        //..
    }
}
```

for循环中的i将在编译时自动推导其类型，而不用我们显式去定义那长长的一串。

### 在定义模板函数时，用于声明依赖模板参数的变量类型。

```cpp
template <typename _Tx,typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    auto v = x*y;
    std::cout << v;
}
```

若不使用auto变量来声明v，那这个函数就难定义啦，不到编译的时候，谁知道x*y的真正类型是什么呢？

### 模板函数依赖于模板参数的返回值

```cpp
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(_Tx*_Ty)
{
    return x*y;
}
```

当模板函数的返回值依赖于模板的参数时，我们依旧无法在编译代码前确定模板参数的类型，故也无从知道返回值的类型，这时我们可以使用auto。格式如上所示。
decltype操作符用于查询表达式的数据类型，也是C++11标准引入的新的运算符，其目的也是解决泛型编程中有些类型由模板参数决定，而难以表示它的问题。
auto在这里的作用也称为**返回值占位**，它只是为函数返回值占了一个位置，真正的返回值是后面的decltype(_Tx*_Ty)。为何要将返回值后置呢？如果没有后置，则函数声明时为：

```cpp
decltype(_Tx*_Ty)multiply(_Tx x, _Ty y)
```

而此时_Tx,_Ty还没声明呢，编译无法通过。

### 注意事项

- auto 变量必须在定义时初始化，这类似于const关键字。
- 定义在一个auto序列的变量必须始终推导成同一类型。例如：

```cpp
    auto a4 = 10, a5 = 20, a6 = 30;//正确
    auto b4 = 10, b5 = 20.0, b6 = 'a';//错误,没有推导为同一类型
```

使用auto关键字做类型自动推导时，依次施加一下规则：

- 如果初始化表达式是引用，则去除引用语义。

```cpp
    int a = 10;
    int &b = a;
 
    auto c = b;//c的类型为int而非int&（去除引用）
    auto &d = b;//此时c的类型才为int&
 
    c = 100;//a =10;
    d = 100;//a =100;
```

- 如果初始化表达式为const或volatile（或者两者兼有），则除去const/volatile语义。

```cpp
    const int a1 = 10;
    auto  b1= a1; //b1的类型为int而非const int（去除const）
    const auto c1 = a1;//此时c1的类型为const int
    b1 = 100;//合法
    c1 = 100;//非法
```

- 如果auto关键字带上&号，则不去除const语意。

```cpp
    const int a2 = 10;
    auto &b2 = a2;//因为auto带上&，故不去除const，b2类型为const int
    b2 = 10; //非法
```

这是因为如何去掉了const，则b2为a2的非const引用，通过b2可以改变a2的值，则显然是不合理的。

- 初始化表达式为数组时，auto关键字推导类型为指针。

```cpp
    int a3[3] = { 1, 2, 3 };
    auto b3 = a3;
    cout << typeid(b3).name() << endl;
```

程序将输出

> int *

- 若表达式为数组且auto带上&，则推导类型为数组类型。

```cpp
    int a7[3] = { 1, 2, 3 };
    auto & b7 = a7;
    cout << typeid(b7).name() << endl;
```

程序输出

> int [3]

- 函数或者模板参数不能被声明为auto

```cpp
void func(auto a)  //错误
{
    //... 
}
```

- 时刻要注意auto并不是一个真正的类型。
  auto仅仅是一个占位符，它并不是一个真正的类型，不能使用一些以类型为操作数的操作符，如sizeof或者typeid。

```cpp
    cout << sizeof(auto) << endl;//错误
    cout << typeid(auto).name() << endl;//错误
```



### 使用：

for (auto x : nums)的作用：
相当于：
for (vector< int >::iterator iter = nums.begin(); iter != nums.end(); iter++)

- for(auto a:b)中b为一个容器，效果是利用a遍历并获得b容器中的每一个值，但是a无法影响到b容器中的元素。
- for(auto &a:b)中加了引用符号，可以对容器中的内容进行赋值，即可通过对a赋值来做到容器b的内容填充。

```c++
 for (auto &x:a)//引用a
    {
        x=0;
        cout<<x<<endl;
    }
    cout<<endl;

    for (auto y:a)//创建y=a,遍历y
    {
        cout<<y<<endl;
    }
```

