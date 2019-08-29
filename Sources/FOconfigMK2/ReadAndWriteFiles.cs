using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;

namespace FOconfig.NET
{
    class ReadAndWriteFiles
    {
        public bool IsNewConfig=true;
        string nameFile;                                        //Назву файла
       // int countOfStrings = 0;                               //Кількість рядків
        List<string> ListOfStrings = new List<string>();        //Список рядків файлу
        public string[] arrayListOfStrings;                     // Масив рядків файлу
        public bool noOptimizedSearch = false;

        //Конструктор
        public ReadAndWriteFiles(string nameFile)
        {
            this.nameFile = nameFile;
            
            //Якщо існує файл - зчитати, якщо ні - створити новый.
            StreamReader file = new StreamReader(new FileStream(nameFile, FileMode.OpenOrCreate), Encoding.Default);
 
            string str;
            while ((str = file.ReadLine()) != null) // цикл відбувається доки в файлі є рядки
               if (noOptimizedSearch) ListOfStrings.Add(str); 
               else if (!str.Contains("#") && str != "") //пропуск пустих рядків та коментарів, для підвищення швидкодії
                    ListOfStrings.Add(str); // Доповнює список рядків

            IsNewConfig = ListOfStrings.Count <= 0;
            arrayListOfStrings = ListOfStrings.ToArray();   // конвертує список в масив
            file.Close();                                   // Закриває потік

            ListOfStrings.Clear(); // Очистка списка, так як він буде застосовуватись далі, для незнайдених рядків
         }

        // Знаходить рядок з вказаною послідовністю символів, та зчитує потрібне значення
        public string ReadValueInLine(string str)
        {
            string result = "10";
            for (int i = 0; i < arrayListOfStrings.Length; i++)
                if (arrayListOfStrings[i].Contains(str))
                {
                    result = arrayListOfStrings[i];
                    result = result.Substring(str.Length + 1, result.Length - str.Length - 1);
                }
            return result;
        }

        public string ReadTextInLine(string str)
        {        
            
            string result = "10";
            for (int i = 0; i < arrayListOfStrings.Length; i++)
                if (arrayListOfStrings[i].Contains(str) || arrayListOfStrings[i].Contains(str.ToUpper()))
                    result = arrayListOfStrings[i];
            return result;
        }

        // Знаходить рядок з вказаною послідовністю символів, та дописує передане значення
        public void WriteValueInLine(string str, string value, bool isConfig)
        {
            bool isNotLine = true;
            for (int i = 0; i < arrayListOfStrings.Length; i++)
                if (arrayListOfStrings[i].Contains(str) || arrayListOfStrings[i].Contains(str.ToUpper()))
                {
                    arrayListOfStrings[i] = str + "=" + value;
                    isNotLine = false;
                }

            // Незнайдені рядки додаються в резервний список
            if (isNotLine)
                    ListOfStrings.Add(str + "=" + value);
        }

        public void WriteText(string str)
        {
             for (int i = 0; i < arrayListOfStrings.Length; i++)
                 if (arrayListOfStrings[i].Contains(str) || arrayListOfStrings[i].Contains(str.ToUpper()))
                     return;
             
            ListOfStrings.Add(str);
        }

        public void WriteTextInLine(string str, string value, bool isConfig)
        {
            bool isNotLine = true;
            for (int i = 0; i < arrayListOfStrings.Length; i++)
                if (arrayListOfStrings[i].Contains(str))
                {
                    arrayListOfStrings[i] = value;
                    isNotLine = false;
                }

            // Незнайдені рядки додаються в резервний список
            if (isNotLine)
                ListOfStrings.Add(value);
        }


        // Запис в файл
        public void writeFile(string nameFile)
        {
            StreamWriter file = new StreamWriter(new FileStream(nameFile, FileMode.Create));
            //долучення не знайдених рядків в початок файлу
            foreach (string s in ListOfStrings)
                file.WriteLine(s);
            
            // Запис знайдених рядків
            foreach (string s in arrayListOfStrings)
               file.WriteLine(s);

            ListOfStrings.Clear();
            file.Close();
        }
    }
}
