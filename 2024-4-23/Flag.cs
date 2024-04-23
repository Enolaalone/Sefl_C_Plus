using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;//Size
using System.Windows.Forms;
using System.Resources;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace Minesweeper
{
    public class Flag:PictureBox
    {
        public PictureBox pictureBox4 = new PictureBox();
        public PictureBox pictureBox5 = new PictureBox();
        public PictureBox pictureBox6 = new PictureBox();

        public ResourceManager rm = Properties.Resources.ResourceManager;//照片流
        public int FlagNum { get; set; } //旗子个数
        public int FlagNum0 { get; set; } //旗子个数


        public Flag() 
        {
            this.Size = new Size(0, 0);        
        }
        /// <summary>
        /// 显示旗表初始化
        /// </summary>
        /// <param name="x">图表Left</param>
        /// <param name="y">图表Top</param>
        public void PictureFlagNumSet(int x, int y)
        {
            int width = 15, height = 32;
            pictureBox4.SizeMode = PictureBoxSizeMode.StretchImage;  // 设置图像显示模式
            pictureBox5.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox6.SizeMode = PictureBoxSizeMode.StretchImage;

            pictureBox4.Size = new Size(width, height);
            pictureBox4.Location = new Point(x + 2 * width, y);
            pictureBox5.Size = new Size(width, height);
            pictureBox5.Location = new Point(x + width, y);
            pictureBox6.Size = new Size(width, height);
            pictureBox6.Location = new Point(x, y);

            this.ShowFlag();

        }


        /// <summary>
        /// 显示图表
        /// </summary>
        public void ShowFlag()
        {
            int G=0, S=0, B = 0;
            G = FlagNum % 10;
            S = FlagNum / 10 % 10;
            B = FlagNum / 100;


            pictureBox4.Image = (Image)rm.GetObject($"download0{G}");
            pictureBox5.Image = (Image)rm.GetObject($"download0{S}");
            pictureBox6.Image = (Image)rm.GetObject($"download0{B}");

        }

        public void ReFlag(int t) 
        {
            this.FlagNum0 = this.FlagNum = t;
        
        }
        public void ReFlagNum ()
        {
            this.FlagNum = this.FlagNum0;
            this.ShowFlag();
        }


    }
}
