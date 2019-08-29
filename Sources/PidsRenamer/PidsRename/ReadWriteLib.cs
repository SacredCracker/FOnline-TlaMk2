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

        public FilesItemInfo(string localPath, string[] arrayNewPidNumbers, string[] arrayOldPidNumbers, string[] arrayItemNames)
        { 
            this.arrayItemNames = arrayItemNames;
            this.arrayNewPidNumbers = arrayNewPidNumbers;
            this.arrayOldPidNumbers = arrayOldPidNumbers;

            ReadFileInArray config = new ReadFileInArray("config.cfg");

            path = config.arrayListOfStrings[0].Replace("ServerPath=", "") + localPath;

            file = new ReadFileInArray(path);
        }        
        
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
                if (!str.Contains("#define") || str.Contains("__ITEM_PID__") || !str.Contains("PID_"))
                    continue;
                ListOfStrings.Add(str);
            }
            return ListOfStrings;
        }

        // Запис в файл
        public void writeFile()
        {
            StreamWriter file = new StreamWriter(new FileStream(path, FileMode.OpenOrCreate), Encoding.Default);
            
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
        string[][] textStruct;
        public TxtFoobj(string Language, string new_itempidPath) : base("\\text\\" + Language + "\\Foobj.msg", new_itempidPath) 
        {     }                

        public string getNum(string str)
        {
            if (str[0] != '{')
                System.Windows.Forms.MessageBox.Show("Строка с номером начинается не с '{'");

             int finIndex = 0;
             for (int j = 0; j < str.Length; j++)
             {
                 if (str[j] != '}')
                    continue;

                    finIndex = j;
                    break;
             }

             str = str.Substring(1, finIndex - 1);
            
            return str;
        }

        public void SetNewText()
        {
            uint count = 0;
            for (int i = 0, iMax = this.file.arrayListOfStrings.Length; i < iMax; i++)
                if (file.arrayListOfStrings[i].Contains("}{}{"))
                    count++;

            for (int i = 0, iMax = this.file.arrayListOfStrings.Length; i < iMax; i++)
                for (int j = 0, jMax = arrayNewPidNumbers.Length; j < jMax; j++)
                {                    
                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "00}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "00}", arrayNewPidNumbers[j] + "00}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "01}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "01}", arrayNewPidNumbers[j] + "01}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "02}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "02}", arrayNewPidNumbers[j] + "02}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "03}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "03}", arrayNewPidNumbers[j] + "03}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "04}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "04}", arrayNewPidNumbers[j] + "04}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "05}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "05}", arrayNewPidNumbers[j] + "05}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "06}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "06}", arrayNewPidNumbers[j] + "06}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "07}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "07}", arrayNewPidNumbers[j] + "07}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "08}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "08}", arrayNewPidNumbers[j] + "08}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "09}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "09}", arrayNewPidNumbers[j] + "09}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "10}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "10}", arrayNewPidNumbers[j] + "10}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "11}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "11}", arrayNewPidNumbers[j] + "11}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "12}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "12}", arrayNewPidNumbers[j] + "12}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "13}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "13}", arrayNewPidNumbers[j] + "13}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "13}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "13}", arrayNewPidNumbers[j] + "13}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "14}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "14}", arrayNewPidNumbers[j] + "14}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "15}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "15}", arrayNewPidNumbers[j] + "15}");
                        break;
                    }

                    if (file.arrayListOfStrings[i].Contains("{" + arrayOldPidNumbers[j] + "16}{}{"))
                    {
                        file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace(arrayOldPidNumbers[j] + "16}", arrayNewPidNumbers[j] + "16}");
                        break;
                    }
                }


            textStruct = new string[count][];
            int textStructIndex = 0;
            for (int i = 0, iMax = this.file.arrayListOfStrings.Length; i < iMax; i++)
                if (file.arrayListOfStrings[i].Contains("}{}{"))
                {
                    textStructIndex++;
                    int j = i;
                    List<string> subTexts = new List<string>();
                    subTexts.Add(getNum(file.arrayListOfStrings[j]));
                    while (j < iMax && (!file.arrayListOfStrings[j].Contains("}{}{") || j == i))
                    {
                        subTexts.Add(file.arrayListOfStrings[j]);
                        j++;
                    }

                    try
                    {
                        textStruct[textStructIndex - 1] = new string[subTexts.Count];
                    }
                    catch
                    { 
                        System.Windows.Forms.MessageBox.Show("textStructIndex-1="+(textStructIndex-1)+"\r"+"textStruct.Length="+textStruct.Length); 
                    }

                    textStruct[textStructIndex - 1][0] = getNum(file.arrayListOfStrings[i]);
                    textStruct[textStructIndex - 1] = subTexts.ToArray();
                }

           // Сортировка
            bool noEnd = true;
            while (noEnd)
            {
                noEnd = false;
                for (int i = 1; i < textStruct.Length; i++)
                    if (Convert.ToInt32(textStruct[i][0]) < Convert.ToInt32(textStruct[i-1][0]))
                    {
                        noEnd = true;
                        string[] buf = textStruct[i-1];
                        textStruct[i - 1] = textStruct[i];
                        textStruct[i] = buf;
                    }
            }


            List<string> list = new List<string>();
            for (int i = 0; i < textStruct.Length; i++)
                for (int j = 1; j < textStruct[i].Length; j++)
                    list.Add(textStruct[i][j]);

            file.arrayListOfStrings = list.ToArray();
        }
    }

    class ProtoChildItem : FilesItemInfo
    {
        public ProtoChildItem(string name, string new_itempidPath)
            : base("\\proto\\items\\" + name, new_itempidPath)
        {
        }

        public void setNewChildPid()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   
                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (!file.arrayListOfStrings[i].Contains("MiscEx.StartVal1"))
                    continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                    if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("MiscEx.StartVal1", "").Replace(" ", ""))
                        continue;

                    file.arrayListOfStrings[i] = "MiscEx.StartVal1=" + arrayNewPidNumbers[j];
                    break;
                }
            }

            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   

                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (!file.arrayListOfStrings[i].Contains("MiscEx.StartVal2"))
                    continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                    if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("MiscEx.StartVal2", "").Replace(" ", ""))
                        continue;

                    file.arrayListOfStrings[i] = "MiscEx.StartVal2=" + arrayNewPidNumbers[j];
                    break;
                }
            }

            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   

                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (!file.arrayListOfStrings[i].Contains("MiscEx.StartVal3"))
                    continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                    if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("MiscEx.StartVal3", "").Replace(" ", ""))
                        continue;

                    file.arrayListOfStrings[i] = "MiscEx.StartVal3=" + arrayNewPidNumbers[j];
                    break;
                }
            }

        }
    }

    class ProtoWeaponDefAmmo : FilesItemInfo
    {
        public ProtoWeaponDefAmmo(string name, string new_itempidPath)
            : base("\\proto\\items\\" + name, new_itempidPath) 
        {
        }

        public void setNewAmmoPid()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   

                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                 if (!file.arrayListOfStrings[i].Contains("Weapon_DefaultAmmoPid"))
                    continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                    if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("Weapon_DefaultAmmoPid", "").Replace(" ", ""))
                        continue;

                    file.arrayListOfStrings[i] = "Weapon_DefaultAmmoPid=" + arrayNewPidNumbers[j];
                    break;
                }
            }
        }
    }

    class ProtoWeaponEffect : FilesItemInfo
    {
        public ProtoWeaponEffect(string name, string new_itempidPath)
            : base("\\proto\\items\\" + name, new_itempidPath) 
        {
        }

        public void setNewEffect()
        {
    
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   

                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (file.arrayListOfStrings[i].Contains("Weapon_Effect_0"))
                {
                    for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                    {
                        if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("Weapon_Effect_0", "").Replace(" ", ""))
                            continue;

                        file.arrayListOfStrings[i] = "Weapon_Effect_0=" + arrayNewPidNumbers[j];
                        break;
                    }
                }
                else if (file.arrayListOfStrings[i].Contains("Weapon_Effect_1"))
                {
                    for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                    {
                        if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("Weapon_Effect_1", "").Replace(" ", ""))
                            continue;

                        file.arrayListOfStrings[i] = "Weapon_Effect_1=" + arrayNewPidNumbers[j];
                        break;
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
        }

        public List<string> GetPids()
        {
            List<string> result = new List<string>();
            foreach (string str in file.arrayListOfStrings)
            {
                if (str.Length < 1)
                    continue;

                if (str[0] != 'P')
                    continue;

                if (!str.Contains("ProtoId") && !str.Contains("Pid"))
                    continue;
               
                result.Add(str.Replace("=", "").Replace("ProtoId", "").Replace("Pid", "").Replace(" ", ""));
            }
            return result;
        }
        
        public List<string> verifyTheAbsenceOfPids()
        {
            List<string> result = new List<string>();

            foreach (string str in file.arrayListOfStrings)
            {
                if (str.Length < 1)
                    continue;

                if (str[0] != 'P')
                    continue;

                if (!str.Contains("ProtoId") && !str.Contains("Pid"))
                     continue;

                bool isAbsence = false;
                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
			    {
                    if (arrayOldPidNumbers[j] != str.Replace("=", "").Replace("ProtoId", "").Replace("Pid", "").Replace(" ", ""))
                        continue;

                    isAbsence = true;
			    }

                if(isAbsence)
                    continue;

                result.Add(str.Replace("=", "").Replace("ProtoId", "").Replace("Pid", "").Replace(" ", ""));
            }

            return result;
        }

        public void setNewProto()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                // Переименование   

                if (file.arrayListOfStrings[i].Length < 1)
                    continue;

                if (file.arrayListOfStrings[i][0] != 'P')
                    continue;

                if (!file.arrayListOfStrings[i].Contains("ProtoId") && !file.arrayListOfStrings[i].Contains("Pid"))
                    continue;

                for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                {
                    if (arrayOldPidNumbers[j] != file.arrayListOfStrings[i].Replace("=", "").Replace("ProtoId", "").Replace("Pid", "").Replace(" ", ""))
                        continue;

                    file.arrayListOfStrings[i] = "ProtoId=" + arrayNewPidNumbers[j];
                    break;
                }
            }
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

        //new MapFiles(fileNames[k], arrayNewPidNumbers, arrayOldPidNumbers, arrayItemNames);
        public MapFiles(string name, string[] arrayNewPidNumbers, string[] arrayOldPidNumbers, string[] arrayItemNames)
            : base("maps\\" + name, arrayNewPidNumbers, arrayOldPidNumbers, arrayItemNames)
        { }

        public void setNewPidItemInMap()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                if (!file.arrayListOfStrings[i].Replace(" ", "").Replace("\t", "").Contains("MapObjType1") && !file.arrayListOfStrings[i].Replace(" ", "").Replace("\t", "").Contains("MapObjType2"))
                    continue;

                 for (int j = 0; j < arrayOldPidNumbers.Length; j++)
                 {
                     if (Convert.ToInt32(file.arrayListOfStrings[i + 1].Replace("ProtoId", "").Replace("Pid", "").Replace("\t", "").Replace(" ", "")) != Convert.ToInt32(arrayOldPidNumbers[j]))
                         continue;

                     file.arrayListOfStrings[i + 1] = file.arrayListOfStrings[i + 1].Replace(arrayOldPidNumbers[j], arrayNewPidNumbers[j]);
                     break;
                 }
            }
        }
    }

    class DialogFiles : FilesItemInfo
    {
        public DialogFiles(string name, string new_itempidPath)
            : base("dialogs\\" + name, new_itempidPath)
        { }

        public DialogFiles(string name, string[] arrayNewPidNumbers, string[] arrayOldPidNumbers, string[] arrayItemNames)
            : base("dialogs\\" + name, arrayNewPidNumbers, arrayOldPidNumbers, arrayItemNames)
        { }

        public void setNewPid()
        {
            for (int i = 0; i < file.arrayListOfStrings.Length; i++)
            {
                if (file.arrayListOfStrings[i].Contains("[russ]"))
                    return;
                
                if (!file.arrayListOfStrings[i].Contains("item p ") && !file.arrayListOfStrings[i].Contains("item n ") )
                    continue;

                for (int j = 0; j < arrayNewPidNumbers.Length; j++)
                {
                    if (!file.arrayListOfStrings[i].Contains("item p " + arrayOldPidNumbers[j]) && !file.arrayListOfStrings[i].Contains("item n " + arrayOldPidNumbers[j]))
                        continue;

                   file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace("item p " + arrayOldPidNumbers[j] + " ", "item p " + arrayItemNames[j] + " ");
                   file.arrayListOfStrings[i] = file.arrayListOfStrings[i].Replace("item n " + arrayOldPidNumbers[j] + " ", "item n " + arrayItemNames[j] + " ");
                }
            }
        }
    }
}