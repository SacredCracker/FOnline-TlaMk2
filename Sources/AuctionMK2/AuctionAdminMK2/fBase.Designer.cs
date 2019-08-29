namespace AuctionAdminMK2
{
    partial class fBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.администрированиеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.настройкиToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.выходToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.базаДанныхToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.ProgressBar = new System.Windows.Forms.ToolStripProgressBar();
			this.StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
			this.прототипыПредметовToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.miTypes = new System.Windows.Forms.ToolStripMenuItem();
			this.miLots = new System.Windows.Forms.ToolStripMenuItem();
			this.miPlayers = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.администрированиеToolStripMenuItem,
            this.базаДанныхToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(675, 24);
			this.menuStrip1.TabIndex = 1;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// администрированиеToolStripMenuItem
			// 
			this.администрированиеToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.настройкиToolStripMenuItem,
            this.exportToolStripMenuItem,
            this.toolStripMenuItem1,
            this.выходToolStripMenuItem});
			this.администрированиеToolStripMenuItem.Name = "администрированиеToolStripMenuItem";
			this.администрированиеToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
			this.администрированиеToolStripMenuItem.Text = "Сервис";
			// 
			// настройкиToolStripMenuItem
			// 
			this.настройкиToolStripMenuItem.Name = "настройкиToolStripMenuItem";
			this.настройкиToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.настройкиToolStripMenuItem.Text = "Настройки ...";
			this.настройкиToolStripMenuItem.Click += new System.EventHandler(this.настройкиToolStripMenuItem_Click);
			// 
			// exportToolStripMenuItem
			// 
			this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
			this.exportToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.exportToolStripMenuItem.Text = "Экспорт прототипов";
			this.exportToolStripMenuItem.Click += new System.EventHandler(this.exportToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(176, 6);
			// 
			// выходToolStripMenuItem
			// 
			this.выходToolStripMenuItem.Name = "выходToolStripMenuItem";
			this.выходToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.выходToolStripMenuItem.Text = "Выход";
			this.выходToolStripMenuItem.Click += new System.EventHandler(this.выходToolStripMenuItem_Click);
			// 
			// базаДанныхToolStripMenuItem
			// 
			this.базаДанныхToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.прототипыПредметовToolStripMenuItem,
            this.miTypes,
            this.miLots,
            this.miPlayers});
			this.базаДанныхToolStripMenuItem.Name = "базаДанныхToolStripMenuItem";
			this.базаДанныхToolStripMenuItem.Size = new System.Drawing.Size(85, 20);
			this.базаДанныхToolStripMenuItem.Text = "База Данных";
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ProgressBar,
            this.StatusLabel});
			this.statusStrip1.Location = new System.Drawing.Point(0, 524);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(675, 22);
			this.statusStrip1.TabIndex = 3;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// ProgressBar
			// 
			this.ProgressBar.Name = "ProgressBar";
			this.ProgressBar.Size = new System.Drawing.Size(100, 16);
			this.ProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
			// 
			// StatusLabel
			// 
			this.StatusLabel.AutoSize = false;
			this.StatusLabel.Name = "StatusLabel";
			this.StatusLabel.Size = new System.Drawing.Size(240, 17);
			this.StatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// прототипыПредметовToolStripMenuItem
			// 
			this.прототипыПредметовToolStripMenuItem.Name = "прототипыПредметовToolStripMenuItem";
			this.прототипыПредметовToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
			this.прототипыПредметовToolStripMenuItem.Text = "Прототипы предметов";
			this.прототипыПредметовToolStripMenuItem.Click += new System.EventHandler(this.прототипыПредметовToolStripMenuItem_Click);
			// 
			// miTypes
			// 
			this.miTypes.Name = "miTypes";
			this.miTypes.Size = new System.Drawing.Size(189, 22);
			this.miTypes.Text = "Типы предметов";
			this.miTypes.Click += new System.EventHandler(this.miTypes_Click);
			// 
			// miLots
			// 
			this.miLots.Name = "miLots";
			this.miLots.Size = new System.Drawing.Size(189, 22);
			this.miLots.Text = "ЛОТЫ АУКЦИОНА";
			this.miLots.Click += new System.EventHandler(this.miLots_Click);
			// 
			// miPlayers
			// 
			this.miPlayers.Name = "miPlayers";
			this.miPlayers.Size = new System.Drawing.Size(189, 22);
			this.miPlayers.Text = "Игроки";
			this.miPlayers.Click += new System.EventHandler(this.miPlayers_Click);
			// 
			// fBase
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(675, 546);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.statusStrip1);
			this.IsMdiContainer = true;
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "fBase";
			this.Text = "БД Админ МК2";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem администрированиеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem настройкиToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        public System.Windows.Forms.StatusStrip statusStrip1;
        public System.Windows.Forms.ToolStripProgressBar ProgressBar;
        public System.Windows.Forms.ToolStripStatusLabel StatusLabel;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem выходToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem базаДанныхToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem прототипыПредметовToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem miTypes;
		private System.Windows.Forms.ToolStripMenuItem miLots;
		private System.Windows.Forms.ToolStripMenuItem miPlayers;
    }
}