namespace AuctionAdminMK2
{
    partial class fEditItemProto
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fEditItemProto));
			this.dsMain = new AuctionAdminMK2.data.dsMain();
			this.tItemProtoBindingSource = new System.Windows.Forms.BindingSource(this.components);
			this.tItemProtoTableAdapter = new AuctionAdminMK2.data.dsMainTableAdapters.tItemProtoTableAdapter();
			this.tableAdapterManager = new AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager();
			this.tItemProtoBindingNavigator = new System.Windows.Forms.BindingNavigator(this.components);
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
			this.tItemProtoBindingNavigatorSaveItem = new System.Windows.Forms.ToolStripButton();
			this.tItemProtoDataGridView = new System.Windows.Forms.DataGridView();
			this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dataGridViewTextBoxColumn6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			((System.ComponentModel.ISupportInitialize)(this.dsMain)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoBindingSource)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoBindingNavigator)).BeginInit();
			this.tItemProtoBindingNavigator.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoDataGridView)).BeginInit();
			this.SuspendLayout();
			// 
			// dsMain
			// 
			this.dsMain.DataSetName = "dsMain";
			this.dsMain.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
			// 
			// tItemProtoBindingSource
			// 
			this.tItemProtoBindingSource.DataMember = "tItemProto";
			this.tItemProtoBindingSource.DataSource = this.dsMain;
			// 
			// tItemProtoTableAdapter
			// 
			this.tItemProtoTableAdapter.ClearBeforeFill = true;
			// 
			// tableAdapterManager
			// 
			this.tableAdapterManager.BackupDataSetBeforeUpdate = false;
			this.tableAdapterManager.tItemProtoTableAdapter = this.tItemProtoTableAdapter;
			this.tableAdapterManager.tItemTypeTableAdapter = null;
			this.tableAdapterManager.tLotsTableAdapter = null;
			this.tableAdapterManager.tPlayerTableAdapter = null;
			this.tableAdapterManager.UpdateOrder = AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager.UpdateOrderOption.InsertUpdateDelete;
			// 
			// tItemProtoBindingNavigator
			// 
			this.tItemProtoBindingNavigator.AddNewItem = this.bindingNavigatorAddNewItem;
			this.tItemProtoBindingNavigator.BindingSource = this.tItemProtoBindingSource;
			this.tItemProtoBindingNavigator.CountItem = this.bindingNavigatorCountItem;
			this.tItemProtoBindingNavigator.DeleteItem = this.bindingNavigatorDeleteItem;
			this.tItemProtoBindingNavigator.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
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
            this.tItemProtoBindingNavigatorSaveItem});
			this.tItemProtoBindingNavigator.Location = new System.Drawing.Point(0, 0);
			this.tItemProtoBindingNavigator.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
			this.tItemProtoBindingNavigator.MoveLastItem = this.bindingNavigatorMoveLastItem;
			this.tItemProtoBindingNavigator.MoveNextItem = this.bindingNavigatorMoveNextItem;
			this.tItemProtoBindingNavigator.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
			this.tItemProtoBindingNavigator.Name = "tItemProtoBindingNavigator";
			this.tItemProtoBindingNavigator.PositionItem = this.bindingNavigatorPositionItem;
			this.tItemProtoBindingNavigator.Size = new System.Drawing.Size(556, 25);
			this.tItemProtoBindingNavigator.TabIndex = 0;
			this.tItemProtoBindingNavigator.Text = "bindingNavigator1";
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
			// tItemProtoBindingNavigatorSaveItem
			// 
			this.tItemProtoBindingNavigatorSaveItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tItemProtoBindingNavigatorSaveItem.Image = ((System.Drawing.Image)(resources.GetObject("tItemProtoBindingNavigatorSaveItem.Image")));
			this.tItemProtoBindingNavigatorSaveItem.Name = "tItemProtoBindingNavigatorSaveItem";
			this.tItemProtoBindingNavigatorSaveItem.Size = new System.Drawing.Size(23, 23);
			this.tItemProtoBindingNavigatorSaveItem.Text = "Save Data";
			this.tItemProtoBindingNavigatorSaveItem.Click += new System.EventHandler(this.tItemProtoBindingNavigatorSaveItem_Click);
			// 
			// tItemProtoDataGridView
			// 
			this.tItemProtoDataGridView.AutoGenerateColumns = false;
			this.tItemProtoDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.tItemProtoDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3,
            this.dataGridViewTextBoxColumn4,
            this.dataGridViewTextBoxColumn5,
            this.dataGridViewTextBoxColumn6});
			this.tItemProtoDataGridView.DataSource = this.tItemProtoBindingSource;
			this.tItemProtoDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tItemProtoDataGridView.Location = new System.Drawing.Point(0, 25);
			this.tItemProtoDataGridView.Name = "tItemProtoDataGridView";
			this.tItemProtoDataGridView.Size = new System.Drawing.Size(556, 428);
			this.tItemProtoDataGridView.TabIndex = 1;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this.dataGridViewTextBoxColumn1.DataPropertyName = "Id";
			this.dataGridViewTextBoxColumn1.HeaderText = "Id";
			this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
			// 
			// dataGridViewTextBoxColumn2
			// 
			this.dataGridViewTextBoxColumn2.DataPropertyName = "FOProtoId";
			this.dataGridViewTextBoxColumn2.HeaderText = "FOProtoId";
			this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
			// 
			// dataGridViewTextBoxColumn3
			// 
			this.dataGridViewTextBoxColumn3.DataPropertyName = "FOProtoName";
			this.dataGridViewTextBoxColumn3.HeaderText = "FOProtoName";
			this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
			// 
			// dataGridViewTextBoxColumn4
			// 
			this.dataGridViewTextBoxColumn4.DataPropertyName = "FOProtoDescription";
			this.dataGridViewTextBoxColumn4.HeaderText = "FOProtoDescription";
			this.dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
			// 
			// dataGridViewTextBoxColumn5
			// 
			this.dataGridViewTextBoxColumn5.DataPropertyName = "FOAlias";
			this.dataGridViewTextBoxColumn5.HeaderText = "FOAlias";
			this.dataGridViewTextBoxColumn5.Name = "dataGridViewTextBoxColumn5";
			// 
			// dataGridViewTextBoxColumn6
			// 
			this.dataGridViewTextBoxColumn6.DataPropertyName = "TypeId";
			this.dataGridViewTextBoxColumn6.HeaderText = "TypeId";
			this.dataGridViewTextBoxColumn6.Name = "dataGridViewTextBoxColumn6";
			// 
			// fEditItemProto
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(556, 453);
			this.Controls.Add(this.tItemProtoDataGridView);
			this.Controls.Add(this.tItemProtoBindingNavigator);
			this.Name = "fEditItemProto";
			this.Text = "Прототипы предметов";
			this.Load += new System.EventHandler(this.fEditItemProto_Load);
			((System.ComponentModel.ISupportInitialize)(this.dsMain)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoBindingSource)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoBindingNavigator)).EndInit();
			this.tItemProtoBindingNavigator.ResumeLayout(false);
			this.tItemProtoBindingNavigator.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.tItemProtoDataGridView)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private AuctionAdminMK2.data.dsMain dsMain;
		private System.Windows.Forms.BindingSource tItemProtoBindingSource;
		private AuctionAdminMK2.data.dsMainTableAdapters.tItemProtoTableAdapter tItemProtoTableAdapter;
		private AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager tableAdapterManager;
		private System.Windows.Forms.BindingNavigator tItemProtoBindingNavigator;
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
		private System.Windows.Forms.ToolStripButton tItemProtoBindingNavigatorSaveItem;
		private System.Windows.Forms.DataGridView tItemProtoDataGridView;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn5;
		private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn6;
    }
}