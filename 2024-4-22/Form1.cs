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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
         
            //this.Load += new System.EventHandler(this.Form1_Load);
            this.Load += Form1_Load;
            setting1.RequestReset += ResetMines;
            minesField1.End += End;
            minesField1.Win += Win;
            minesField1.Begin += Begin;
            minesField1.FlagChange1 += FlagChange1;
            minesField1.FlagChange0 += FlagChange0;

        }



        /// <summary>
        /// 面板初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void Form1_Load(object sender,EventArgs e)
        {
            this.minesField1.Init(10,10);


            this.setting1.SetButtonInit0();//设置脸
            this.setting1.SetButtonInit1();//设置底座
            this.setting1.ButtonAdd();//合并
            this.setting1.TimeRecord();//时间
            this.setting1.FlagSet();//旗子




        }

        public void ResetMines(object sender,EventArgs e) 
        {
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


    }
}
