using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace PidsRename
{
    public partial class Form1 : Form
    {
        string mapName = "";
        string path = "";
        public Form1()
        {
            InitializeComponent();
            if (checkBox1.Checked)
            {
               textBoxPathItemPid.Enabled = false;
               textBoxPathItemName.Enabled = false;
               textBoxPathProto.Enabled = false;
               textBoxPathText.Enabled = false;                
            }

            ReadFileInArray config = new ReadFileInArray("config.cfg");
            path = config.arrayListOfStrings[0].Replace("ServerPath=", "");    
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                textBoxPathItemPid.Enabled = false;
                textBoxPathItemName.Enabled = false;
                textBoxPathProto.Enabled = false;
                textBoxPathText.Enabled = false;
                textBoxPath.Enabled = true;
                return;
            }
            
            textBoxPathItemPid.Enabled = true;
            textBoxPathItemName.Enabled = true;
            textBoxPathProto.Enabled = true;
            textBoxPathText.Enabled = true;
            textBoxPath.Enabled = false;
        }

        private void label5_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            textBoxPath.Text = "new_itempid.fos";
            this.Width = 468;
            this.Height = 269;
            listBox1.Visible = false;
            button2.Visible = false;
        }

        private void button1_Click_2(object sender, EventArgs e)
        {
            this.Width = 999;
            this.Height = 463;
            listBox1.Visible = true;
            button1.Visible = false;
            button2.Visible = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Width = 468;
            this.Height = 269;
            listBox1.Visible = false;
            button1.Visible = true;
            button2.Visible = false;
        }

        // Диагностика
        private void label1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox1.Items.Add("Старый пид" + "\t" + "Новый пид" + "\t" + "Именованая константа");
            listBox1.Items.Add("________________________________________________________________________");
            FilesItemInfo fItemInfo = new FilesItemInfo("\\scripts\\_itempid.fos", textBoxPath.Text);
            for (int i = 0; i < fItemInfo.arrayItemNames.Length; i++)
                listBox1.Items.Add("|\t" + fItemInfo.arrayOldPidNumbers[i] + "\t|\t" + fItemInfo.arrayNewPidNumbers[i] + "\t| " + fItemInfo.arrayItemNames[i]);            
        }

        private void label2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox1.Items.Add("Пид" + "\t" + "Именованая константа");
            listBox1.Items.Add("________________________________________________________________________");
            listBox1.Items.Add("");
            ItemNamesLst itLst = new ItemNamesLst(textBoxPath.Text);
            itLst.SetNewItemList();
            for (int i = 0; i < itLst.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itLst.file.arrayListOfStrings[i]);
        }

        private void label3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ItemPidsNumber itPidsNum = new ItemPidsNumber(textBoxPath.Text);
            itPidsNum.SetNewPidsNumber();
            for (int i = 0; i < itPidsNum.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itPidsNum.file.arrayListOfStrings[i]);
        }

        private void label4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("russ", textBoxPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void label6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("engl", textBoxPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void label7_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoItemFiles prItfiles = new ProtoItemFiles("ammo.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            for (int i = 0; i < prItfiles.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(prItfiles.file.arrayListOfStrings[i]);
        }

        private void label8_Click(object sender, EventArgs e)
        {
            string[] fileNames = Directory.GetFiles(path + "maps");

            for (int i = 0; i < fileNames.Length; i++)
            {
                fileNames[i] = fileNames[i].Replace(path + "maps\\", "");     
            }

            listBox1.Items.Clear();
            foreach (string item in fileNames)
            {
                listBox1.Items.Add(item);
            }
        }

        private void label9_Click(object sender, EventArgs e)
        {
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            mapName=(string)listBox1.SelectedItem;
        }

        private void itemNameslstToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ItemNamesLst itLst = new ItemNamesLst(textBoxPath.Text);
            itLst.SetNewItemList();
            itLst.writeFile();
        }

        private void itempidfosToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ItemPidsNumber itPidsNum = new ItemPidsNumber(textBoxPath.Text);
            itPidsNum.SetNewPidsNumber();
            itPidsNum.writeFile();
        }

        private void russFoobjmsgToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TxtFoobj txtFj = new TxtFoobj("russ", textBoxPath.Text);
            txtFj.SetNewText();
            txtFj.writeFile();
        }

        private void englFoobjmsgToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TxtFoobj txtFj = new TxtFoobj("engl", textBoxPath.Text);
            txtFj.SetNewText();
            txtFj.writeFile();
        }

        private void allProtoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProtoItemFiles prItfiles = new ProtoItemFiles("ammo.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("armor.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("car.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("container.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("door.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("drug.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("generic.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("grid.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("key.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("misc.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("wall.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("weapon.fopro", textBoxPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
        }

        private void currentMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (mapName == "")
            {
                MessageBox.Show("Карта не выбрана. Нужно вывести список какрт и выбрать нужную");
                return;
            }

            if (!mapName.Contains(".fomap"))
            {
                MessageBox.Show("Выбраный элемент не является картой");
                return;
            }

            MapFiles map = new MapFiles(mapName, textBoxPath.Text);
            map.setNewPidItemInMap();
            map.writeFile();
        }

        private void allMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] fileNames = Directory.GetFiles(path + "maps");

            for (int i = 0; i < fileNames.Length; i++)
            {
                fileNames[i] = fileNames[i].Replace(path + "maps\\", "");
                MapFiles map = new MapFiles(fileNames[i], textBoxPath.Text);
                map.setNewPidItemInMap();
                map.writeFile();
            }
        }
    }
}