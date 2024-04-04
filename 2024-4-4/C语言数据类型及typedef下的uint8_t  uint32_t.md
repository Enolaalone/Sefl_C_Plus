# C语言数据类型及typedef下的uint8_t / uint32_t





------

## 前言

在基于C语言的代码中总能看到uint8_t / uint16_t / uint32_t /uint64_t的身影。如：uint32_t a = 300;
但它似乎又不属于C语言中的6种基本数据类型（short、int、long、char、float、double），那么它是一种新的数据类型？

本文以这个问题为切入点，回顾了C语言中的6种基本数据类型；描述了数据类型在不同编译器、平台存在的字长差异；进而引出了uint8_t / uint16_t / uint32_t /uint64_t的来源和作用；最后介绍了typedef的用法及与define的区别。

------

## 一、C语言基本数据类型

C语言共有6种基本数据类型，分别是：

1）整型：short、int、long；

2）浮点型：float、double；

3）字符类型：char。

## 二、数据类型在不同编译器下存在的字长差异

C语言的6种基本数据类型中，int类型（整型-short、int、long）比较特殊，其具体的字节数同机器字长和编译器有关。下面对比数据类型在16位、32位、64位编译器下的字节长度，用sizeof( )函数得出。

*注：
① 这里的编译器位数指的是编译生成的软件（应用程序）的位数；
② char型从本质上说，也是种整型类型，它是长度为1的整数，通常用来存放字符的ASCII码。*

**16位编译器：**

```c
char 			// 1个字节
char*           // 2个字节(*指针变量) 
                // 16位的寻址空间是2^16, 即16个bit，即2字节。(32位、64位编译器同理)
                
short int       // 2个字节
int             // 2个字节
unsigned int    // 2个字节 无符号整型

float           // 4个字节
double          // 8个字节

long            // 4个字节
long long       // 8个字节
unsigned long   // 4个字节
```

**32位编译器：**

```c
char           // 1个字节
char*          // 4个字节(*指针变量)(16&32&64位机各不相同)

short int      // 2个字节
int            // 4个字节(16位-2B,32&64位-4B(Byte))
unsigned int   // 4个字节(16位-2B,32&64位-4B)

float          // 4个字节
double         // 8个字节

long           // 4个字节(16&32位-4B,64位-8B)
long long      // 8个字节
unsigned long  // 4个字节(16&32位-4B,64位-8B)
```

**64位编译器：**

```c
char            // 1个字节
char*           // 8个字节

short int       // 2个字节
int             // 4个字节
unsigned int    // 4个字节

float           // 4个字节
double          // 8个字节

long            // 8个字节
long long       // 8个字节
unsigned long   // 8个字节
```

如上所示，**int，long int，short int的数据位宽与编译器有关**。但存在以下原则（ANSI/ISO制订），即
**1） sizeof(short int) <= sizeof(int) ；
2） sizeof(int) <= sizeof(long int) ；
3） short int至少应为16位(2字节) ；
4） long int至少应为32位。**

## 三、uint8_t / uint16_t / uint32_t /uint64_t的来源和作用

**1、来源**
*_t表示该标识由typedef定义得到，是结构的一种标注。C语言代码中的uint8_t / uint16_t / uint32_t /uint64_t**都不是新的数据类型**，而是通过typedef给数据类型起得新名字，如：

```c
typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
```

**2、作用**
**1）增加代码的可读性**
uint8_t,uint32_t能更明显的显示所占字节数。
uint8_t表示占1个字节(1 字节=8 bit)；
uint32_t表示占4个字节(4 字节=32 bit)。

**2）增加代码的可维护性**
在涉及到跨平台时，不同的平台会有不同的字长，所以利用预编译和typedef可以方便的维护代码。

*注：uint8_t实际上就是一个char，所以输出 uint8_t类型的变量实际上输出对应的字符，而不是数值，如：*

```c
uint8_t  num=67;
cout << num << endl;		//输出结果为C
```

