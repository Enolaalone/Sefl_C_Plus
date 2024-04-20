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
        /// <summary>
        /// 踩雷失败或者成功扫雷
        /// </summary>

        public delegate void MineSweepSuccessEventHandler(object sender, EventArgs e);
        public event MineSweepSuccessEventHandler MineSweepSuccess;
        public delegate void MineSweepFailedEventHandler(object sender, EventArgs e);
        public event MineSweepFailedEventHandler MineSweepFailed;

        public MinesField()
        {
            InitializeComponent();

            this.Resize += new EventHandler(ResetMinesField);//将ResetMinesField事件绑定到窗口大小改变的事件
        }
        /// <summary>
        /// 放置地雷
        /// </summary>
        /// <param name="PaneLineNum">边长方格数</param>
        /// <param name="MineNum">地雷数目</param>
        public void Init(int PaneLineNum,int MineNum) 
        {
            //添加地雷
            
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

        public void DisplayAround2(Pane pane)
        {
            if (pane.State != States.Closed) return;
            else if (pane.AroundNumber > 0 && pane.State == States.Closed)
            {
                pane.Opened();
                return;
            }

            pane.Opened();
            if (pane.IsMine) return;

            List<Pane> list = this.AroundMine(pane);

            foreach (Pane mine in list)
            {
                DisplayAround2(mine);
            }
        }
    }
}
