using Minesweeper.Properties;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
