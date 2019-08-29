using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;

namespace PidsRename
{
    class ReadFileInArray
    {
        public string[] arrayListOfStrings;                     // Масив рядків файлу
        public ReadFileInArray(string path)
        {
            //System.Windows.Forms.MessageBox.Show(path);
            StreamReader file = new StreamReader(new FileStream(path, FileMode.OpenOrCreate), Encoding.Default);
            
            string str;
            List<string> ListOfStrings = new List<string>();        //Список рядків файлу
            while ((str = file.ReadLine()) != null) // цикл відбувається доки в файлі є рядки
                ListOfStrings.Add(str);
            arrayListOfStrings = ListOfStrings.ToArray();

            file.Close();
        }
    }
    
    class FilesItemInfo
    {
        public string path;
        public ReadFileInArray file;
        public string[] arrayItemNames;
        public string[] arrayNewPidNumbers;
        public string[] arrayOldPidNumbers;
        public ReadFileInArray new_itempid;

        public FilesItemInfo(string localPath, string new_itempidPath)
        {
            ReadFileInArray config = new ReadFileInArray("config.cfg");

            path = config.arrayListOfStrings[0].Replace("ServerPath=", "") + localPath;

            file = new ReadFileInArray(path);
            new_itempid = new ReadFileInArray(new_itempidPath);
            ReadFileInArray oldItemsName;
            oldItemsName = new ReadFileInArray("old_itempid.fos");

            List<string> NewListOfStrings = getListOfStrings(new_itempid.arrayListOfStrings);
            List<string> OldListOfStrings = getListOfStrings(oldItemsName.arrayListOfStrings);

            arrayItemNames = new string[NewListOfStrings.Count];
            arrayNewPidNumbers = new string[NewListOfStrings.Count];
            arrayOldPidNumbers = new string[NewListOfStrings.Count];
           
            int i=0;
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
                arrayNewPidNumbers[i] += buf.Substring(startNum + 1, ((finNum - startNum) - 1)>0?((finNum - startNum) - 1):1);

               /* string s="";
                foreach (string item in OldListOfStrings)
                {
                    s += item + "\r";
                }
                System.Windows.Forms.MessageBox.Show(s);*/

                arrayOldPidNumbers[i] = "-1";
                foreach (string oldStr in OldListOfStrings)
                {
                    buf = oldStr.Replace("#define", "").Replace(" ", "").Replace("\t", "");
                    if (!buf.Contains(arrayItemNames[i]))
                        continue;

                    string subbuf = "";
                    foreach (char ch in buf)
                    {
                        if(ch=='(')
                            break;

                        subbuf+=ch;
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
        }

        List<string> getListOfStrings(string[] arrayListOfStrings)
        {
            List<string> ListOfStrings = new List<string>();

            foreach (string str in arrayListOfStrings)
            {
                if (!str.Contains("#define") || str.Contains("__ITEM_PID__"))
                    continue;
                ListOfStrings.Add(str);
            }
            return ListOfStrings;
        }

        // Запис в файл
        public void writeFile()
        {
            StreamWriter file = new StreamWriter(new FileStream(path, FileMode.Create));
            
            // Запис знайдених рядків
            foreach (string s in this.file.arrayListOfStrings)
               file.WriteLine(s);

            file.Close();
        }
    }

    class ItemNamesLst : FilesItemInfo
    {
        public ItemNamesLst(string new_itempidPath)
            : base("\\data\\ItemNames.lst", new_itempidPath)
        {
        }

        // Запись новых значений в список пидов
        public void SetNewItemList()
        {            
            string[] arrayListOfStringsNames = new string[file.arrayListOfStrings.Length];
            file.arrayListOfStrings = new string[arrayItemNames.Length];
            string[] curName = arrayItemNames;
            string[] curNum = arrayNewPidNumbers;
            if (curName.Length!=curNum.Length)
                System.Windows.Forms.MessageBox.Show("Ошибка! Количество имен констант не отвечает их констану");

            bool noEnd = true;
            while (noEnd)
            {
                noEnd = false;
                for (int i = 1; i < curName.Length; i++)
                    if (Convert.ToInt32(curNum[i]) < Convert.ToInt32(curNum[i - 1]))
                    {
                        noEnd = true;
                        string buf = curNum[i - 1];
                        curNum[i - 1] = curNum[i];
                        curNum[i] = buf;

                        buf = curName[i - 1];
                        curName[i - 1] = curName[i];
                        curName[i] = buf;
                    }
            }

            for (int i = 0, iMax = file.arrayListOfStrings.Length; i < iMax; i++)
                file.arrayListOfStrings[i] = curNum[i]+" "+curName[i];
        }
    }

    class ItemPidsNumber : FilesItemInfo
    {
        public ItemPidsNumber(string new_itempidPath) : base("\\scripts\\_itempid.fos", new_itempidPath) { }

        public void SetNewPidsNumber()     
        {
            file.arrayListOfStrings = new_itempid.arrayListOfStrings;
        }
    }

    class TxtFoobj : FilesItemInfo
    {
        public TxtFoobj(string Language, string new_itempidPath) : base("\\text\\" + Language + "\\Foobj.msg", new_itempidPath) { }

        public void SetNewText()
        {
                for (int i = 0, iMax = this.file.arrayListOfStrings.Length; i < iMax; i++)
                    for (int j = 0, jMax = arrayItemNames.Length; j < jMax; j++)
                        for (int indexInfo = 0; indexInfo < 5; indexInfo++)
                        {
                            if (!this.file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "0" + indexInfo + "}{}{"))
                                continue;
                            
                                file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace("{" + arrayOldPidNumbers[j] + "0" + indexInfo + "}{}{", "{" + arrayNewPidNumbers[j] + "0" + indexInfo + "}{}{");
                        }

            // Сортировка
            int[] arreyNumbers = new int[file.arrayListOfStrings.Length];
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (file.arrayListOfStrings[i][0]!= '{')
                    continue;

                int finIndex = 0;
                for (int j = 0; j < file.arrayListOfStrings[i].Length; j++)
                {
                    if (file.arrayListOfStrings[i][j] != '}')
                        continue;

                    finIndex = j;
                    break;
                }

                try
                {
                    arreyNumbers[i] = Convert.ToInt32(file.arrayListOfStrings[i].Substring(1, finIndex - 1));
                }
                catch
                {
                    if (finIndex < 2)
                        continue;                       

                    System.Windows.Forms.MessageBox.Show("Выполнение остановлено! Данный номер строки не является числом: " + file.arrayListOfStrings[i].Substring(1, finIndex - 1));
                    return;
                }
               // System.Windows.Forms.MessageBox.Show("Test="+arreyNumbers[i]);
            }

            bool noEnd = true;
            while (noEnd)
            {
                noEnd = false;
                for (int index = 1; index < file.arrayListOfStrings.Length; index++)
                {

                    if (arreyNumbers[index] == 0) continue;

                        if (arreyNumbers[index] < arreyNumbers[index - 1])
                        {
                            noEnd = true;
                            string buf = file.arrayListOfStrings[index - 1];
                            file.arrayListOfStrings[index - 1] = file.arrayListOfStrings[index];
                            file.arrayListOfStrings[index] = buf;

                            int bufNum = arreyNumbers[index - 1];
                            arreyNumbers[index - 1] = arreyNumbers[index];
                            arreyNumbers[index] = bufNum;
                            continue;
                        }

                        
                        if (arreyNumbers[index] == arreyNumbers[index - 1])
                        {
                            System.Windows.Forms.MessageBox.Show("Выполнение остановлено! Два одинаковых номера строки: " + arreyNumbers[index] + " В строке: " + index);
                            return;
                        }
                }
            }
        }
    }

