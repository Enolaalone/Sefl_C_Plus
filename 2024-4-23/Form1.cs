using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //游戏等级设置
            this.初级ToolStripMenuItem.Click += new EventHandler(LToolClick);
            this.中级ToolStripMenuItem.Click += new EventHandler(MToolClick);
            this.高级ToolStripMenuItem.Click += new EventHandler(HToolClick);

            //事件绑定
            //this.Load += Form1_Load;
            this.setting1.RequestReset += ResetMines;
            this.setting1.NoFlag += NoFlag;
            this.minesField1.End += End;
            this.minesField1.Win += Win;
            this.minesField1.Begin += Begin;
            this.minesField1.FlagChange1 += FlagChange1;
            this.minesField1.FlagChange0 += FlagChange0;

            //==============

            this.Resize += new EventHandler(SizeChange);//字适应

        }

        public void SizeChange(object sender,EventArgs e)
        {
            this.MainMenuStrip.Size = new Size(this.Size.Width,10);

            this.setting1.Size = new Size(this.Size.Width - 30,38);
            this.setting1.Location = new Point(-7+(this.Size.Width-this.setting1.Width)/2,30);

            this.minesField1.Size = new Size(this.Size.Width - 30, this.Size.Width - 30);
            this.minesField1.Location = new Point(-7 + (this.Size.Width - this.setting1.Width) / 2, 85);



        }
        public void HToolClick(object ender, EventArgs e)
        {
            this.minesField1.ResetMines();
            this.setting1.Reset();
            ReSize(3);
            Form1_Load(24, 200, 200);


        }
        public void MToolClick(object ender, EventArgs e)
        {
            this.minesField1.ResetMines();
            this.setting1.Reset();

            ReSize(2);
            Form1_Load(16, 60, 60);

        }
        public void LToolClick(object ender, EventArgs e)
        {
            this.minesField1.ResetMines();
            this.setting1.Reset();
            ReSize(1);

            Form1_Load(9, 10, 10);

        }

        /// <summary>
        /// 面板初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void Form1_Load(int PaneLine, int PaneNum, int Flag)
        {

            this.minesField1.Init(PaneLine, PaneNum);

            this.setting1.SetButtonInit0();//设置脸
            this.setting1.SetButtonInit1();//设置底座
            this.setting1.ButtonAdd();//合并
            this.setting1.TimeRecord();//时间
            this.setting1.FlagSet(Flag);//旗子

        }
        public void ReSize(int n)
        {
            //this.MaximizeBox = true;
            //this.MinimizeBox = true;

            this.setting1.Size = this.setting1.Size;
            if (n==1)
            this.Size = new Size(336, 440);
            else if(n==2)
            this.Size = new Size(600, 700);

            else if(n==3)
            this.Size = new Size(900,1000);

            //this.MaximumSize = this.Size;
            //this.MinimumSize = this.Size;



        }


        public void ResetMines(object sender,EventArgs e) 
        {
            this.minesField1.Release();//事件解绑-----------------------------------------
            this.minesField1.ResetMines2();
            this.setting1.ReGame();
        }

        public void End(object sender, EventArgs e)
        {
            this.minesField1.Release();
            this.setting1.GameOver();
        }
        public void Win(object sender, EventArgs e)
        {
            this.minesField1.Release();
            this.setting1.GameWin();
        }
        public void Begin(object sender, EventArgs e)
        {
            this.setting1.TimeStart();
        }

        public void FlagChange1(object sender,EventArgs e)
        {

            this.setting1.FlagSetting1();
        }
        public void FlagChange0(object sender, EventArgs e)
        {

            this.setting1.FlagSetting0();
        }

        public void NoFlag(object sender, EventArgs e)
        {

            this.minesField1.FlagCheckWin();
        }


    }
}
