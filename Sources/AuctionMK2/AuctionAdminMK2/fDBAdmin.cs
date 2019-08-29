using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SQLite;

namespace AuctionAdminMK2
{
    public partial class fDBAdmin : Form
    {
        public fDBAdmin()
        {
            InitializeComponent();
        }



        private void bOk_Click(object sender, EventArgs e)
        {
      
        }

        private void fDBAdmin_Load(object sender, EventArgs e)
        {
            tbxCnString.Text = Properties.Settings.Default.mk2ConnectionString.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                // data source=F:\mk2\mk2.db;FailIfMissing=True
                SQLiteConnection cn = new SQLiteConnection(Properties.Settings.Default.mk2ConnectionString);
                cn.Open();
                cn.Close();
                MessageBox.Show("Подключение успешно установлено");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message );    
            }
        }
    }
}
