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
    public partial class fBackup : Form
    {
        public fBackup()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                System.Data.SQLite.SQLiteConnection cn = new System.Data.SQLite.SQLiteConnection("F:\\mk2\\mk2.db");
                //cn.BackupDatabase();
                //System.Data.SQLite
                System.Data.SQLite.SQLiteConnection.CreateFile("amk2.db");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при попытке бекапа:\n" + ex,ToString());
            }
        }
    }
}
