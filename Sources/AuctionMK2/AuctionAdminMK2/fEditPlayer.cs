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
    public partial class fEditPlayer : Form
    {
        public fEditPlayer()
        {
            InitializeComponent();
        }

		private void tPlayerBindingNavigatorSaveItem_Click(object sender, EventArgs e)
		{
			this.Validate();
			this.tPlayerBindingSource.EndEdit();
			this.tableAdapterManager.UpdateAll(this.dsMain);

		}

		private void fEditPlayer_Load(object sender, EventArgs e)
		{
			// TODO: This line of code loads data into the 'dsMain.tPlayer' table. You can move, or remove it, as needed.
			this.tPlayerTableAdapter.Fill(this.dsMain.tPlayer);

		}
    }
}
