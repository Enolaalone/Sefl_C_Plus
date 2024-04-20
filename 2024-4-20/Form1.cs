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

        }

        /// <summary>
        /// 雷区生成
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void Form1_Load(object sender,EventArgs e)
        {
            this.minesField1.Init(10,10);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.minesField1.DisplayAllMine();
        }
    }
}
