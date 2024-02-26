## c++的命名空间namespace

命名不同空间，以防相同命名的冲突

### 定义：

```c++
//定义一个名字为A的命名空间（变量、函数）
namespace A {
    int a = 100;
}
namespace B {
    int a = 200;
}
void test02()
{
    //A::a  a是属于A中
    cout<<"A中a = "<<A::a<<endl;//100
    cout<<"B中a = "<<B::a<<endl;//200
}
```

*命名空间只能在全局定义，不能在函数中定义*

### 嵌套：

```c++
namespace A {
    int a = 100;
    int b = 200;
}
//将c添加到已有的命名空间A中
namespace A {
    int c = 300;
}
```

打印输出：

```c++
void test03()
{
    cout<<"A中的a = "<<A::a<<endl; //1000
    cout<<"B中的a = "<<A::B::a<<endl; //2000
}
```

`: :`打开空间

### 添加：

```c++
namespace A {
    int a = 100;
    int b = 200;
}
//将c添加到已有的命名空间A中
namespace A {
    int c = 300;
}
```

### 命名空间——函数：

空间内定义：

```c++
namespace A {
    int a=100;//变量
 
    void func()//函数
    {
        cout<<"func遍历a = "<<a<<endl;
    }
}
```

空间外定义：

```c++
namespace A {
    int a=100;//变量
 
    void func();
}
 
void A::func()//成员函数 在外部定义的时候 记得加作用域
{
    //访问命名空间的数据不用加作用域
    cout<<"func遍历a = "<<a<<endl;
}
```

### 无名空间：

无名命名空间，又称为未命名的命名空间。是指关键字namespace后紧跟花括号括起来的一系列声明语句，不需要对命名空间取名。

```c++
namespace {
    int a = 10;
    int get(void)
    {
        return 20;
    }
}
```



生命周期：

无名命名空间中定义的变量拥有同静态变量一样的生命周期，在第一次使用前创建，直到程序结束才销毁。

作用域：

无名命名空间中定义的成员的作用域与该命名空间所在的作用域相同。比如，如果在某个源文件中定义无名命名空间，则该无名命名空间只在该源文件能访问。
