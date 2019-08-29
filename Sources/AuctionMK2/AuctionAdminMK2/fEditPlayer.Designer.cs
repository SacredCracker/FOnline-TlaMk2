namespace AuctionAdminMK2
{
    partial class fEditPlayer
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fEditPlayer));
			this.dsMain = new AuctionAdminMK2.data.dsMain();
			this.tPlayerBindingSource = new System.Windows.Forms.BindingSource(this.components);
			this.tPlayerTableAdapter = new AuctionAdminMK2.data.dsMainTableAdapters.tPlayerTableAdapter();
			this.tableAdapterManager = new AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager();
			this.tPlayerBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
			this.bindingNavigatorMoveFirstItem = new System.Windows.Forms.ToolStripButton();
			this.bindingNavigatorMovePreviousItem = new System.Windows.Forms.ToolStripButton();
			this.bindingNavigatorSeparator = new System.Windows.Forms.ToolStripSeparator();
			this.bindingNavigatorPositionItem = new System.Windows.Forms.ToolStripTextBox();
			this.bindingNavigatorCountItem = new System.Windows.Forms.ToolStripLabel();
			this.bindingNavigatorSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.bindingNavigatorMoveNextItem = new System.Windows.Forms.ToolStripButton();
			this.bindingNavigatorMoveLastItem = new System.Windows.Forms.ToolStripButton();
			this.bindingNavigatorSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.bindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
			this.bindingNavigatorDeleteItem = new System.Windows.Forms.ToolStripButton();
			this.tPlayerBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
			this.tPlayerDataGridView = new System.Windows.Forms.DataGridView();
			this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			((System.ComponentModel.ISupportInitialize)(this.dsMain)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerBindingSource)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerBindingNavigator)).BeginInit();
			this.tPlayerBindingNavigator.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerDataGridView)).BeginInit();
			this.SuspendLayout();
			// 
			// dsMain
			// 
			this.dsMain.DataSetName = "dsMain";
			this.dsMain.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
			// 
			// tPlayerBindingSource
			// 
			this.tPlayerBindingSource.DataMember = "tPlayer";
			this.tPlayerBindingSource.DataSource = this.dsMain;
			// 
			// tPlayerTableAdapter
			// 
			this.tPlayerTableAdapter.ClearBeforeFill = true;
			// 
			// tableAdapterManager
			// 
			this.tableAdapterManager.BackupDataSetBeforeUpdate = false;
			this.tableAdapterManager.tItemProtoTableAdapter = null;
			this.tableAdapterManager.tItemTypeTableAdapter = null;
			this.tableAdapterManager.tLotsTableAdapter = null;
			this.tableAdapterManager.tPlayerTableAdapter = this.tPlayerTableAdapter;
			this.tableAdapterManager.UpdateOrder = AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager.UpdateOrderOption.InsertUpdateDelete;
			// 
			// tPlayerBindingNavigator
			// 
			this.tPlayerBindingNavigator.AddNewItem = this.bindingNavigatorAddNewItem;
			this.tPlayerBindingNavigator.BindingSource = this.tPlayerBindingSource;
			this.tPlayerBindingNavigator.CountItem = this.bindingNavigatorCountItem;
			this.tPlayerBindingNavigator.DeleteItem = this.bindingNavigatorDeleteItem;
			this.tPlayerBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bindingNavigatorMoveFirstItem,
            this.bindingNavigatorMovePreviousItem,
            this.bindingNavigatorSeparator,
            this.bindingNavigatorPositionItem,
            this.bindingNavigatorCountItem,
            this.bindingNavigatorSeparator1,
            this.bindingNavigatorMoveNextItem,
            this.bindingNavigatorMoveLastItem,
            this.bindingNavigatorSeparator2,
            this.bindingNavigatorAddNewItem,
            this.bindingNavigatorDeleteItem,
            this.tPlayerBindingNavigatorSaveItem});
			this.tPlayerBindingNavigator.Location = new System.Drawing.Point(0, 0);
			this.tPlayerBindingNavigator.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
			this.tPlayerBindingNavigator.MoveLastItem = this.bindingNavigatorMoveLastItem;
			this.tPlayerBindingNavigator.MoveNextItem = this.bindingNavigatorMoveNextItem;
			this.tPlayerBindingNavigator.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
			this.tPlayerBindingNavigator.Name = "tPlayerBindingNavigator";
			this.tPlayerBindingNavigator.PositionItem = this.bindingNavigatorPositionItem;
			this.tPlayerBindingNavigator.Size = new System.Drawing.Size(457, 25);
			this.tPlayerBindingNavigator.TabIndex = 0;
			this.tPlayerBindingNavigator.Text = "bindingNavigator1";
			// 
			// bindingNavigatorMoveFirstItem
			// 
			this.bindingNavigatorMoveFirstItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorMoveFirstItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveFirstItem.Image")));
			this.bindingNavigatorMoveFirstItem.Name = "bindingNavigatorMoveFirstItem";
			this.bindingNavigatorMoveFirstItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorMoveFirstItem.Size = new System.Drawing.Size(23, 22);
			this.bindingNavigatorMoveFirstItem.Text = "Move first";
			// 
			// bindingNavigatorMovePreviousItem
			// 
			this.bindingNavigatorMovePreviousItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorMovePreviousItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMovePreviousItem.Image")));
			this.bindingNavigatorMovePreviousItem.Name = "bindingNavigatorMovePreviousItem";
			this.bindingNavigatorMovePreviousItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorMovePreviousItem.Size = new System.Drawing.Size(23, 22);
			this.bindingNavigatorMovePreviousItem.Text = "Move previous";
			// 
			// bindingNavigatorSeparator
			// 
			this.bindingNavigatorSeparator.Name = "bindingNavigatorSeparator";
			this.bindingNavigatorSeparator.Size = new System.Drawing.Size(6, 25);
			// 
			// bindingNavigatorPositionItem
			// 
			this.bindingNavigatorPositionItem.AccessibleName = "Position";
			this.bindingNavigatorPositionItem.AutoSize = false;
			this.bindingNavigatorPositionItem.Name = "bindingNavigatorPositionItem";
			this.bindingNavigatorPositionItem.Size = new System.Drawing.Size(50, 21);
			this.bindingNavigatorPositionItem.Text = "0";
			this.bindingNavigatorPositionItem.ToolTipText = "Current position";
			// 
			// bindingNavigatorCountItem
			// 
			this.bindingNavigatorCountItem.Name = "bindingNavigatorCountItem";
			this.bindingNavigatorCountItem.Size = new System.Drawing.Size(36, 13);
			this.bindingNavigatorCountItem.Text = "of {0}";
			this.bindingNavigatorCountItem.ToolTipText = "Total number of items";
			// 
			// bindingNavigatorSeparator1
			// 
			this.bindingNavigatorSeparator1.Name = "bindingNavigatorSeparator";
			this.bindingNavigatorSeparator1.Size = new System.Drawing.Size(6, 6);
			// 
			// bindingNavigatorMoveNextItem
			// 
			this.bindingNavigatorMoveNextItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorMoveNextItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveNextItem.Image")));
			this.bindingNavigatorMoveNextItem.Name = "bindingNavigatorMoveNextItem";
			this.bindingNavigatorMoveNextItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorMoveNextItem.Size = new System.Drawing.Size(23, 20);
			this.bindingNavigatorMoveNextItem.Text = "Move next";
			// 
			// bindingNavigatorMoveLastItem
			// 
			this.bindingNavigatorMoveLastItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorMoveLastItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveLastItem.Image")));
			this.bindingNavigatorMoveLastItem.Name = "bindingNavigatorMoveLastItem";
			this.bindingNavigatorMoveLastItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorMoveLastItem.Size = new System.Drawing.Size(23, 20);
			this.bindingNavigatorMoveLastItem.Text = "Move last";
			// 
			// bindingNavigatorSeparator2
			// 
			this.bindingNavigatorSeparator2.Name = "bindingNavigatorSeparator";
			this.bindingNavigatorSeparator2.Size = new System.Drawing.Size(6, 6);
			// 
			// bindingNavigatorAddNewItem
			// 
			this.bindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorAddNewItem.Image")));
			this.bindingNavigatorAddNewItem.Name = "bindingNavigatorAddNewItem";
			this.bindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 22);
			this.bindingNavigatorAddNewItem.Text = "Add new";
			// 
			// bindingNavigatorDeleteItem
			// 
			this.bindingNavigatorDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.bindingNavigatorDeleteItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorDeleteItem.Image")));
			this.bindingNavigatorDeleteItem.Name = "bindingNavigatorDeleteItem";
			this.bindingNavigatorDeleteItem.RightToLeftAutoMirrorImage = true;
			this.bindingNavigatorDeleteItem.Size = new System.Drawing.Size(23, 20);
			this.bindingNavigatorDeleteItem.Text = "Delete";
			// 
			// tPlayerBindingNavigatorSaveItem
			// 
			this.tPlayerBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tPlayerBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("tPlayerBindingNavigatorSaveItem.Image")));
			this.tPlayerBindingNavigatorSaveItem.Name = "tPlayerBindingNavigatorSaveItem";
			this.tPlayerBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 23);
			this.tPlayerBindingNavigatorSaveItem.Text = "Save Data";
			this.tPlayerBindingNavigatorSaveItem.Click += new System.EventHandler(this.tPlayerBindingNavigatorSaveItem_Click);
			// 
			// tPlayerDataGridView
			// 
			this.tPlayerDataGridView.AutoGenerateColumns = false;
			this.tPlayerDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.tPlayerDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3});
			this.tPlayerDataGridView.DataSource = this.tPlayerBindingSource;
			this.tPlayerDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tPlayerDataGridView.Location = new System.Drawing.Point(0, 25);
			this.tPlayerDataGridView.Name = "tPlayerDataGridView";
			this.tPlayerDataGridView.Size = new System.Drawing.Size(457, 316);
			this.tPlayerDataGridView.TabIndex = 1;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this.dataGridViewTextBoxColumn1.DataPropertyName = "Id";
			this.dataGridViewTextBoxColumn1.HeaderText = "Id";
			this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
			// 
			// dataGridViewTextBoxColumn2
			// 
			this.dataGridViewTextBoxColumn2.DataPropertyName = "FOCritterId";
			this.dataGridViewTextBoxColumn2.HeaderText = "FOCritterId";
			this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
			// 
			// dataGridViewTextBoxColumn3
			// 
			this.dataGridViewTextBoxColumn3.DataPropertyName = "FOPlayerName";
			this.dataGridViewTextBoxColumn3.HeaderText = "FOPlayerName";
			this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
			// 
			// fEditPlayer
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(457, 341);
			this.Controls.Add(this.tPlayerDataGridView);
			this.Controls.Add(this.tPlayerBindingNavigator);
			this.Name = "fEditPlayer";
			this.Text = "Игроки";
			this.Load += new System.EventHandler(this.fEditPlayer_Load);
			((System.ComponentModel.ISupportInitialize)(this.dsMain)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerBindingSource)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerBindingNavigator)).EndInit();
			this.tPlayerBindingNavigator.ResumeLayout(false);
			this.tPlayerBindingNavigator.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.tPlayerDataGridView)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private AuctionAdminMK2.data.dsMain dsMain;
		private System.Windows.Forms.BindingSource tPlayerBindingSource;
		private AuctionAdminMK2.data.dsMainTableAdapters.tPlayerTableAdapter tPlayerTableAdapter;
		private AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager tableAdapterManager;
		private System.Windows.Forms.BindingNavigator tPlayerBindingNavigator;
		private System.Windows.Forms.ToolStripButton bindingNavigatorAddNewItem;
		private System.Windows.Forms.ToolStripLabel bindingNavigatorCountItem;
		private System.Windows.Forms.ToolStripButton bindingNavigatorDeleteItem;
		private System.Windows.Forms.ToolStripButton bindingNavigatorMoveFirstItem;
		private System.Windows.Forms.ToolStripButton bindingNavigatorMovePreviousItem;
		private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator;
		private System.Windows.Forms.ToolStripTextBox bindingNavigatorPositionItem;
		private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator1;
		private System.Windows.Forms.ToolStripButton bindingNavigatorMoveNextItem;
		private System.Windows.Forms.ToolStripButton bindingNavigatorMoveLastItem;
		private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator2;
		private System.Windows.Forms.ToolStripButton tPlayerBindingNavigatorSaveItem;
		private System.Windows.Forms.DataGridView tPlayerDataGridView;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
    }
}