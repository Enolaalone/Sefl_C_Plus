namespace Minesweeper
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.setting1 = new Minesweeper.Setting();
            this.minesField1 = new Minesweeper.MinesField();
            this.SuspendLayout();
            // 
            // setting1
            // 
            this.setting1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.setting1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(204)))), ((int)(((byte)(204)))));
            this.setting1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.setting1.Location = new System.Drawing.Point(15, 10);
            this.setting1.Name = "setting1";
            this.setting1.Size = new System.Drawing.Size(450, 55);
            this.setting1.TabIndex = 2;
            // 
            // minesField1
            // 
            this.minesField1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.minesField1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.minesField1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.minesField1.Location = new System.Drawing.Point(15, 75);
            this.minesField1.Name = "minesField1";
            this.minesField1.Size = new System.Drawing.Size(450, 450);
            this.minesField1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(204)))), ((int)(((byte)(204)))));
            this.ClientSize = new System.Drawing.Size(480, 550);
            this.Controls.Add(this.setting1);
            this.Controls.Add(this.minesField1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;

        }

        #endregion

        private MinesField minesField1;
        private Setting setting1;
    }
}

