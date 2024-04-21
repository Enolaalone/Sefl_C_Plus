using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    public partial class MinesField : UserControl//用户自定义
    {
/*        /// <summary>
        /// 踩雷失败或者成功扫雷
        /// </summary>

        public delegate void MineSweepSuccessEventHandler(object sender, EventArgs e);
        public event MineSweepSuccessEventHandler MineSweepSuccess;
        public delegate void MineSweepFailedEventHandler(object sender, EventArgs e);
        public event MineSweepFailedEventHandler MineSweepFailed;*/


        public int PaneNum { get; set; }
        public int PaneLineNum { get; set; }
        public int Num { get; set; }

        public event EventHandler End;//结束
        public event EventHandler Win;//结束

        protected virtual void GameEnd()
        {
            End?.Invoke(this, EventArgs.Empty);//通知订阅者
        }

        protected virtual void GameWin()
        {
            Win?.Invoke(this, EventArgs.Empty);//通知订阅者
        }

        public MinesField()
        {
            InitializeComponent();

          
        }
        /// <summary>
        /// 放置地雷
        /// </summary>
        /// <param name="PaneLineNum">边长方格数</param>
        /// <param name="MineNum">地雷数目</param>
        public void Init(int PaneLineNum,int MineNum) 
        {
            //添加地雷
            this.PaneNum = MineNum;
            this.PaneLineNum = PaneLineNum;
            for (int i = 0; i < PaneLineNum*PaneLineNum; i++) { 
                Pane pane = new Pane();
                pane.MouseDown += new MouseEventHandler(Pane_MouseDown);//绑定鼠标按下事件,参数一致(object sender ,MouseDown)
                pane.Closed();
                this.Controls.Add(pane);
            
            }


            //放置方块

            this.LayOut();
            //随机布雷
            this.SetMines(MineNum);
            //获取周围雷数
            foreach (Pane pane in this.Controls)//遍历周围雷数
            {
                pane.AroundNumber = this.GetAroundNumber(pane);
              
            }
            //计数初始化
            this.Num = 0;

        }

        /// <summary>
        /// 显示所有地雷
        /// </summary>

        public void DisplayAllMine()
        {
            foreach (Pane pane in this.Controls) 
            {
                if (pane.State != States.Opened)//如果未被翻开
                {
                    pane.Opened();
                }

            }

        }

        /// <summary>
        /// 显示周围地雷,迭代
        /// </summary>
        public void DisplayAround(Pane pane)
        {
            Queue<Pane> queue = new Queue<Pane>();
            queue.Enqueue(pane);

            while (queue.Count > 0)
            {
                Pane currentPane = queue.Dequeue();
                
                if (currentPane.State != States.Closed) continue;

                currentPane.Opened();
                if (currentPane.IsMine) continue;
                //胜利！！
                this.Num++;
                if (Num == (PaneLineNum * PaneLineNum) - PaneNum)this.GameWin();
                
                if (currentPane.AroundNumber == 0)
                {
                    List<Pane> neighbors = this.AroundMine(currentPane);
                    foreach (Pane neighbor in neighbors)
                    {
                        if (neighbor.State == States.Closed && !neighbor.IsMine)
                        {
                            queue.Enqueue(neighbor);
                        }
                    }
                }
            }
        }


        /// <summary>
        /// 随机布置地雷
        /// </summary>
        /// <param name="num"></param>
        public void SetMines(int num)
        {
            Random rnd = new Random();

            for (int i = 0;i < num;i++)
            {
                int index=rnd.Next(0,this.Controls.Count);//生成随机数0----Count-1
                Pane pane = (Pane)this.Controls[index];
                pane.IsMine = true;//设置地雷



                pane.Marked();
            
            }
        }

        /// <summary>
        /// 按下鼠标事件
        /// </summary>
        public void Pane_MouseDown(object sender,MouseEventArgs e)
        {
            Pane pane= sender as Pane;
            if(e.Button == MouseButtons.Left)//左键
            {
                if (pane.State == States.Marked) pane.Closed();//关闭
                else if (pane.State == States.Closed)
                {

                    this.DisplayAround2(pane);

                    if (pane.IsMine) GameEnd();
                }

            }
            else if(e.Button == MouseButtons.Right) //右键
            {
                if(pane.State == States.Closed)pane.Marked();//标记
            }


     
        }

        /// <summary>
        /// 雷区重新布局
        /// </summary>

        public void LayOut()
        {
            if (this.Controls.Count == 0) return;//空间为0无需布局

            int paneLineNum = (int)Math.Sqrt(this.Controls.Count);//控件数量开平方
            int width=this.Width/paneLineNum;//宽
            int height=this.Height/paneLineNum;//高
            int index = 0;
            int Top=0;
            int Left=0;
            for(int col=0; col < paneLineNum; col++) 
            {
                Top = col * height; 
                for(int row=0; row < paneLineNum; row++) 
                {
                    Left = row * width;
                    //设置方格大小和位置
                    Pane pane = (Pane)this.Controls[index];

                    pane.Size=new Size(width, height);
                    pane.Location = new Point(Left, Top);
                    index++;
                }
            
            }

        }

        /// <summary>
        /// 根据窗口大小调整雷区，添加到public MinesField()方法中
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void ResetMinesField(object sender,EventArgs e)
        {
            this.LayOut();
        
        }

        /// <summary>
        /// 获取周围雷数
        /// </summary>
        /// <param name="pane">当前地雷</param>
        public int GetAroundNumber(Pane pane)
        {
            List<Pane> list = AroundMine(pane);
            int MinesNum=0;
            foreach (Pane mine in list)
            {
                if (mine.IsMine) MinesNum++;

            }

            return MinesNum ;
        
        }

        /// <summary>
        /// 查找周围的雷
        /// </summary>
        /// <param name="pane">当前方格</param>
        /// <returns></returns>

        public List<Pane> AroundMine(Pane pane)
        { 
            List<Pane> list = new List<Pane>();

            foreach (Pane mine in this.Controls)
            {
                //使用距离查询周围雷数
                if (mine.Top == pane.Top && Math.Abs(mine.Left - pane.Left) == pane.Width
                    || mine.Left == pane.Left && Math.Abs(mine.Top - pane.Top) == pane.Height
                    || Math.Abs(mine.Top - pane.Top) == pane.Height && Math.Abs(mine.Left - pane.Left) == pane.Width
                   )
                { 
                  
                    list.Add(mine);
                
                }
            }

            return list;
        }

        /// <summary>
        /// 重新开始游戏
        /// </summary>
        public void ResetMines() 
        {
            foreach(Control control in this.Controls.Cast<Control>().ToArray())
            {
                this.Controls.Remove(control);
                control.Dispose();//销毁

            }

            this.Init(10, this.PaneNum);
        }


        /// <summary>
        /// 重新开始游戏2
        /// </summary>

        public void ResetMines2()
        {
            //添加地雷

            foreach (Pane pane in this.Controls)
            {

                pane.IsMine = false;
                pane.AroundNumber = 0;
                pane.Closed();
                pane.MouseDown += new MouseEventHandler(Pane_MouseDown);


            }


            //放置方块

            this.LayOut();
            //随机布雷
            this.SetMines(this.PaneNum);
            //获取周围雷数
            foreach (Pane pane in this.Controls)//遍历周围雷数
            {
                pane.AroundNumber = this.GetAroundNumber(pane);

            }
            //计数初始化
            this.Num = 0;
        }



        /// <summary>
        /// 消除按键事件绑定
        /// </summary>
        public void Release()
        { 
            foreach(Pane pane in this.Controls)
            {

                pane.MouseDown -= Pane_MouseDown;
            }
        
        }
        /// <summary>
        /// 递归扫雷2
        /// </summary>
        /// <param name="pane"></param>
        public void DisplayAround2(Pane pane)
        {
            if (pane.State != States.Closed) return;
            else if (pane.AroundNumber > 0 && pane.State == States.Closed)
            {
                
                pane.Opened();
                this.Num++;
                if (Num == (PaneLineNum * PaneLineNum) - PaneNum) this.GameWin();
                return;
            }

            pane.Opened();

            if (pane.IsMine) return;
            this.Num++;
            if (Num == (PaneLineNum * PaneLineNum) - PaneNum) this.GameWin();
            List<Pane> list = this.AroundMine(pane);

            foreach (Pane mine in list)
            {
                DisplayAround2(mine);
            }
        }
    }
}
