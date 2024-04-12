# `pair`&`decltype`&`Lambda`函数

## `pair<int,int>`

### 头文件：

其标准库类型--pair类型定义在#include <utility>头文件中;

**注意：**由于 map 的内部实现中涉及 pair，因此添加 map 头文件时会自动添加 utility 头文件，此时如果需要使用 pair ，就不需要额外再去添加 utility 头文件了。

### 定义：

pair是将2个数据组合成一组数据,在C++中，`pair<int, int>`是一个简单的结构体，用于存储和管理一对元素，这两个元素都是整数类型。`pair`类型是标准模板库（STL）的一部分，广泛用于需要将两个值捆绑在一起的情况。

### 访问:

`pair<int, int>`中的两个元素分别可以通过`.first`和`.second`成员访问。

### 比较：

两个 pair 类型数据可以直接使用 ==，！=，<，<=，>，>= 比较大小，比较规则是先以 first 的大小作为标准，只有当 first 相等时才去判别 second 的大小。

### EG:

例如，如果你有一个`pair<int, int> p = {3, 5};`，那么`p.first`的值为3，`p.second`的值为5。这种类型经常用在需要通过两个维度的索引来访问数据的情况下

```c++
pair<string, string> anon;        // 创建一个空对象anon，两个元素类型都是string
pair<string, int> word_count;     // 创建一个空对象 word_count, 两个元素类型分别是string和int类型
pair<string, vector<int> > line;  // 创建一个空对象line，两个元素类型分别是string和vector类型
```



## `decltype`

`decltype`的类型推导并不是像auto一样是从变量声明的初始化表达式获得变量的类型，而是总是**以一个普通表达式作为参数**，返回该表达式的类型,而且`decltype`并**不会对表达式进行求值**。

## Lambda:

在C++中，Lambda 函数提供了一种便捷的方式来定义匿名函数对象。Lambda 函数自C++11起被引入，广泛用于简短的函数定义，尤其是在STL算法中常与容器一起使用。Lambda 函数的语法如下：

```cpp
[capture](parameters) -> return_type {
    // function body
};
```

其中各部分的含义如下：
- **capture**：捕获列表，定义了Lambda 函数体内可以访问的外部变量，以及访问方式（如值传递、引用传递等）。
- **parameters**：参数列表，与普通函数的参数类似。
- **return_type**：返回类型，可以省略，在省略的情况下，如果函数体内包含`return`语句，则返回类型会自动推导。
- **function body**：函数体，包含了Lambda的执行代码。

### 示例

下面是一个简单的示例，展示了如何使用Lambda函数对一个整数数组进行排序：

```cpp
#include <iostream>
int main() {
    // 定义一个 Lambda 表达式并赋值给变量 add
    auto add = [](int a, int b) {
        return a + b;
    };
    // 使用 Lambda 表达式
    int result = add(10, 20);
    // 输出结果
    std::cout << "10 + 20 = " << result << std::endl;
    return 0;
}
```



Lambda表达式的捕获列表在这个例子中是空的（`[]`），因为Lambda内部没有使用任何外部变量。如果需要使用外部变量，可以通过值（`[=]`）、引用（`[&]`）、指定变量的值捕获（`[x, y]`）或引用捕获（`[&x, &y]`）等方式来指定。
