## new:

创建数据所需空间，赋值，返回指针；

假如有一个类A，那么下面这条语句：

```c++
A* pa = new A(3);
```


大致相当于以下三句话的作用（注意只是大致上）：

```c++
A* pa = (A*)malloc(sizeof(A)); //在堆上为对象分配内存空间
pa->A::A(3); //调用类A的构造函数对对象进行初始化
return pa; //返回创建对象的指针
```


总结一下：关于关键词new，主要是要明白用它在堆上创建数组或对象时，它会返回创建的数组或对象的指针，返回创建的数组或对象的指针，返回创建的数组或对象的指针！重要的事情说三遍！