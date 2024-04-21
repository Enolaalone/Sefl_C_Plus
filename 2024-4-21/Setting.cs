using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    public partial class Setting : UserControl
    {

        public event EventHandler RequestReset;
        public Setting()
        {
            InitializeComponent();
        }


        public void SetButtonInit0() 
        {
            SetButton setButton = new SetButton();
            setButton.Name = "setButton";
            setButton.State=GameStates.Process;
            setButton.MouseClick += new MouseEventHandler(ResetGame);
            setButton.MouseDown += new MouseEventHandler(Under);
            setButton.MouseUp += new MouseEventHandler(Up);
            this.Controls.Add(setButton);

        }

        public void SetButtonInit1()
        {

            SetButton setButton = new SetButton();
            setButton.Name = "setButtonUnder";
            setButton.State = GameStates.none;
            setButton.Down = false;
            this.Controls.Add(setButton);

        }


        /// <summary>
        /// 重启游戏
        /// </summary>
        /// <param name="ender"></param>
        /// <param name="e"></param>
        public void ResetGame(object ender,EventArgs e) 
        {
            RequestReset?.Invoke(this, EventArgs.Empty);
        }



        public void LayButton() 
        
        {
            SetButton setButton = (SetButton)Controls["setButtonUnder"];//找Button
            int b_width, b_top, b_left;

            b_width = (10 * this.Height) / 11;
            b_left = (this.Width - b_width) / 2;
            b_top = this.Height / 55;
            setButton.Size = new Size(b_width, b_width);
            setButton.Location = new Point(b_left, b_top);
            ButtonCheck(setButton);
        }

        public void LayButton2()

        {
            SetButton setButton = (SetButton)Controls["setButton"];//找Button
            int b_width, b_top, b_left;

            b_width = (7 * this.Height) / 11;
            b_left = b_width/20 + (this.Width - b_width) / 2;
            b_top = 2*b_width/11 + this.Height / 55;
            setButton.Size = new Size(b_width, b_width);
            setButton.Location = new Point(b_left, b_top);

            ButtonCheck(setButton);
        }

        public void ButtonCheck(SetButton setButton)
        {
            if (setButton.State == GameStates.Process) setButton.Process();
            else if (setButton.State == GameStates.Win) setButton.Win();
            else if (setButton.State == GameStates.Lost) setButton.Lost();
            else if (setButton.State == GameStates.none) setButton.SetUpDown();

        }

        public void ButtonAdd() 
        {
            this.LayButton();
            this.LayButton2();
        
        }




        public void Under(object sender, EventArgs e) 
        {
            SetButton setButton = (SetButton)Controls["setButtonUnder"];//找Button
            setButton.Down = true;
            setButton.SetUpDown();

        }
        public void Up(object sender, EventArgs e)
        {
            SetButton setButton = (SetButton)Controls["setButtonUnder"];//找Button
            setButton.Down = false;
            setButton.SetUpDown();

        }


        public void GameOver()
        {
            SetButton setButton = (SetButton)Controls["setButton"];//找Button
            setButton.Lost();
        }

        public void ReGame()
        {
            SetButton setButton = (SetButton)Controls["setButton"];//找Button
            setButton.Process();
        }

        public void GameWin()
        {
            SetButton setButton = (SetButton)Controls["setButton"];//找Button
            setButton.Win();
        }
    }
}
