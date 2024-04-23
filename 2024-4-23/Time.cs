using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Drawing;//Size
using System.Windows.Forms;
using System.Resources;

namespace Minesweeper
{

    public class Time:PictureBox
    {
        /// <summary>
        /// 当下时间
        /// </summary>

        public System.Timers.Timer timer = new System.Timers.Timer(1000);

        public PictureBox pictureBox1 = new PictureBox();
        public PictureBox pictureBox2 = new PictureBox();
        public PictureBox pictureBox3 = new PictureBox();

        public ResourceManager rm = Properties.Resources.ResourceManager;//照片流

        public int time { get; set; } = 0;//记录时间
        public bool Start {  get; set; }=false;


        public Time()
        {
            this.Size = new Size(0, 0);
        }
        public void ShowTime (object sender,EventArgs e)
        {
           timer.Stop();
            int G, S, B;
            G=time%10;
            S=time/10%10;
            B=time/100;


            pictureBox1.Image = (Image)rm.GetObject($"download0{G}");
            pictureBox2.Image = (Image)rm.GetObject($"download0{S}");
            pictureBox3.Image = (Image)rm.GetObject($"download0{B}");

            if(Start)time++;
            timer.Start();
        }


        public void ReSetTime() 
        {
            time = 0;
            this.ShowTime(this.timer, EventArgs.Empty);//快速显示
            this.Start = false;
        }
        public void Time0()
        {
            timer.Start();
            this.Start = true;
            this.ShowTime(this.timer, EventArgs.Empty);//快速显示
        }

        public void Time1()
        { 
            timer.Stop();
            this.Start = false;
        }




        public void PictureTimeSet(int x,int y)
        {
            int width=15,height=32;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;  // 设置图像显示模式
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;  
            pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;  
            
            pictureBox1.Size = new Size(width, height);
            pictureBox1.Location = new Point(x+2*width, y);
            pictureBox2.Size = new Size(width, height);
            pictureBox2.Location = new Point(x+ width, y);
            pictureBox3.Size = new Size(width, height);
            pictureBox3.Location = new Point(x , y);

            timer.AutoReset = true;//计时器归零
            //timer.Start();
            this.ShowTime(this.timer, EventArgs.Empty);//直接显示不必等待
            timer.Elapsed += ShowTime;//绑定事件
             
        }


    }
}
