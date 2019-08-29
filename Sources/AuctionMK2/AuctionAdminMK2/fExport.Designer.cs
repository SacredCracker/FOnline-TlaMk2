namespace AuctionAdminMK2
{
    partial class fExport
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
			this.components = new System.ComponentModel.Container();
			this.button1 = new System.Windows.Forms.Button();
			this.fd = new System.Windows.Forms.OpenFileDialog();
			this.panel1 = new System.Windows.Forms.Panel();
			this.button2 = new System.Windows.Forms.Button();
			this.panel2 = new System.Windows.Forms.Panel();
			this.dataGridView1 = new System.Windows.Forms.DataGridView();
			this.protoIdDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.protoNameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.protoDescriptionDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.aliasDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.typeDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.cm = new System.Windows.Forms.BindingSource(this.components);
			this.label1 = new System.Windows.Forms.Label();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.cm)).BeginInit();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(12, 12);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(87, 42);
			this.button1.TabIndex = 0;
			this.button1.Text = "Загрузить из файла";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// fd
			// 
			this.fd.DefaultExt = "fopro";
			this.fd.Filter = "Файлы прототипов предметов*.fopro|*.fopro";
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.label1);
			this.panel1.Controls.Add(this.button2);
			this.panel1.Controls.Add(this.button1);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(580, 63);
			this.panel1.TabIndex = 1;
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(122, 12);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(87, 42);
			this.button2.TabIndex = 1;
			this.button2.Text = "Сохранить в БД";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.dataGridView1);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel2.Location = new System.Drawing.Point(0, 63);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(580, 462);
			this.panel2.TabIndex = 2;
			// 
			// dataGridView1
			// 
			this.dataGridView1.AllowUserToAddRows = false;
			this.dataGridView1.AutoGenerateColumns = false;
			this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.protoIdDataGridViewTextBoxColumn,
            this.protoNameDataGridViewTextBoxColumn,
            this.protoDescriptionDataGridViewTextBoxColumn,
            this.aliasDataGridViewTextBoxColumn,
            this.typeDataGridViewTextBoxColumn});
			this.dataGridView1.DataSource = this.cm;
			this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dataGridView1.Location = new System.Drawing.Point(0, 0);
			this.dataGridView1.Name = "dataGridView1";
			this.dataGridView1.Size = new System.Drawing.Size(580, 462);
			this.dataGridView1.TabIndex = 0;
			// 
			// protoIdDataGridViewTextBoxColumn
			// 
			this.protoIdDataGridViewTextBoxColumn.DataPropertyName = "ProtoId";
			this.protoIdDataGridViewTextBoxColumn.HeaderText = "ProtoId";
			this.protoIdDataGridViewTextBoxColumn.Name = "protoIdDataGridViewTextBoxColumn";
			// 
			// protoNameDataGridViewTextBoxColumn
			// 
			this.protoNameDataGridViewTextBoxColumn.DataPropertyName = "ProtoName";
			this.protoNameDataGridViewTextBoxColumn.FillWeight = 130F;
			this.protoNameDataGridViewTextBoxColumn.HeaderText = "Наименование";
			this.protoNameDataGridViewTextBoxColumn.Name = "protoNameDataGridViewTextBoxColumn";
			this.protoNameDataGridViewTextBoxColumn.Width = 130;
			// 
			// protoDescriptionDataGridViewTextBoxColumn
			// 
			this.protoDescriptionDataGridViewTextBoxColumn.DataPropertyName = "ProtoDescription";
			this.protoDescriptionDataGridViewTextBoxColumn.FillWeight = 240F;
			this.protoDescriptionDataGridViewTextBoxColumn.HeaderText = "Описание";
			this.protoDescriptionDataGridViewTextBoxColumn.Name = "protoDescriptionDataGridViewTextBoxColumn";
			this.protoDescriptionDataGridViewTextBoxColumn.Width = 240;
			// 
			// aliasDataGridViewTextBoxColumn
			// 
			this.aliasDataGridViewTextBoxColumn.DataPropertyName = "Alias";
			this.aliasDataGridViewTextBoxColumn.FillWeight = 180F;
			this.aliasDataGridViewTextBoxColumn.HeaderText = "Представление в скриптах";
			this.aliasDataGridViewTextBoxColumn.Name = "aliasDataGridViewTextBoxColumn";
			this.aliasDataGridViewTextBoxColumn.Width = 180;
			// 
			// typeDataGridViewTextBoxColumn
			// 
			this.typeDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
			this.typeDataGridViewTextBoxColumn.DataPropertyName = "Type";
			this.typeDataGridViewTextBoxColumn.HeaderText = "Тип предмета";
			this.typeDataGridViewTextBoxColumn.MinimumWidth = 25;
			this.typeDataGridViewTextBoxColumn.Name = "typeDataGridViewTextBoxColumn";
			// 
			// cm
			// 
			this.cm.DataSource = typeof(AuctionAdminMK2.Fonline.FOProtoItem);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(216, 13);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(352, 41);
			this.label1.TabIndex = 2;
			this.label1.Text = "Позволяет повторно перезаписывать прототипы, но при этом происходит продувка всех" +
				" лотов с заменой Id на новое. Может занять недели";
			// 
			// fExport
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(580, 525);
			this.Controls.Add(this.panel2);
			this.Controls.Add(this.panel1);
			this.Name = "fExport";
			this.Text = "Экспорт описаний прототипов из серверных файлов";
			this.panel1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.cm)).EndInit();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.OpenFileDialog fd;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.BindingSource cm;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn protoIdDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn protoNameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn protoDescriptionDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn aliasDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn typeDataGridViewTextBoxColumn;
        private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Label label1;
    }
}