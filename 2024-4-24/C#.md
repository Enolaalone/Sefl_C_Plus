# C#

## 语法

### 变量：

![image-20240418152053036](assets/image-20240418152053036.png)

### 存储单位

![image-20240418152343104](assets/image-20240418152343104.png)

![image-20240418152632353](assets/image-20240418152632353.png)

![屏幕截图 2024-04-18 152737](assets/屏幕截图 2024-04-18 152737.png)

### 计算

![屏幕截图 2024-04-18 152920](assets/屏幕截图 2024-04-18 152920.png)

### 格式化：$"abc={n}"

![屏幕截图 2024-04-18 153111](assets/屏幕截图 2024-04-18 153111.png)

## winform

### 设计界面：

添加界面元素；

![屏幕截图 2024-04-18 163758](assets/屏幕截图 2024-04-18 163758.png)

### designer.cs代码设计：

![image-20240418163901447](assets/image-20240418163901447.png)

### 内部代码MainForm.cs：

![image-20240418164203689](assets/image-20240418164203689.png)

### 



## 界面设计：

### 工具箱拖动设计

![屏幕截图 2024-04-18 164241](assets/屏幕截图 2024-04-18 164241.png)



### 右键属性：

![image-20240424123744180](assets/image-20240424123744180.png)

Text进行Form名称修改；

BacKColor进行背景颜色修改

FromBorderstyle禁止窗口缩放；

MinSizeBox,MaxSizeBox关闭防止缩放；



## 基本操作：

### 类的创建：

直接创建,直接选中类 或者 用户控件

![image-20240424125204362](assets/image-20240424125204362.png)

#### 模板：

```c#
namespace Minesweeper：Button
{
    public class Pane
    {
        //属性
        public int Id { get; set; }

        //方法

        public void Def()
        { 
        }
    }
}
```

一个类只能继承于一个类（Button）

### 控件的创建与使用：

#### 创建：

- 直接从（.cs）设计中拖动添加到Form窗口；

```c#
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {this.难度});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(480, 32);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
```

FormDesigner.cs中会自动添加代码，生成参数；

- 代码动态生成；

```c#

for (int i = 0; i < PaneLineNum*PaneLineNum; i++) { //添加100个雷到雷区
    Pane pane = new Pane();
    this.Controls.Add(pane);

}
```

创建一个新的对象Pane;

将其添加到对应窗口类的控件（Controls）中；



#### 使用：



##### 特殊控件;较少的单独的控件

> 建议:特殊控件取名，方便查找使用；

```c#
pane.Name = "地雷";
this.Controls.Add(pane);
```

```c#
Pane pane = (Pane)this.Controls["地雷"];
Pane pane = this.Controls["地雷"] as Pane;//与以上代码等价
```

##### 批量控件的遍历查找：

```
foreach (Pane pane in this.Controls)//遍历周围雷数
{
    pane.AroundNumber = this.GetAroundNumber(pane);

}
```

#### 控件的属性：

可直接根据属性面板 用 `对象.属性（）=`设置；

![image-20240424131907538](assets/image-20240424131907538.png)

常用设置：

- .Size =new Size(width,height)
- .Location = new Point(Left,Top)

### 事件绑定：

#### 绑定：

Eg:

```c#
 pane.MouseDown += new MouseEventHandler(Pane_MouseDown);

public void Pane_MouseDown(object sender,MouseEventArgs e)
{
}
```

模板事件如:(鼠标点击)Click可以直接用+=连接到对应事件EventHandler处理函数

事件处理函数包括两个固定参数：(Object对象 ; EventArgs事件参数)

例如：例子中雷检测到鼠标按下，触发事件Pane_MouseDown();

#### 解绑：

```c#
pane.MouseDown -= Pane_MouseDown;
```

(鼠标点击)Click可以直接-=取消连接到对应事件EventHandler处理函数

没有事件绑定解绑多次使用没有影响；



### 枚举 状态：

本质上是一个数组，以不同的名称命名0，1，2；

使用时候变量为对应枚举名称类型；

