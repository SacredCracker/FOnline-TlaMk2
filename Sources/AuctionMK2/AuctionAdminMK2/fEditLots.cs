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
    public partial class fEditLots : Form
    {
        public fEditLots()
        {
            InitializeComponent();
        }

		private void tLotsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
		{
            try
            {

			this.Validate();
			this.tLotsBindingSource.EndEdit();
			this.tableAdapterManager.UpdateAll(this.dsMain);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message );
            }

		}

		private void fEditLots_Load(object sender, EventArgs e)
		{
			// TODO: This line of code loads data into the 'dsMain.tLots' table. You can move, or remove it, as needed.
			this.tLotsTableAdapter.Fill(this.dsMain.tLots);

		}
    }
}
