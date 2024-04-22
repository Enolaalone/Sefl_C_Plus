using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    public class SetButton:Button
    {
        public SetButton() 
        {
            this.BackgroundImageLayout = ImageLayout.Stretch;//拉伸
            this.FlatStyle = FlatStyle.Flat;
            this.FlatAppearance.BorderSize = 0;//无边界
            this.FlatAppearance.BorderColor = Color.White;//无色

        }

        public bool Down { get; set; }
        public GameStates State {  get; set; }//枚举


        public void Process()
        {
            this.BackgroundImage = Properties.Resources.smile1;
            this.State = GameStates.Process;
        
        }

        public void Win()
        {
            this.BackgroundImage = Properties.Resources.cool1;
            this.State = GameStates.Win;

        }


        public void Lost()
        {
            this.BackgroundImage = Properties.Resources.dead1;
            this.State = GameStates.Lost;

        }

        public void SetUpDown()
        {
            if (!this.Down) this.BackgroundImage = Properties.Resources.under0;

            else this.BackgroundImage = Properties.Resources.under1;
        }


    }


    public enum GameStates 
    {
        Win,
        Lost,
        Process,
        none,

    }
}
