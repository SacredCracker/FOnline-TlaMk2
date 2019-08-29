namespace PidsRename
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonRun = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.textBoxPath = new System.Windows.Forms.TextBox();
            this.textBoxPathItemPid = new System.Windows.Forms.TextBox();
            this.textBoxPathItemName = new System.Windows.Forms.TextBox();
            this.textBoxPathText = new System.Windows.Forms.TextBox();
            this.textBoxPathProto = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.openFileDialogOpenNewNames = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.файлToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.видToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.сравнитьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.itemNameslstToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.itempidfosToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.russFoobjmsgToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.englFoobjmsgToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.allProtoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.allMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.currentMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialogMap = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonRun
            // 
            this.buttonRun.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonRun.Font = new System.Drawing.Font("Verdana", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonRun.ForeColor = System.Drawing.Color.Black;
            this.buttonRun.Location = new System.Drawing.Point(33, 36);
            this.buttonRun.Margin = new System.Windows.Forms.Padding(1);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(176, 43);
            this.buttonRun.TabIndex = 0;
            this.buttonRun.Text = "Переименовать все";
            this.buttonRun.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Enabled = false;
            this.checkBox1.Location = new System.Drawing.Point(6, 92);
            this.checkBox1.Margin = new System.Windows.Forms.Padding(1);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(15, 14);
            this.checkBox1.TabIndex = 2;
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // textBoxPath
            // 
            this.textBoxPath.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxPath.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxPath.Enabled = false;
            this.textBoxPath.Location = new System.Drawing.Point(23, 90);
            this.textBoxPath.Margin = new System.Windows.Forms.Padding(1);
            this.textBoxPath.Name = "textBoxPath";
            this.textBoxPath.Size = new System.Drawing.Size(380, 21);
            this.textBoxPath.TabIndex = 6;
            this.textBoxPath.Text = "Использовать файл конфигурации";
            // 
            // textBoxPathItemPid
            // 
            this.textBoxPathItemPid.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxPathItemPid.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxPathItemPid.Location = new System.Drawing.Point(6, 121);
            this.textBoxPathItemPid.Margin = new System.Windows.Forms.Padding(1);
            this.textBoxPathItemPid.Name = "textBoxPathItemPid";
            this.textBoxPathItemPid.Size = new System.Drawing.Size(407, 21);
            this.textBoxPathItemPid.TabIndex = 9;
            this.textBoxPathItemPid.Text = "Путь к _itempid.fos";
            // 
            // textBoxPathItemName
            // 
            this.textBoxPathItemName.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxPathItemName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxPathItemName.Location = new System.Drawing.Point(5, 153);
            this.textBoxPathItemName.Margin = new System.Windows.Forms.Padding(1);
            this.textBoxPathItemName.Name = "textBoxPathItemName";
            this.textBoxPathItemName.Size = new System.Drawing.Size(408, 21);
            this.textBoxPathItemName.TabIndex = 10;
            this.textBoxPathItemName.Text = "Путь к ItemNames.lst";
            // 
            // textBoxPathText
            // 
            this.textBoxPathText.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxPathText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxPathText.Location = new System.Drawing.Point(5, 185);
            this.textBoxPathText.Margin = new System.Windows.Forms.Padding(1);
            this.textBoxPathText.Name = "textBoxPathText";
            this.textBoxPathText.Size = new System.Drawing.Size(408, 21);
            this.textBoxPathText.TabIndex = 11;
            this.textBoxPathText.Text = "Путь к текстовикам";
            // 
            // textBoxPathProto
            // 
            this.textBoxPathProto.BackColor = System.Drawing.SystemColors.Info;
            this.textBoxPathProto.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxPathProto.Location = new System.Drawing.Point(5, 218);
            this.textBoxPathProto.Margin = new System.Windows.Forms.Padding(1);
            this.textBoxPathProto.Name = "textBoxPathProto";
            this.textBoxPathProto.Size = new System.Drawing.Size(408, 21);
            this.textBoxPathProto.TabIndex = 12;
            this.textBoxPathProto.Text = "Путь к прототипам";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Cursor = System.Windows.Forms.Cursors.Hand;
            this.label5.Font = new System.Drawing.Font("Courier New", 18.25F, ((System.Drawing.FontStyle)(((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic)
                            | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(204)), true);
            this.label5.ForeColor = System.Drawing.Color.DodgerBlue;
            this.label5.Location = new System.Drawing.Point(233, 49);
            this.label5.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(118, 30);
            this.label5.TabIndex = 13;
            this.label5.Text = "TLA mk2";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // openFileDialogOpenNewNames
            // 
            this.openFileDialogOpenNewNames.FileName = "_itempid.fos";
            this.openFileDialogOpenNewNames.Filter = "_itempid.fos|_itempid.fos";
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Location = new System.Drawing.Point(417, 31);
            this.button1.Margin = new System.Windows.Forms.Padding(1);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(36, 208);
            this.button1.TabIndex = 18;
            this.button1.Text = ">>";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_2);
            // 
            // button2
            // 
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Location = new System.Drawing.Point(417, 31);
            this.button2.Margin = new System.Windows.Forms.Padding(1);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(36, 391);
            this.button2.TabIndex = 19;
            this.button2.Text = "<<";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(8, 243);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(405, 214);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Диагностика";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label8.Cursor = System.Windows.Forms.Cursors.Default;
            this.label8.Location = new System.Drawing.Point(6, 164);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(178, 15);
            this.label8.TabIndex = 6;
            this.label8.Text = "Список редактируемых карт";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label7.Cursor = System.Windows.Forms.Cursors.Default;
            this.label7.Location = new System.Drawing.Point(6, 138);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(239, 15);
            this.label7.TabIndex = 5;
            this.label7.Text = "Новое содержимое файлов прототипов";
            this.label7.Click += new System.EventHandler(this.label7_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label6.Cursor = System.Windows.Forms.Cursors.Default;
            this.label6.Location = new System.Drawing.Point(6, 113);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(212, 15);
            this.label6.TabIndex = 4;
            this.label6.Text = "Новое содержимое engl Foobj.msg";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.Cursor = System.Windows.Forms.Cursors.Default;
            this.label4.Location = new System.Drawing.Point(6, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(212, 15);
            this.label4.TabIndex = 3;
            this.label4.Text = "Новое содержимое russ Foobj.msg";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.Cursor = System.Windows.Forms.Cursors.Default;
            this.label3.Location = new System.Drawing.Point(6, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(195, 15);
            this.label3.TabIndex = 2;
            this.label3.Text = "Новое содержимое _itempid.fos";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label2.Cursor = System.Windows.Forms.Cursors.Default;
            this.label2.Location = new System.Drawing.Point(6, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(212, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "Новое содержимое ItemNames.lst ";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.Cursor = System.Windows.Forms.Cursors.Default;
            this.label1.Location = new System.Drawing.Point(6, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(278, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Новый и старый списки именованых констант";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.SystemColors.Info;
            this.listBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.listBox1.Dock = System.Windows.Forms.DockStyle.Right;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(523, 24);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(526, 431);
            this.listBox1.TabIndex = 21;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.файлToolStripMenuItem,
            this.видToolStripMenuItem,
            this.сравнитьToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1049, 24);
            this.menuStrip1.TabIndex = 22;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // файлToolStripMenuItem
            // 
            this.файлToolStripMenuItem.Name = "файлToolStripMenuItem";
            this.файлToolStripMenuItem.Size = new System.Drawing.Size(45, 20);
            this.файлToolStripMenuItem.Text = "Файл";
            // 
            // видToolStripMenuItem
            // 
            this.видToolStripMenuItem.Name = "видToolStripMenuItem";
            this.видToolStripMenuItem.Size = new System.Drawing.Size(38, 20);
            this.видToolStripMenuItem.Text = "Вид";
            // 
            // сравнитьToolStripMenuItem
            // 
            this.сравнитьToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.itemNameslstToolStripMenuItem,
            this.itempidfosToolStripMenuItem,
            this.russFoobjmsgToolStripMenuItem,
            this.englFoobjmsgToolStripMenuItem,
            this.allProtoToolStripMenuItem,
            this.allMapToolStripMenuItem,
            this.currentMapToolStripMenuItem});
            this.сравнитьToolStripMenuItem.Name = "сравнитьToolStripMenuItem";
            this.сравнитьToolStripMenuItem.Size = new System.Drawing.Size(98, 20);
            this.сравнитьToolStripMenuItem.Text = "Переименовать";
            // 
            // itemNameslstToolStripMenuItem
            // 
            this.itemNameslstToolStripMenuItem.Name = "itemNameslstToolStripMenuItem";
            this.itemNameslstToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.itemNameslstToolStripMenuItem.Text = " ItemNames.lst ";
            this.itemNameslstToolStripMenuItem.Click += new System.EventHandler(this.itemNameslstToolStripMenuItem_Click);
            // 
            // itempidfosToolStripMenuItem
            // 
            this.itempidfosToolStripMenuItem.Name = "itempidfosToolStripMenuItem";
            this.itempidfosToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.itempidfosToolStripMenuItem.Text = "_itempid.fos";
            this.itempidfosToolStripMenuItem.Click += new System.EventHandler(this.itempidfosToolStripMenuItem_Click);
            // 
            // russFoobjmsgToolStripMenuItem
            // 
            this.russFoobjmsgToolStripMenuItem.Name = "russFoobjmsgToolStripMenuItem";
            this.russFoobjmsgToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.russFoobjmsgToolStripMenuItem.Text = "russ Foobj.msg";
            this.russFoobjmsgToolStripMenuItem.Click += new System.EventHandler(this.russFoobjmsgToolStripMenuItem_Click);
            // 
            // englFoobjmsgToolStripMenuItem
            // 
            this.englFoobjmsgToolStripMenuItem.Name = "englFoobjmsgToolStripMenuItem";
            this.englFoobjmsgToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.englFoobjmsgToolStripMenuItem.Text = "engl Foobj.msg";
            this.englFoobjmsgToolStripMenuItem.Click += new System.EventHandler(this.englFoobjmsgToolStripMenuItem_Click);
            // 
            // allProtoToolStripMenuItem
            // 
            this.allProtoToolStripMenuItem.Name = "allProtoToolStripMenuItem";
            this.allProtoToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.allProtoToolStripMenuItem.Text = "All Proto";
            this.allProtoToolStripMenuItem.Click += new System.EventHandler(this.allProtoToolStripMenuItem_Click);
            // 
            // allMapToolStripMenuItem
            // 
            this.allMapToolStripMenuItem.Name = "allMapToolStripMenuItem";
            this.allMapToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.allMapToolStripMenuItem.Text = "All Map";
            this.allMapToolStripMenuItem.Click += new System.EventHandler(this.allMapToolStripMenuItem_Click);
            // 
            // currentMapToolStripMenuItem
            // 
            this.currentMapToolStripMenuItem.Name = "currentMapToolStripMenuItem";
            this.currentMapToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.currentMapToolStripMenuItem.Text = "Current Map";
            this.currentMapToolStripMenuItem.Click += new System.EventHandler(this.currentMapToolStripMenuItem_Click);
            // 
            // openFileDialogMap
            // 
            this.openFileDialogMap.FileName = "*.fomap";
            this.openFileDialogMap.Filter = "*.fomap|*.fomap";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.NavajoWhite;
            this.ClientSize = new System.Drawing.Size(1049, 462);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxPathProto);
            this.Controls.Add(this.textBoxPathText);
            this.Controls.Add(this.textBoxPathItemName);
            this.Controls.Add(this.textBoxPathItemPid);
            this.Controls.Add(this.textBoxPath);
            this.Controls.Add(this.buttonRun);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(1);
            this.Name = "Form1";
            this.Text = "Pids ReName";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TextBox textBoxPath;
        private System.Windows.Forms.TextBox textBoxPathItemPid;
        private System.Windows.Forms.TextBox textBoxPathItemName;
        private System.Windows.Forms.TextBox textBoxPathText;
        private System.Windows.Forms.TextBox textBoxPathProto;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.OpenFileDialog openFileDialogOpenNewNames;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem файлToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialogMap;
        private System.Windows.Forms.ToolStripMenuItem видToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem сравнитьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem itemNameslstToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem itempidfosToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem russFoobjmsgToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem englFoobjmsgToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem allProtoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem allMapToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem currentMapToolStripMenuItem;
    }
}

