# Pytorch

## 概论

### 学习系统：

![image-20240520221757161](assets/image-20240520221757161.png)

>  Deep Learning 端到端



### 神经网络：





## Lecture1:线性模型

- DataSet;//数据集合
- Model;//模型
- Training;//训练
- inferring;//推理

### 问题：

![image-20240521165322667](assets/image-20240521165322667.png)

### 流程：

![image-20240521165615731](assets/image-20240521165615731.png)

### DataSet;//数据集合：

- 训练数据集合（包含输入和输出）；使模型有更强泛化能力；
  - 开发集合：类似测试集合，用于评估模型；
- 测试数据集合（只有输入）；



### Model;//模型：

> y = f(x);

- 线性模型：Linear Model：

![image-20240521170939071](assets/image-20240521170939071.png)

- 随机猜测（w = a random guess）；

- 求偏移程度；

​	![image-20240521171412308](assets/image-20240521171412308.png)

- 对样本评估`Evaluate`模型，求平均损失；

  ![image-20240521171552324](assets/image-20240521171552324.png)

- 平均平方误差MSE;

  ![image-20240521172110059](assets/image-20240521172110059.png)



Code

![image-20240521173550703](assets/image-20240521173550703.png)

Draw Graph

![image-20240521174836083](assets/image-20240521174836083.png)



## 梯度下降

### ![image-20240521231555609](assets/image-20240521231555609.png)

### 梯度：

![image-20240521231640632](assets/image-20240521231640632.png)

- 如果>0，函数上升；
- 如果<0，函数下降；

> 梯度负方向；



### 梯度更新：（贪心）

![image-20240521231839084](assets/image-20240521231839084.png)

> a学习率要尽量取小点0.01；



**非凸函数 全局最优**

![image-20240521232242603](assets/image-20240521232242603.png)



**鞍点** 

> 梯度为0;

![image-20240521232605275](assets/image-20240521232605275.png)



### 梯度计算：

![image-20240521232901782](assets/image-20240521232901782.png)



### 发散：

![image-20240522090513300](assets/image-20240522090513300.png)



### 随机梯度下降:

![image-20240522090755658](assets/image-20240522090755658.png)

- 单个数据的损失`(pre_y - y)**2`
- 对每个样本求梯度`2*x*(w*x - y)`

### Code；

![image-20240522090231480](assets/image-20240522090231480.png)





![image-20240522090949073](assets/image-20240522090949073.png)



## 反向传播 

![image-20240522212420013](assets/image-20240522212420013.png)

- 更新权重：![image-20240522212509925](assets/image-20240522212509925.png)



![image-20240522212528892](assets/image-20240522212528892.png)



### 反向传播：

#### 层：

![image-20240522213235840](assets/image-20240522213235840.png)

> X输入后x乘转置矩阵；
>
> 加上偏移量；



![image-20240522213526383](assets/image-20240522213526383.png)

> 对每一层加非线性函数；
>
> 必须分层计算；



### 链式求导：

![image-20240522213703519](assets/image-20240522213703519.png)

> 链式法则;

#### 过程：



![image-20240522214115853](assets/image-20240522214115853.png)

> 先前馈后反馈；

![image-20240522215506716](assets/image-20240522215506716.png)

> 为了求梯度：
> $$
> \dfrac{\partial loss}{\partial \omega}
> $$
> 转化为：
> $$
> \dfrac{\partial loss}{\partial r}
> \times
> \dfrac{\partial r}{\partial \widehat{y}}
> \times
> \dfrac{\partial \widehat{y}}{\partial \omega}
> $$
> 反向求梯度；



### Tensor:建立计算图

- Data;

- $$
  \dfrac{\partial loss}{\partial \omega}
  $$

  

#### 设定需要梯度计算：

![image-20240522221627839](assets/image-20240522221627839.png)

> 默认Tensor不计算梯度；



![image-20240522222116814](assets/image-20240522222116814.png)

> `x`需要转为`Tensor`；
>
> 结果也需要梯度



![image-20240522222308586](assets/image-20240522222308586.png)

> .backward();求链上梯度；
>
> 取梯度的Data进行数据计算（标量）；//grad计算会生成计算图；
>
> .item()取值计算；
>
> .grad.data.zero()清零运算；//每次都要



### 总结：

![image-20240522223240259](assets/image-20240522223240259.png)
