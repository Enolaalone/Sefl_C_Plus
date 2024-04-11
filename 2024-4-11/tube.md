# 共阳极数码管

## 四位共阳极数码管

### 引脚图

![img](https://img-blog.csdnimg.cn/direct/668e3f2993ad4dd0bca012ae376b3e87.png)

![img](https://img-blog.csdnimg.cn/direct/e38f3ecebf344e418e4fc80866c6759b.png)



### 官方图

![image-20240402155439119](assets/image-20240402155439119.png)



## HC573-引脚图--YC7

![image-20240402155651960](assets/image-20240402155651960.png)



主要采用灌电流 ；外部供电；

- 内部输出高电平 灯熄灭；
- 内部输出低电平 灯亮起；

## HC573-共阳极--YC6

![image-20240402155917092](assets/image-20240402155917092.png)

- 共阳角com1-8对应了数码管从左到右；
- 共阳极为供电级，输出高电平供电，

### 控制：使用`unsigned char`

**char** vs **unsigned char**
相同点：在内存中都是一个字节，8位（2^8=256），都能表示256个数字
不同点：char的最高位为符号位，因此char能表示的数据范围是-128~127，unsigned char没有符号位，因此能表示的数据范围是0~255

## 动态显示：



![image-20240411161859158](assets/image-20240411161859158.png)