using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AuctionAdminMK2
{
    public partial class fEditItemType : Form
    {
        public fEditItemType()
        {
            InitializeComponent();
        }

		private void tItemTypeBindingNavigatorSaveItem_Click(object sender, EventArgs e)
		{
			this.Validate();
			this.tItemTypeBindingSource.EndEdit();
			this.tableAdapterManager.UpdateAll(this.dsMain);

		}

		private void fEditItemType_Load(object sender, EventArgs e)
		{
			// TODO: This line of code loads data into the 'dsMain.tItemType' table. You can move, or remove it, as needed.
			this.tItemTypeTableAdapter.Fill(this.dsMain.tItemType);

		}
    }
}