```c#
public States State { get; set; }
public enum States//枚举
{
    Closed,
    Opened,
    Marked,
}
```



### 动态资源库加载：方便查找

- `ResourceManager`: 这是一个用于访问应用程序资源的类。
- 在这里，`Properties.Resources.ResourceManager`表示正在使用的资源管理器，通常是在项目中的 Properties 文件夹下的 Resources.resx 中定义的资源管理器。
- `(Image)rm.GetObject($"_{this.AroundNumber}")`: 这部分是从资源管理器中获取图像的过程。`GetObject` 方法用于检索具有指定名称的资源对象,并转化为指定类型（Image）。
- $" {变量名称 } "类似于Python的format格式

```c#
ResourceManager rm = Properties.Resources.ResourceManager;
this.BackgroundImage=(Image)rm.GetObject($"_{this.AroundNumber}");
```



### Button背景:

```c#
button1.BackgroundImage = Properties.Resources.MyImage; // 设置按钮的背景图像为项目资源中的一个图像
```

```c#
button1.BackColor = Color.Red; // 设置按钮的背景颜色为红色
```

### 类之间的消息传递：

#### 不含参数：

官方自带EventHandler

```c#
public delegate void EventHandler(object sender, EventArgs e);
```

##### eg：

事件发布者中定义类；

```c#
public class Publisher
{
    // 定义一个事件，使用标准的EventHandler
    public event EventHandler StandardEvent;

    // 方法来触发事件
    public void RaiseEvent()
    {
        // 触发事件
        StandardEvent?.Invoke(this, EventArgs.Empty);
    }
}
```

事件接受者中订阅事件；

```c#
public class Subscriber
{
    public void Subscribe(Publisher pub)//事件发布者对象
    {
        pub.StandardEvent += OnStandardEvent;
    }
	//事件处理函数
    private void OnStandardEvent(object sender, EventArgs e)
    {
        Console.WriteLine("Standard Event was raised.");
    }
}
```





## 雷块（继承于Button）

### 属性：

- 是否是地雷；
- 周围雷数目；
- 当前方格状态；

### 方法：

- 打开状态；
- 关闭状态；
- 标记状态；



### 代码实现：

```c#
namespace Minesweeper
{
    /// <summary>
    /// 雷类，方格
    /// </summary>
    public class Pane:Button//继承于按键
    {
        /// <summary>
        /// 构造方法
        /// </summary>
       public Pane() //按键方法
        {

            this.BackgroundImageLayout=ImageLayout.Stretch;//拉伸
            this.FlatStyle = FlatStyle.Flat;
            this.FlatAppearance.BorderSize = 0;//无边界
            this.FlatAppearance.BorderColor = Color.White;//无色
        }

        /// <summary>
        /// 获取或设置地雷
        /// </summary>
        public bool IsMine { get; set; }
       
        /// <summary>
        /// 获取当前方格周围地雷数目，雷除外
        /// </summary>
        public int AroundNumber {  get; set; }
        /// <summary>
        /// 获取或设置方格状态（枚举）
        /// </summary>
        public States State { get; set; }
        /// <summary>
        /// 打开状态
        /// </summary>
        public void Opened() 
        {
            if (this.IsMine)
                this.BackgroundImage = Properties.Resources.red_boom;
            else if (this.AroundNumber == 0)
                this.BackgroundImage = Properties.Resources.under1;
            else 
            {
                //动态资源排序
                //ResourceManager 类提供了一种动态获取资源的方法，它允许你根据资源的名称来动态获取资源对象
                ResourceManager rm = Properties.Resources.ResourceManager;
                this.BackgroundImage=(Image)rm.GetObject($"_{this.AroundNumber}");
            }
            this.State = States.Opened;
        }
        public void Closed() 
        {
            this.BackgroundImage = Properties.Resources.under0;
            this.State = States.Closed;
        }
        public void Marked() 
        {
            this.BackgroundImage = Properties.Resources.flag;
            this.State = States.Marked;
        }
    }

    public enum States//枚举
    {
        Closed,
        Opened,
        Marked,
    }
}
```



