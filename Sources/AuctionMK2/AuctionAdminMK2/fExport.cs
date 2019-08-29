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
    public partial class fExport : Form
    {
        public fExport()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Fonline.FOProtoItemManager mng = new AuctionAdminMK2.Fonline.FOProtoItemManager();
                if (fd.ShowDialog() == DialogResult.OK)
                {
                    Cursor = Cursors.WaitCursor;
                    mng.Load(fd.FileName);
                    this.cm.DataSource = mng.Items;
                    this.cm.ResetBindings(false);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                Cursor = Cursors.Arrow;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (MessageBox.Show("Подтвердите экспорт списка в базу данных.", "Экспорт", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                    return;
                data.dsMain ds = new AuctionAdminMK2.data.dsMain();
                data.dsMainTableAdapters.TableAdapterManager ta = new AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager();
                ta.Init();
                ta.tItemTypeTableAdapter.Fill(ds.tItemType);
                var q = (this.cm.DataSource as List<Fonline.FOProtoItem>);
                fBase f = this.MdiParent as fBase;
                int c = 0;
                int l = q.Count();
                f.ProgressBar.Maximum = q.Count();
                f.ProgressBar.Value = 0;
                foreach (var i in q)
                {
                    c++;
                    if (f != null)
                    {
                        f.ProgressBar.Value = c;
                        f.StatusLabel.Text = string.Format("Обработка записи {0} из {1}", c, l);
                        Application.DoEvents();
                    }

                    i.Export(ds.tItemType );
                }
                if (f != null)
                {
                    f.ProgressBar.Value = 0;
                    f.StatusLabel.Text = "Выполнено";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message );
            }
        }

    }
}
