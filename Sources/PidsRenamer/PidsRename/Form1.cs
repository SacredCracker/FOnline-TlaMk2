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
        string dlgName = "";
        string path = "";
        public Form1()
        {
            InitializeComponent();
            if (checkBoxNewItemPid.Checked)
            {
               ServerPath.Enabled = false;             
            }

            ReadFileInArray config = new ReadFileInArray("config.cfg");
            path = config.arrayListOfStrings[0].Replace("ServerPath=", "");    
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxNewItemPid.Checked)
            {
                ServerPath.Enabled = false;
                NewItemPidPath.Enabled = true;
                return;
            }
            
            ServerPath.Enabled = true;
            NewItemPidPath.Enabled = false;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            NewItemPidPath.Text = "new_itempid.fos";
        }

        private void label2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ItemNamesLst itLst = new ItemNamesLst(NewItemPidPath.Text);
            itLst.SetNewItemList();
            for (int i = 0; i < itLst.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itLst.file.arrayListOfStrings[i]);
        }

        private void label3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ItemPidsNumber itPidsNum = new ItemPidsNumber(NewItemPidPath.Text);
            itPidsNum.SetNewPidsNumber();
            for (int i = 0; i < itPidsNum.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itPidsNum.file.arrayListOfStrings[i]);
        }

        private void label4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("russ", NewItemPidPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void label6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("engl", NewItemPidPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void label9_Click(object sender, EventArgs e)
        {
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            mapName=(string)listBox1.SelectedItem;
            dlgName=(string)listBox1.SelectedItem;
        }

        private void itemNameslstToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ItemNamesLst itLst = new ItemNamesLst(NewItemPidPath.Text);
            itLst.SetNewItemList();
            itLst.writeFile();
        }

        private void itempidfosToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ItemPidsNumber itPidsNum = new ItemPidsNumber(NewItemPidPath.Text);
            itPidsNum.SetNewPidsNumber();
            itPidsNum.writeFile();
        }

        private void russFoobjmsgToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TxtFoobj txtFj = new TxtFoobj("russ", NewItemPidPath.Text);
            txtFj.SetNewText();
            txtFj.writeFile();
        }

        private void englFoobjmsgToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TxtFoobj txtFj = new TxtFoobj("engl", NewItemPidPath.Text);
            txtFj.SetNewText();
            txtFj.writeFile();
        }

        private void allProtoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProtoItemFiles prItfiles = new ProtoItemFiles("ammo.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("armor.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("car.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("container.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("door.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("drug.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("generic.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("grid.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("key.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("misc.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("wall.fopro", NewItemPidPath.Text);
            prItfiles.setNewProto();
            prItfiles.writeFile();
            prItfiles = new ProtoItemFiles("weapon.fopro", NewItemPidPath.Text);
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

            MapFiles map = new MapFiles(mapName, NewItemPidPath.Text);
            map.setNewPidItemInMap();
            map.writeFile();
        }

        List<string> getListOfStrings(string[] arrayListOfStrings)
        {
            List<string> ListOfStrings = new List<string>();

            foreach (string str in arrayListOfStrings)
            {
                if (!str.Contains("#define") || str.Contains("__ITEM_PID__") || !str.Contains("PID_"))
                    continue;
                ListOfStrings.Add(str);
            }
            return ListOfStrings;
        }

        private void allMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] arrayItemNames;
            string[] arrayNewPidNumbers;
            string[] arrayOldPidNumbers;
            ReadFileInArray new_itempid;
            new_itempid = new ReadFileInArray(NewItemPidPath.Text);
            ReadFileInArray oldItemsName;
            oldItemsName = new ReadFileInArray("old_itempid.fos");
            List<string> NewListOfStrings = getListOfStrings(new_itempid.arrayListOfStrings);
            List<string> OldListOfStrings = getListOfStrings(oldItemsName.arrayListOfStrings);

            arrayItemNames = new string[NewListOfStrings.Count];
            arrayNewPidNumbers = new string[NewListOfStrings.Count];
            arrayOldPidNumbers = new string[NewListOfStrings.Count];

            int i = 0;
            foreach (string str in NewListOfStrings)
            {
                string buf = str.Replace("#define", "").Replace(" ", "").Replace("\t", "");
                int startNum = 0;
                int finNum = 0;
                for (int j = 0, jMax = buf.Length; j < jMax; j++)
                {
                    if (buf[j] == ')')
                    {
                        finNum = j;
                        break;
                    }
                    if (buf[j] == '(')
                        startNum = j;
                }

                arrayItemNames[i] += buf.Substring(0, startNum);
                arrayNewPidNumbers[i] += buf.Substring(startNum + 1, ((finNum - startNum) - 1) > 0 ? ((finNum - startNum) - 1) : 1);

                arrayOldPidNumbers[i] = "-1";
                foreach (string oldStr in OldListOfStrings)
                {
                    buf = oldStr.Replace("#define", "").Replace(" ", "").Replace("\t", "");
                    if (!buf.Contains(arrayItemNames[i]))
                        continue;

                    string subbuf = "";
                    foreach (char ch in buf)
                    {
                        if (ch == '(')
                            break;

                        subbuf += ch;
                    }

                    if (subbuf != arrayItemNames[i])
                        continue;

                    startNum = 0;
                    finNum = 0;
                    for (int j = 0, jMax = buf.Length; j < jMax; j++)
                    {
                        if (buf[j] == ')')
                        {
                            finNum = j;
                            break;
                        }
                        if (buf[j] == '(')
                            startNum = j;
                    }
                    arrayOldPidNumbers[i] = buf.Substring(startNum + 1, ((finNum - startNum) - 1) > 0 ? ((finNum - startNum) - 1) : 1);
                }
                i++;
            }            
            
            string[] fileNames = Directory.GetFiles(path + "maps");

            for (int k = 0; k < fileNames.Length; k++)
            {
                fileNames[k] = fileNames[k].Replace(path + "maps\\", "");
                if (!fileNames[k].Contains(".fomap"))
                    continue;
                MapFiles map = new MapFiles(fileNames[k], arrayNewPidNumbers, arrayOldPidNumbers, arrayItemNames);
                map.setNewPidItemInMap();
                map.writeFile();
            }
        }

        private void currentDialogToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (dlgName == "")
            {
                MessageBox.Show("Диалог не выбран. Нужно вывести список диалогов и выбрать нужный");
                return;
            }

            if (!mapName.Contains(".fodlg"))
            {
                MessageBox.Show("Выбраный элемент не является диалогом");
                return;
            }

            DialogFiles dialog = new DialogFiles(dlgName, NewItemPidPath.Text);
            dialog.setNewPid();
            dialog.writeFile();
        }

        private void allDialogsToolStripMenuItem_Click(object sender, EventArgs e)
        {

            string[] arrayItemNames;
            string[] arrayNewPidNumbers;
            string[] arrayOldPidNumbers;
            ReadFileInArray new_itempid;
            new_itempid = new ReadFileInArray(NewItemPidPath.Text);
            ReadFileInArray oldItemsName;
            oldItemsName = new ReadFileInArray("old_itempid.fos");
            List<string> NewListOfStrings = getListOfStrings(new_itempid.arrayListOfStrings);
            List<string> OldListOfStrings = getListOfStrings(oldItemsName.arrayListOfStrings);

            arrayItemNames = new string[NewListOfStrings.Count];
            arrayNewPidNumbers = new string[NewListOfStrings.Count];
            arrayOldPidNumbers = new string[NewListOfStrings.Count];

            int i = 0;
            foreach (string str in NewListOfStrings)
            {
                string buf = str.Replace("#define", "").Replace(" ", "").Replace("\t", "");
                int startNum = 0;
                int finNum = 0;
                for (int j = 0, jMax = buf.Length; j < jMax; j++)
                {
                    if (buf[j] == ')')
                    {
                        finNum = j;
                        break;
                    }
                    if (buf[j] == '(')
                        startNum = j;
                }

                arrayItemNames[i] += buf.Substring(0, startNum);
                arrayNewPidNumbers[i] += buf.Substring(startNum + 1, ((finNum - startNum) - 1) > 0 ? ((finNum - startNum) - 1) : 1);

                arrayOldPidNumbers[i] = "-1";
                foreach (string oldStr in OldListOfStrings)
                {
                    buf = oldStr.Replace("#define", "").Replace(" ", "").Replace("\t", "");
                    if (!buf.Contains(arrayItemNames[i]))
                        continue;

                    string subbuf = "";
                    foreach (char ch in buf)
                    {
                        if (ch == '(')
                            break;

                        subbuf += ch;
                    }

                    if (subbuf != arrayItemNames[i])
                        continue;

                    startNum = 0;
                    finNum = 0;
                    for (int j = 0, jMax = buf.Length; j < jMax; j++)
                    {
                        if (buf[j] == ')')
                        {
                            finNum = j;
                            break;
                        }
                        if (buf[j] == '(')
                            startNum = j;
                    }
                    arrayOldPidNumbers[i] = buf.Substring(startNum + 1, ((finNum - startNum) - 1) > 0 ? ((finNum - startNum) - 1) : 1);
                }
                i++;
            }             
            
            string[] fileNames = Directory.GetFiles(path + "dialogs");

            for (int k = 0; k < fileNames.Length; k++)
            {
                fileNames[k] = fileNames[k].Replace(path + "dialogs\\", "");
                if (!fileNames[k].Contains(".fodlg"))
                    continue;
                DialogFiles dialog = new DialogFiles(fileNames[k], arrayNewPidNumbers, arrayOldPidNumbers, arrayItemNames);
                dialog.setNewPid();
                dialog.writeFile();
            }
        }

        private void CheckAll_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            List<int> num = new List<int>();

            reservedConstToolStripMenuItem_Click(sender, e);
            listBox1.Items.Add("Проверка дублей номеров прототипов");
            FilesItemInfo filesItemInfo = new FilesItemInfo("temp" ,NewItemPidPath.Text);
            for (int j = 0; j < filesItemInfo.arrayNewPidNumbers.Length; j++)
                for (int i = 0; i < filesItemInfo.arrayNewPidNumbers.Length; i++)
                    if (filesItemInfo.arrayNewPidNumbers[i] == filesItemInfo.arrayNewPidNumbers[j] && i>j)
                    {
                        if (filesItemInfo.arrayItemNames[i] == filesItemInfo.arrayItemNames[j])
                        {

                            if (num.Contains(j))
                                continue;

                            num.Add(j);
                            num.Add(i);

                            listBox1.Items.Add("Ошибка! Найден дубль именованых констант: " + filesItemInfo.arrayItemNames[i] + " и " + filesItemInfo.arrayItemNames[j]);
                            continue;
                        }
                        listBox1.Items.Add("Ошибка! Совпадения номеров прототипов для " + filesItemInfo.arrayItemNames[i] + " и " + filesItemInfo.arrayItemNames[j]);
                    }

            listBox1.Items.Add("---------------------------------------");
            listBox1.Items.Add("Проверка соответствий новых и старых именованых констант");
            listBox1.Items.Add("");
            bool isFail = false;
            for (int j = 0; j < filesItemInfo.arrayOldPidNumbers.Length; j++)
                if (filesItemInfo.arrayOldPidNumbers[j] == "-1")
                {
                    listBox1.Items.Add("Ошибка! Именованая константа: " + filesItemInfo.arrayItemNames[j] + " отсутствует в старом файле именованых коснтант.");
                    listBox1.Items.Add("Убедитесь что такая константа есть в стром файле прототипов и написана без ошибок, иначе её не с чем будет сравнивать.");
                    isFail = true;
                }

            if(!isFail)
                listBox1.Items.Add("Ошибок не найдено.");
            
            if(checkedTextFile("russ"))
                listBox1.Items.Add("Ошибок не найдено");
            if (checkedTextFile("engl"))
                listBox1.Items.Add("Ошибок не найдено");            

            checkedProtoFile("armor.fopro");
            checkedProtoFile("weapon.fopro");
            checkedProtoFile("ammo.fopro");
            checkedProtoFile("drug.fopro");
            checkedProtoFile("key.fopro");
            checkedProtoFile("misc.fopro");
            checkedProtoFile("car.fopro");
            checkedProtoFile("container.fopro");
            checkedProtoFile("door.fopro");
            checkedProtoFile("grid.fopro");
            checkedProtoFile("wall.fopro");
            checkedProtoFile("generic.fopro");


            // Запис знайдених рядків
            StreamWriter file = new StreamWriter(new FileStream("log.txt", FileMode.OpenOrCreate), Encoding.Default);
            foreach (string str in listBox1.Items)
                file.WriteLine(str);
            file.Close();

            listBox1.Items.Add("Отчет сохранен в log.txt");
        }

        bool checkedTextFile(string Language)
        {
            List<int> num = new List<int>();
            listBox1.Items.Add("---------------------------------------");
            listBox1.Items.Add("Проверка дублей номеров строк " + Language + "/FOOBJ.MSG");
            listBox1.Items.Add("");            
            bool result = true;
            TxtFoobj txtFoobj = new TxtFoobj(Language, NewItemPidPath.Text);
            for (int i = 0; i < txtFoobj.file.arrayListOfStrings.Length; i++)
            {
                if (txtFoobj.file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (txtFoobj.file.arrayListOfStrings[i][0] != '{')
                    continue;

                for (int j = 0; j < txtFoobj.arrayOldPidNumbers.Length; j++)
                {
                    if (txtFoobj.file.arrayListOfStrings[j].Length < 1)
                        continue;

                    if (txtFoobj.file.arrayListOfStrings[j][0] != '{')
                        continue;

                    if (txtFoobj.getNum(txtFoobj.file.arrayListOfStrings[j]) == txtFoobj.getNum(txtFoobj.file.arrayListOfStrings[i]) && i!=j)
                    {
                        if (num.Contains(j))
                            continue;

                        result = false;
                        num.Add(j);
                        num.Add(i);
                        listBox1.Items.Add("Внимание! Совпадение номеров строк:");
                        listBox1.Items.Add(txtFoobj.file.arrayListOfStrings[j]);
                        listBox1.Items.Add(txtFoobj.file.arrayListOfStrings[i]);
                        listBox1.Items.Add("");
                    }
                }
            }
           return result;      
        }

        void checkedProtoFile(string fileName)
        {
            listBox1.Items.Add("---------------------------------------");
            listBox1.Items.Add(""); 
            List<string> result = new List<string>();

            listBox1.Items.Add("Проверка " + fileName);
            ProtoItemFiles prItfiles = new ProtoItemFiles(fileName, NewItemPidPath.Text);
            result = prItfiles.verifyTheAbsenceOfPids();

            if (result.Count < 1)
            {
                listBox1.Items.Add("Ошибок не найдено.");
            }
            else
            {
                listBox1.Items.Add("Внимание! Данные номера прототипов отсутствуют в старом списке именованых констант:");
                foreach (string str in result)
                    listBox1.Items.Add(str);
                listBox1.Items.Add("Это может привести к дублированию номеров прототипов.");
                listBox1.Items.Add("Рекомендуется либо добавить именованые константы, для этих прототипов, в старый и новый _itempid.fos,");
                listBox1.Items.Add("либо убедится в отсутствии таких номеров в новом _itempid.fos");
                foreach (string str in result)
                    foreach (string subStr in prItfiles.arrayNewPidNumbers)
                        if(str==subStr) 
                            listBox1.Items.Add("Обратите внимание! Этот занятый номер вы зарезервировали в новом _itempid.fos: "+str);

            }
        }

        private void fOOBJMSGToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (checkedTextFile("russ"))
                listBox1.Items.Add("Ошибок не найдено");
        }

        private void englFOOBJMSGToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (checkedTextFile("engl"))
                listBox1.Items.Add("Ошибок не найдено");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ItemNamesLst itLst = new ItemNamesLst(NewItemPidPath.Text);
            itLst.SetNewItemList();
            for (int i = 0; i < itLst.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itLst.file.arrayListOfStrings[i]);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ItemPidsNumber itPidsNum = new ItemPidsNumber(NewItemPidPath.Text);
            itPidsNum.SetNewPidsNumber();
            for (int i = 0; i < itPidsNum.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(itPidsNum.file.arrayListOfStrings[i]);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("russ", NewItemPidPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            TxtFoobj txtFj = new TxtFoobj("engl", NewItemPidPath.Text);
            txtFj.SetNewText();
            for (int i = 0; i < txtFj.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(txtFj.file.arrayListOfStrings[i]);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();

            fillProtoText("armor.fopro");
            /*fillProtoText("weapon.fopro");
            fillProtoText("ammo.fopro");
            fillProtoText("drug.fopro");
            fillProtoText("key.fopro");
            fillProtoText("misc.fopro");
            fillProtoText("car.fopro");
            fillProtoText("container.fopro");
            fillProtoText("door.fopro");
            fillProtoText("grid.fopro");
            fillProtoText("wall.fopro");
            fillProtoText("generic.fopro");*/
        }

        void fillProtoText(string name)
        {
            listBox1.Items.Add(name);
            listBox1.Items.Add("---------------------------------------");
            ProtoItemFiles prItfiles = new ProtoItemFiles(name, NewItemPidPath.Text);
            prItfiles.setNewProto();
            for (int i = 0; i < prItfiles.file.arrayListOfStrings.Length; i++)
                listBox1.Items.Add(prItfiles.file.arrayListOfStrings[i]);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox1.Items.Add("Старый пид" + "\t" + "Новый пид" + "\t" + "Именованая константа");
            listBox1.Items.Add("________________________________________________________________________");
            FilesItemInfo fItemInfo = new FilesItemInfo("\\scripts\\_itempid.fos", NewItemPidPath.Text);
            for (int i = 0; i < fItemInfo.arrayItemNames.Length; i++)
                listBox1.Items.Add("|\t" + fItemInfo.arrayOldPidNumbers[i] + "\t|\t" + fItemInfo.arrayNewPidNumbers[i] + "\t| " + fItemInfo.arrayItemNames[i]);            
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru/");
        }

        private void button7_Click(object sender, EventArgs e)
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

        private void button8_Click(object sender, EventArgs e)
        {
            string[] fileNames = Directory.GetFiles(path + "dialogs");

            for (int i = 0; i < fileNames.Length; i++)
            {
                fileNames[i] = fileNames[i].Replace(path + "dialogs\\", "");
            }

            listBox1.Items.Clear();
            foreach (string item in fileNames)
            {
                listBox1.Items.Add(item);
            }
        }

        private void ConvertAll_Click(object sender, EventArgs e)
        {
            itemNameslstToolStripMenuItem_Click(sender, e);
            itempidfosToolStripMenuItem_Click(sender, e);
            russFoobjmsgToolStripMenuItem_Click(sender, e);
            englFoobjmsgToolStripMenuItem_Click(sender, e);
            allProtoToolStripMenuItem_Click(sender, e);
            allMapToolStripMenuItem_Click(sender, e);
            allDialogsToolStripMenuItem_Click(sender, e);
            ammoInProtoToolStripMenuItem_Click(sender, e);
            childItemToolStripMenuItem_Click(sender, e);
            effectInProtoToolStripMenuItem_Click(sender, e);

        }
           
        private void armorfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
             checkedProtoFile("armor.fopro");
        }

        private void weaponfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("weapon.fopro");
        }

        private void ammofoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("ammo.fopro");
        }

        private void drugfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("drug.fopro");
        }

        private void keyfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("key.fopro");
        }

        private void miscfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("misc.fopro");
        }

        private void carfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
             checkedProtoFile("car.fopro");
        }

        private void containerfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("container.fopro");
        }

        private void doorfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("door.fopro");
        }

        private void genericfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
           checkedProtoFile("generic.fopro");
        }

        private void gridfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("grid.fopro");
        }

        private void wallfoproToolStripMenuItem_Click(object sender, EventArgs e)
        {
            checkedProtoFile("wall.fopro");
        }

        void ProtoPidsGenerate(string name)
        {
            listBox1.Items.Clear();
            List<string> result = new List<string>();
            ProtoItemFiles prItfiles = new ProtoItemFiles(name, NewItemPidPath.Text);
            result = prItfiles.GetPids();

            if (result.Count < 1)
            {
                listBox1.Items.Add("В файле нет прототипов!");
                return;
            }

            StreamWriter file = new StreamWriter(new FileStream("PID_" + name.Replace(".fopro", "").ToUpper() + ".txt", FileMode.Create), Encoding.Default);
            listBox1.Items.Add("Генерация именованых констант с "+name);
            file.WriteLine("//" + name);
            for (int i = 0; i < result.Count; i++)
            {
                listBox1.Items.Add("#define " + "PID_" + name.Replace(".fopro", "").ToUpper() + "_" + (i + 1) + "\t\t\t\t(" + result[i] + ")");
                file.WriteLine("#define " + "PID_" + name.Replace(".fopro", "").ToUpper() + "_" + (i + 1) + "\t\t\t\t(" + result[i] + ")");
            }

            file.Close();
                
            listBox1.Items.Add("");
             foreach (string str in result)
                 foreach (string subStr in prItfiles.arrayNewPidNumbers)
                     if (str == subStr)
                          listBox1.Items.Add("Обратите внимание! Этот занятый номер вы зарезервировали в новом _itempid.fos: " + str);

        }

        private void doorfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("door.fopro");
        }

        private void containerfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("container.fopro");
        }

        private void genericfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("generic.fopro");
        }

        private void gridfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("grid.fopro");
        }

        private void wallfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("wall.fopro");        
        }

        private void armorfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("armor.fopro");
        }

        private void weaponfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("weapon.fopro");
        }

        private void ammofoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("ammo.fopro");        
        }

        private void drugfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("drug.fopro"); 
        }

        private void keyfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("key.fopro");         
        }

        private void miscfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("misc.fopro");         
        }

        private void carfoproToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            ProtoPidsGenerate("car.fopro");          
        }

        private void reservedConstToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox1.Items.Add("---------------------------------------");
            listBox1.Items.Add("Прверка отсутствия зарезерированых значений констант");
            listBox1.Items.Add("Новый файл прототипов");
            bool isFail = false;
            FilesItemInfo filesItemInfo = new FilesItemInfo("temp" ,NewItemPidPath.Text);            
            foreach (string str in filesItemInfo.arrayNewPidNumbers)
	        {
                int pid = Convert.ToInt32(str);
                if (pid == 41 ||
                    (pid >= 1000 && pid <= 1100) || pid == 2049 ||
                    pid == 2067 || pid == 2141 || pid == 3852 ||
                    pid == 3853 || pid == 4012 || (pid >= 4016 && pid <= 4023) ||
                    (pid >= 4031 && pid <= 4046) || pid == 5621 || pid == 5622)
                    {
                        isFail=true;
                        listBox1.Items.Add("Данный номер константы зарезервирован. Его нельзя использовать: "+ str);    
                    }
	        }
            listBox1.Items.Add("Старый файл прототипов");
            foreach (string str in filesItemInfo.arrayOldPidNumbers)
            {
                int pid = Convert.ToInt32(str);
                if (pid == 41 ||
                    (pid >= 1000 && pid <= 1100) || pid == 2049 ||
                    pid == 2067 || pid == 2141 || pid == 3852 ||
                    pid == 3853 || pid == 4012 || (pid >= 4016 && pid <= 4023) ||
                    (pid >= 4031 && pid <= 4046) || pid == 5621 || pid == 5622)
                {
                    isFail = true;
                    listBox1.Items.Add("Данный номер константы зарезервирован. Его нельзя использовать: " + str);
                }
            }
            if(isFail)
            {
                listBox1.Items.Add("Убедитесь что ваши новые номера прототипов не имеют и на заменяют значения:");
                listBox1.Items.Add("1000-1100, 2049, 2067, 2141, 3852, 3853, 4012, 4016-4023, 4031-4046, 5621, 5622");
                listBox1.Items.Add("Данные прототипы зарезервированы для триггеров, энтайров, сеток выхода, рукопашных ударов и т. п.");
            }

        }

        private void ammoInProtoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProtoWeaponDefAmmo prItfiles = new ProtoWeaponDefAmmo("weapon.fopro", NewItemPidPath.Text);
            prItfiles.setNewAmmoPid();
            prItfiles.writeFile();
        }

        private void childItemToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProtoChildItem prItfiles = new ProtoChildItem("car.fopro", NewItemPidPath.Text);
            prItfiles.setNewChildPid();
            prItfiles.writeFile();
            prItfiles = new ProtoChildItem("misc.fopro", NewItemPidPath.Text);
            prItfiles.setNewChildPid();
            prItfiles.writeFile();
        }

        private void effectInProtoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ProtoWeaponEffect prItfiles = new ProtoWeaponEffect("weapon.fopro", NewItemPidPath.Text);
            prItfiles.setNewEffect();
            prItfiles.writeFile();
        }
    }
}