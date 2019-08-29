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
    public partial class fBase : Form
    {
        public fBase()
        {
            InitializeComponent();
        }

        private void настройкиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                fDBAdmin f = new fDBAdmin();
                f.StartPosition = FormStartPosition.CenterParent;
                f.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message );
            }
        }

        private void exportToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                fExport f = new fExport();
                f.MdiParent = this;
                f.WindowState = FormWindowState.Maximized;
                f.Show();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message );
            }
        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

		private void прототипыПредметовToolStripMenuItem_Click(object sender, EventArgs e)
		{
			try
			{
				fEditItemProto f = new fEditItemProto();
				f.MdiParent = this;
				f.WindowState = FormWindowState.Maximized;
				f.Show();
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message );
			}
		}

		private void miTypes_Click(object sender, EventArgs e)
		{
			try
			{

				fEditItemType f = new fEditItemType();
				f.MdiParent = this;
				f.WindowState = FormWindowState.Maximized;
				f.Show();
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message );
			}
		}

		private void miLots_Click(object sender, EventArgs e)
		{
			try
			{
				fEditLots f = new fEditLots();
				f.MdiParent = this;
				f.WindowState = FormWindowState.Maximized;
				f.Show();
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
			}
		}

		private void miPlayers_Click(object sender, EventArgs e)
		{
			try
			{
				fEditPlayer f = new fEditPlayer();
				f.MdiParent = this;
				f.WindowState = FormWindowState.Maximized;
				f.Show();
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
			}
		}
    }
}