    class ProtoItemFiles : FilesItemInfo
    {
        public ProtoItemFiles(string name, string new_itempidPath)
            : base("\\proto\\items\\" + name, new_itempidPath) 
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование                
                if (!file.arrayListOfStrings[i].Contains("ProtoId"))
                continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                   if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("ProtoId", "").Replace(" ", ""))
                      continue;

                   file.arrayListOfStrings[i] = "ProtoId=" + arrayNewPidNumbers[j];
                }
            }
        }

        public void setNewProto()
        {

        }
    }

    class protoText
    {
        public int pid;
        public string[] text;

        public protoText(int pid, string[] text)
        {
            this.pid = pid;
            this.text = text;
        }
    }

    class MapFiles : FilesItemInfo
    {
        public MapFiles(string name, string new_itempidPath)
            : base("maps\\" + name, new_itempidPath)
        { }

        public void setNewPidItemInMap()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                if (!file.arrayListOfStrings[i].Replace(" ", "").Replace("\t", "").Contains("MapObjType1"))
                    continue;

                 for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                 {
                     if (Convert.ToInt32(file.arrayListOfStrings[i + 1].Replace("ProtoId", "").Replace("\t", "").Replace(" ", "")) != Convert.ToInt32(arrayOldPidNumbers[j]))
                         continue;

                     file.arrayListOfStrings[i + 1] = file.arrayListOfStrings[i + 1].Replace(arrayOldPidNumbers[j], arrayNewPidNumbers[j]);
                 }
            }
        }
    }
}