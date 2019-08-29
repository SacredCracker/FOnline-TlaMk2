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
    public partial class fEditItemProto : Form
    {
        public fEditItemProto()
        {
            InitializeComponent();
        }

		private void tItemProtoBindingNavigatorSaveItem_Click(object sender, EventArgs e)
		{
			this.Validate();
			this.tItemProtoBindingSource.EndEdit();
			this.tableAdapterManager.UpdateAll(this.dsMain);

		}

		private void fEditItemProto_Load(object sender, EventArgs e)
		{
			// TODO: This line of code loads data into the 'dsMain.tItemProto' table. You can move, or remove it, as needed.
			this.tItemProtoTableAdapter.Fill(this.dsMain.tItemProto);

		}
    }
}
