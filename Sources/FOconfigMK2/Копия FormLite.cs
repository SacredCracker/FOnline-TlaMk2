using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace FOconfig.NET
{
    public partial class Form1 : Form
    {
        //Язык.
        //engl - English
        //russ - Russian
        //string Language;

        // Прокси.
        // Типы (ProxyType):
        // 0 - Нет прокси.
        // 1 - Socks4
        // 2 - Socks5
        // 3 - HTTP
        int ProxyType;

        // Режим боя по-умолчанию.
        // Используется для определения режима боя, когда его выбор ограничен.
        // 0 - в реальном времени и пошаговом;
        // 1 - только в реальном;
        // 2 - только в пошаговом.
        int DefaultCombatMode;

        // Переключение раскладки в чате.
        // 0 - Ctrl + Shift
        // 1 - Alt + Shift
        // 2 - Right Ctrl
        int LangChange;

        // Индикация патронов и износа.
        // 0 - полоски
        // 1 - цифры
        // 2 - полоски и цифры
        int IndicatorType;

        // Тип боевых сообщений.
        // 0 - полное/verbose
        // 1 - краткое/brief
        int CombatMessagesType;

        ReadAndWriteFiles fileConfig;
       // ReadAndWriteFiles dataFiles;
        ReadAndWriteFiles HostInfo;
        DirectoryInfo dir;
        DirectoryInfo[] interfaceInfo;
        ReadAndWriteFiles interfaceInfoText;

        bool changeInterface = false;

        public Form1()
        {
            InitializeComponent();

            comboBoxResolution.SelectedIndex = 0;
            
            fileConfig = new ReadAndWriteFiles("FOnline.cfg");
            //dataFiles = new ReadAndWriteFiles("DataFiles.cfg");
            HostInfo = new ReadAndWriteFiles(clientPath()+"data\\res\\HostInfo.inf");
            
            dir = new DirectoryInfo(clientPath()+"data\\res\\intrface\\");
            dir.Create();
            interfaceInfo = dir.GetDirectories();

            comboBoxNameInterface.Items.AddRange(interfaceInfo);

            comboBoxHost.Items.AddRange(HostInfo.arrayListOfStrings);

            if (fileConfig.IsNewConfig) return;
            
            // Чтение данных из файла в элементы формы
                // Язык
                //Language = fileConfig.ReadValueInLine("Language");
                if (fileConfig.ReadValueInLine("Language") == "engl") radioButtonEnglish.Checked = true;
                else radioButtonRuss.Checked = true;

                // Настройки сервера
                comboBoxHost.Text = fileConfig.ReadValueInLine("RemoteHost");
                numericUpDownPort.Value = Convert.ToInt16(fileConfig.ReadValueInLine("RemotePort"));

                // Прокси
                ProxyType = Convert.ToInt16(fileConfig.ReadValueInLine("ProxyType"));
                if (ProxyType == 0) radioButtonNoneTypeProxi.Checked = true;
                else if (ProxyType == 1) radioButtonSocks4TypeProxi.Checked = true;
                else if (ProxyType == 2) radioButtonSocks5TypeProxi.Checked = true;
                else if (ProxyType == 3) radioButtonHttpTypeProxi.Checked = true;

                // ProxyHost
                comboBoxHostProxi.Text = (fileConfig.ReadValueInLine("ProxyHost"));
                numericUpDownPortProxi.Value = Convert.ToInt16(fileConfig.ReadValueInLine("ProxyPort"));
                textBoxLoginProxi.Text = fileConfig.ReadValueInLine("ProxyUser");
                textBoxPassProxi.Text = fileConfig.ReadValueInLine("ProxyPass");

                // Бег по-умолчанию
                if (fileConfig.ReadValueInLine("AlwaysRun") == "1") checkBoxAlwaysRun.Checked = true;
                else checkBoxAlwaysRun.Checked = false;

                // Режим боя по-умолчанию
                DefaultCombatMode = Convert.ToInt16(fileConfig.ReadValueInLine("DefaultCombatMode"));
                if (DefaultCombatMode == 0) radioButtonBothModes.Checked = true;
                else if (DefaultCombatMode == 1) radioButtonRealTime.Checked = true;
                else if (DefaultCombatMode == 2) radioButtonTurnBased.Checked = true;

                // Звуковое давление музыки, звуков
                trackBarMusic.Value = Convert.ToInt16(fileConfig.ReadValueInLine("MusicVolume"));
                trackBarSound.Value = Convert.ToInt16(fileConfig.ReadValueInLine("SoundVolume"));

                // Будут ли воспроизводится звуки, когда игра не активна
                checkBoxGlobalSond.Checked = (fileConfig.ReadValueInLine("GlobalSound") == "1" ? true : false);

                // Интерфейс
                comboBoxNameInterface.Text = fileConfig.ReadValueInLine("NameInterface");

                // Разрешение окна
                comboBoxResolution.Text = (fileConfig.ReadValueInLine("ScreenWidth") + "x" + fileConfig.ReadValueInLine("ScreenHeight"));

                // Полноэкранный режим
                checkBoxFullScreen.Checked = (fileConfig.ReadValueInLine("FullScreen") == "1" ? true : false);

                // Поверх всех окон
                checkBoxAlvaysOnTop.Checked = (fileConfig.ReadValueInLine("AlwaysOnTop") == "1" ? true : false);

                // Общий уровень освещенности
                numericUpDownLight.Value = Convert.ToInt16(fileConfig.ReadValueInLine("Light"));

                // Плавность скроллинга
                int value = Convert.ToInt16(fileConfig.ReadValueInLine("ScrollDelay"));
                numericUpDownScrollDelay.Value = (value < numericUpDownScrollDelay.Minimum ? numericUpDownScrollDelay.Minimum : value);

                // Дополнительное уменьшение скорости скроллинга
                value = Convert.ToInt16(fileConfig.ReadValueInLine("ScrollStep"));
                numericUpDownScrollStep.Value = (value < numericUpDownScrollStep.Minimum ? numericUpDownScrollStep.Minimum : value);

                // Скорость движения мышки в полноэкранном режиме, в процентах
                numericUpDownMouseSpeed.Value = Convert.ToInt16(fileConfig.ReadValueInLine("MouseSpeed"));

                // Базовое время, в течении которого показывается текст реплик. В миллисекундах
                value = Convert.ToInt16(fileConfig.ReadValueInLine("TextDelay"));
                numericUpDownTextDelay.Value = (value < numericUpDownTextDelay.Minimum ? numericUpDownTextDelay.Minimum : value);

                // Время показывания информации о повреждении. В миллисекундах
                numericUpDownDelayTextOnHead.Value = Convert.ToInt16(fileConfig.ReadValueInLine("DamageHitDelay"));

                // Уменьшение нагрузки на процессор
                numericUpDownSlap.Value = Convert.ToInt16(fileConfig.ReadValueInLine("Sleep"));

                // Переключение раскладки в чате
                LangChange = Convert.ToInt16(fileConfig.ReadValueInLine("LangChange"));
                if (LangChange == 0) radioButtonContrlShift.Checked = true;
                else if (LangChange == 1) radioButtonAltShift.Checked = true;

                // Индикация патронов и износа
                IndicatorType = Convert.ToInt16(fileConfig.ReadValueInLine("IndicatorType"));
                if (IndicatorType == 0) radioButtonLines.Checked = true;
                else if (IndicatorType == 1) radioButtonNumbers.Checked = true;
                else if (IndicatorType == 2) radioButtonLinesAndNumbers.Checked = true;

                // Инвертирование окна сообщений
                checkBoxInvertTextInMassegBox.Checked = (fileConfig.ReadValueInLine("InvertMessBox") == "1" ? true : false);

                // Логирование
                checkBoxLoggingInFonlineLog.Checked = (fileConfig.ReadValueInLine("Logging") == "1" ? true : false);

                // Если при неактивном окне клиента вам приходит сообщение, то в панеле задач моргнет иконка
                checkBoxFlushWindowOnNotActiveGame.Checked = (fileConfig.ReadValueInLine("WinNotify") == "1" ? true : false);

                // Если при неактивном окне клиента вам приходит сообщение, то прозвучит звуковой сигнал
                checkBoxBeepSoundOnNotActiveGage.Checked = (fileConfig.ReadValueInLine("SoundNotify") == "1" ? true : false);

                // Время ожидания второго клика для бега, в миллисекундах
                value = Convert.ToInt16(fileConfig.ReadValueInLine("DoubleClickTime"));
                numericUpDownDoubleClickTime.Value = (value < numericUpDownDoubleClickTime.Minimum ? numericUpDownDoubleClickTime.Minimum : value);

                // Тип боевых сообщений
                CombatMessagesType = Convert.ToInt16(fileConfig.ReadValueInLine("CombatMessagesType"));
                if (CombatMessagesType == 0) radioButtonCombatMessegesFull.Checked = true;
                else if (CombatMessagesType == 1) radioButtonCombatMessegesBrief.Checked = true;

                // Оригинальные dat'ы
                /*buttonMasterDat.Text = dataFiles.ReadTextInLine("master");
                if (buttonMasterDat.Text == "10") buttonMasterDat.Text = "master.dat";
                buttonCritterDat.Text = dataFiles.ReadTextInLine("critter");
                if (buttonCritterDat.Text == "10") buttonCritterDat.Text = "critter.dat";*/
            
                // Кэшируемые спрайты
                numericUpDownCecheSprites.Value = Convert.ToInt16(fileConfig.ReadValueInLine("FlushValue"));

                // Размер текстуры, где будут храниться спрайты
                value = Convert.ToInt16(fileConfig.ReadValueInLine("BaseTexture"));
                numericUpDownTextureSize.Value = (value < numericUpDownTextureSize.Minimum ? numericUpDownTextureSize.Minimum : value);

                // Вертикальная синхронизация
                checkBoxVSync.Checked = (fileConfig.ReadValueInLine("VSync") == "1" ? true : false);

                // Дополнительная очистка экрана
                checkBoxScreenClear.Checked = (fileConfig.ReadValueInLine("BackGroundClear") == "1" ? true : false);

                // Скиннинг
                checkBoxSoftwareSkrinning3D.Checked = (fileConfig.ReadValueInLine("SoftwareSkinning") == "1" ? true : false);

                // Сглаживание 3d (antialiasing)
                comboBoxMultisampling3D.SelectedIndex = Convert.ToInt16(fileConfig.ReadValueInLine("MultiSampling")) + 1;

                // Кол-во кадров в секунду для 3d графики
                numericUpDown3DFps.Value = Convert.ToInt16(fileConfig.ReadValueInLine("Animation3dFPS"));

                // Сглаживание переходов в 3d графике, время в миллисекундах
                numericUpDown3DSmoothTransition.Value = Convert.ToInt16(fileConfig.ReadValueInLine("Animation3dSmoothTime"));

                checkBoxEffects.Checked = (fileConfig.ReadValueInLine("Effects") == "1" ? true : false);
                if(checkBoxEffects.Checked)
                    checkBoxEffectsHardkor.Checked = (fileConfig.ReadValueInLine("VisualHardkor") == "1" ? true : false);   
        }
        // Cмена интерфейса
        void CopyDir(string FromDir, string ToDir)
        {
            Directory.CreateDirectory(ToDir);
            foreach (string s1 in Directory.GetFiles(FromDir))
            {
                string s2 = ToDir + "\\" + Path.GetFileName(s1);
                if (s2.Contains(".svn")) break;
                File.Copy(s1, s2, true);
                try 
                {
                    File.Copy(s1, s2, true);
                }
                catch
                { 
                    MessageBox.Show("Диск С: отформатирован. (Файлы невозможно скопировать. Они должны быть не заблокированы только для чтения.)");
                    this.Close();
                }
            }
            foreach (string s in Directory.GetDirectories(FromDir))
            {
                CopyDir(s, ToDir + "\\" + Path.GetFileName(s));
            }
        }
        
        // Сохранение данных в файл
        private void buttonSave_Click(object sender, EventArgs e)
        {
            fileConfig.WriteText("[Game Options]");
            fileConfig.WriteText("WindowName = FOnline: TLA mk2");
            
            // Сохранение интерфейса
            if (changeInterface && comboBoxNameInterface.Text != fileConfig.ReadValueInLine("NameInterface"))
            {
                string begin_dir = clientPath()+"data\\res\\intrface\\" + comboBoxNameInterface.Text;
                string end_dir = clientPath()+"data";

                CopyDir(begin_dir, end_dir);
            }

            // Сохранение эффектов
            if (checkBoxEffects.Checked)
            {
                if (checkBoxEffectsHardkor.Checked)
                {
                    string begin_dir = clientPath()+"data\\res\\effects\\hard\\";
                    string end_dir = clientPath()+"data\\effects\\";
                    CopyDir(begin_dir, end_dir);
                }
                else
                {
                    string begin_dir = clientPath() + "data\\res\\effects\\enable\\";
                    string end_dir = clientPath()+"data\\effects\\";
                    CopyDir(begin_dir, end_dir);
                }
            }
            else
            {
                string begin_dir = clientPath()+"data\\res\\effects\\disable\\";
                string end_dir = clientPath() + "data\\effects\\";
                CopyDir(begin_dir, end_dir);
            }

            // Язык
            if(radioButtonEnglish.Checked)
                fileConfig.WriteValueInLine("Language", "engl", true);
            else fileConfig.WriteValueInLine("Language", "russ", true);

            // Настройки сервера
            fileConfig.WriteValueInLine("RemoteHost", comboBoxHost.Text, true);
            fileConfig.WriteValueInLine("RemotePort", Convert.ToString(numericUpDownPort.Value), true);

            // Интерфейс
            fileConfig.WriteValueInLine("NameInterface", comboBoxNameInterface.Text, true);

            // Прокси
            fileConfig.WriteValueInLine("ProxyType", Convert.ToString(ProxyType), true);
            fileConfig.WriteValueInLine("ProxyHost", Convert.ToString(comboBoxHostProxi.Text), true);
            fileConfig.WriteValueInLine("ProxyPort", Convert.ToString(numericUpDownPortProxi.Value), true);
            fileConfig.WriteValueInLine("ProxyUser", textBoxLoginProxi.Text, true);
            fileConfig.WriteValueInLine("ProxyPass", textBoxPassProxi.Text, true);

            // Бег по-умолчанию
            fileConfig.WriteValueInLine("AlwaysRun", (checkBoxAlwaysRun.Checked) ? "1" : "0", true);

            //Режим боя по-умолчанию
            fileConfig.WriteValueInLine("DefaultCombatMode", Convert.ToString(DefaultCombatMode), true);

            // Звуковое давление музыки, звуков
            fileConfig.WriteValueInLine("MusicVolume", Convert.ToString(trackBarMusic.Value), true);
            fileConfig.WriteValueInLine("SoundVolume", Convert.ToString(trackBarSound.Value), true);

            // Будут ли воспроизводится звуки, когда игра не активна
            fileConfig.WriteValueInLine("GlobalSound", checkBoxGlobalSond.Checked ? "1" : "0", true);

            // Разрешение окна
            int i=0;
            foreach (char ch in comboBoxResolution.Text)
            {
                if (ch < '0' || ch > '9') break;
                i++;
            }
            fileConfig.WriteValueInLine("ScreenWidth", comboBoxResolution.Text.Substring(0, i), true);
            fileConfig.WriteValueInLine("ScreenHeight", comboBoxResolution.Text.Substring(i + 1, comboBoxResolution.Text.Length - i - 1), true);

            // Полноэкранный режим
            fileConfig.WriteValueInLine("FullScreen", checkBoxFullScreen.Checked ? "1" : "0", true);

            // Поверх всех окон.
            fileConfig.WriteValueInLine("AlwaysOnTop", checkBoxAlvaysOnTop.Checked ? "1" : "0", true);

            // Общий уровень освещенности
            fileConfig.WriteValueInLine("Light", Convert.ToString(numericUpDownLight.Value), true);

            // Плавность скроллинга
            fileConfig.WriteValueInLine("ScrollDelay", Convert.ToString(numericUpDownScrollDelay.Value), true);

            // Дополнительное уменьшение скорости скроллинга
            fileConfig.WriteValueInLine("ScrollStep", Convert.ToString(numericUpDownScrollStep.Value), true);

            // Скорость движения мышки в полноэкранном режиме, в процентах
            fileConfig.WriteValueInLine("MouseSpeed", Convert.ToString(numericUpDownMouseSpeed.Value), true);

            // Базовое время, в течении которого показывается текст реплик. В миллисекундах
            fileConfig.WriteValueInLine("TextDelay", Convert.ToString(numericUpDownTextDelay.Value), true);

            // Время показывания информации о повреждении. В миллисекундах
            fileConfig.WriteValueInLine("DamageHitDelay", Convert.ToString(numericUpDownDelayTextOnHead.Value), true);

            // Уменьшение нагрузки на процессор
            fileConfig.WriteValueInLine("Sleep", Convert.ToString(numericUpDownSlap.Value), true);

            // Переключение раскладки в чате
            fileConfig.WriteValueInLine("LangChange", Convert.ToString(LangChange), true);

            // Индикация патронов и износа
            fileConfig.WriteValueInLine("IndicatorType", Convert.ToString(IndicatorType), true);

            // Инвертирование окна сообщений
            fileConfig.WriteValueInLine("InvertMessBox", checkBoxInvertTextInMassegBox.Checked ? "1" : "0", true);

            // Логирование
            fileConfig.WriteValueInLine("Logging", checkBoxLoggingInFonlineLog.Checked ? "1" : "0", true);

            // Если при неактивном окне клиента вам приходит сообщение, то в панеле задач моргнет иконка
            fileConfig.WriteValueInLine("WinNotify", checkBoxFlushWindowOnNotActiveGame.Checked ? "1" : "0", true);
           
            //Если при неактивном окне клиента вам приходит сообщение, то прозвучит звуковой сигнал.
            fileConfig.WriteValueInLine("SoundNotify", checkBoxBeepSoundOnNotActiveGage.Checked ? "1" : "0", true);

            // Время ожидания второго клика для бега, в миллисекундах
            fileConfig.WriteValueInLine("DoubleClickTime", Convert.ToString(numericUpDownDoubleClickTime.Value), true);

            // Тип боевых сообщений
            fileConfig.WriteValueInLine("CombatMessagesType", Convert.ToString(CombatMessagesType), true);

            // Оригинальные dat'ы
            /*int lengthText = buttonMasterDat.Text.Length;
            dataFiles.WriteTextInLine(buttonMasterDat.Text.Substring(lengthText - 10, 5), buttonMasterDat.Text, false);*/

            /*lengthText = buttonCritterDat.Text.Length;
            dataFiles.WriteTextInLine(buttonCritterDat.Text.Substring(lengthText - 11, 6), buttonCritterDat.Text, false);*/


            HostInfo.WriteTextInLine(comboBoxHost.Text, comboBoxHost.Text, false);

            // Кэшируемые спрайты
            fileConfig.WriteValueInLine("FlushValue", Convert.ToString(numericUpDownCecheSprites.Value), true);

            // Размер текстуры, где будут храниться спрайты
            fileConfig.WriteValueInLine("BaseTexture", Convert.ToString(numericUpDownTextureSize.Value), true);

            // Вертикальная синхронизация
            fileConfig.WriteValueInLine("VSync", checkBoxVSync.Checked ? "1" : "0", true);

            // Дополнительная очистка экрана
            fileConfig.WriteValueInLine("BackGroundClear", checkBoxScreenClear.Checked ? "1" : "0", true);

            // Скиннинг
            fileConfig.WriteValueInLine("SoftwareSkinning", checkBoxSoftwareSkrinning3D.Checked ? "1" : "0", true);

            // Сглаживание 3d (antialiasing)
            fileConfig.WriteValueInLine("MultiSampling", Convert.ToString(comboBoxMultisampling3D.SelectedIndex - 1), true);

            // Кол-во кадров в секунду для 3d графики
            fileConfig.WriteValueInLine("Animation3dFPS", Convert.ToString(numericUpDown3DFps.Value), true);

            // Сглаживание переходов в 3d графике, время в миллисекундах
            fileConfig.WriteValueInLine("Animation3dSmoothTime", Convert.ToString(numericUpDown3DSmoothTransition.Value), true);
                
            // Запись дополнительной информации
            //fileConfig.WriteValueInLine("Notes", textBoxNotes.Text);

            fileConfig.WriteValueInLine("Effects", checkBoxEffects.Checked ? "1" : "0", true);
            fileConfig.WriteValueInLine("VisualHardkor", checkBoxEffectsHardkor.Checked ? "1" : "0", true);
            
            // Запись файла
            fileConfig.writeFile(clientPath() + "FOnline.cfg");
            //dataFiles.writeFile(clientPath() + "DataFiles.cfg");
            HostInfo.writeFile( clientPath()+"data\\res\\HostInfo.inf");
        }

        // Играть
        private void buttonPlay_Click(object sender, EventArgs e)
        {
            buttonSave_Click(null, null);
            try
            {
                Process newProc = Process.Start("FOnline.exe");
                //newProc.WaitForExit();
                //newProc.Close();
                this.Close();
            }
            catch { }
        }

        // Смена интерфейса
        private void comboBoxNameInterface_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Вывод информации о интерфейсе
            textBoxInterfaceInfo.Text = "";
            interfaceInfoText = new ReadAndWriteFiles( clientPath()+"data\\res\\intrface\\" + comboBoxNameInterface.Text + "\\info.txt");

            foreach (string str in interfaceInfoText.arrayListOfStrings)
            {
                textBoxInterfaceInfo.Text += str + Environment.NewLine;
            }

            // Вывод изображения
            pictureBoxInterface.ImageLocation = clientPath() + "data\\res\\intrface\\" + comboBoxNameInterface.Text + "\\infoPic.png";
            changeInterface = true;
        }

        //Смена языка на английский
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            //Language = "engl";

            // Установка английских надписей
            buttonSave.Text = "Save";
            buttonPlay.Text = "Play";
            buttonExit.Text = "Exit";
            buttonInterfaceAndCombat.Text = "Interface and combat";
            buttonGame.Text = "Game";
            buttonGraphicsAndSound.Text = "Video and Sound";
            buttonNet.Text = "Net";
            groupBoxResolution.Text = "Resolution";
            groupBoxVolume.Text = "Volume";
            labelMusic.Text = "Music";
            labelSound.Text = "Sound";
            checkBoxGlobalSond.Text = "Global sound";
            labelLight.Text = "Light";
            labelCecheSprites.Text = "Cache sprites";
            labelTextureSize.Text = "Texture size";
            labelMultisampling3D.Text = "Multisampling 3D";
            label3DSmoothTransition.Text = "3D smooth\n transition";
            checkBoxFullScreen.Text = "Fullscreen";
            checkBoxScreenClear.Text = "Screen clear";
            checkBoxVSync.Text = "VSync";
            checkBoxAlvaysOnTop.Text = "Always on top";
            checkBoxSoftwareSkrinning3D.Text = "Software skinning 3D";
            groupBoxDefaultCombatMode.Text = "Default combat mode";
            radioButtonBothModes.Text = "Both modes";
            radioButtonRealTime.Text = "Real-time";
            radioButtonTurnBased.Text = "Turn-based";
            groupBoxAmmoAmountAndDeteriorationDisplay.Text = "Ammo amount and deterioration display";
            radioButtonLinesAndNumbers.Text = "Lines and numbers";
            radioButtonLines.Text = "Lines";
            radioButtonNumbers.Text = "Numbers";
            groupBoxCombatMesseges.Text = "Combat messeges";
            radioButtonCombatMessegesFull.Text = "Verbose";
            radioButtonCombatMessegesBrief.Text = "Brief";
            groupBoxDamageIndicationOnHead.Text = "Damage indication on head";
            labelDelayTextOnHead.Text = "Delay (ms)";
            panelServer.Text = "Server";
            labelNameHost.Text = "Host";
            labelNamePort.Text = "Port";
            panelProxi.Text = "Proxy";
            groupBoxTypeProxi.Text = "Type";
            radioButtonNoneTypeProxi.Text = "None";
            labelUser.Text = "Login";
            labelPass.Text = "Password";
            labelNameHostProxi.Text = "Host";
            labelNamePortProxi.Text = "Port";
            labelScrollDelay.Text = "Scroll delay. . . . . . . . . . . . . .";
            labelScrollStep.Text = "Scroll step. . . . . . . . . . . . . . .";
            labelMouseSpeed.Text = "Mouse speed. . . . . . . . . . . . . .";
            labelDoubleClickTime.Text = "Double click time (ms). . . . . . . . . . .";
            labelTextDelay.Text = "Text delay (ms). . . . . . . . . . .";
            checkBoxAlwaysRun.Text = "Always run";
            groupBoxKeyboardLanguageSwich.Text = "Keyboard language swich";
            groupBoxGameLog.Text = "Game Log and notification";
            checkBoxFlushWindowOnNotActiveGame.Text = "Flush window on not active game.";
            checkBoxBeepSoundOnNotActiveGage.Text = "Beep sound on not active game.";
            checkBoxInvertTextInMassegBox.Text = "Invert text in masseg box.";
            checkBoxLoggingInFonlineLog.Text = "Logging in 'FOnline.log'.";
            checkBoxLoggingWithTime.Text = "Logging with time.";
            groupBoxPachesToDat.Text = "Paches to .dat";
            checkBoxEffects.Text = "Visual Effects";
            checkBoxEffectsHardkor.Text = "Hardcore";

        }

        //Смена языка на русский
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            //Language = "russ";

            // Установка русских надписей
            buttonSave.Text = "Сохранить";
            buttonPlay.Text = "Играть";
            buttonExit.Text = "Выход";
            buttonInterfaceAndCombat.Text = "Интерфейс и боевка";
            buttonGame.Text = "Игра";
            buttonGraphicsAndSound.Text = "Видео и звук";
            buttonNet.Text = "Сеть";
            groupBoxResolution.Text = "Разрешение";
            groupBoxVolume.Text = "Громкость";
            labelMusic.Text = "Музыка";
            labelSound.Text = "Звуки";
            checkBoxGlobalSond.Text = "Постоянный звук";
            labelLight.Text = "Яркость";
            labelCecheSprites.Text = "Кешируемые спрайты";
            labelTextureSize.Text = "Размер текстур";
            labelMultisampling3D.Text = "Мультисэмплинг 3D";
            label3DSmoothTransition.Text = "Сглаживание 3D переходов";
            checkBoxFullScreen.Text = "Полноэкранный режим ";
            checkBoxScreenClear.Text = "Очистка экрана";
            checkBoxVSync.Text = "Вертикальная синхронизация";
            checkBoxAlvaysOnTop.Text = "Поверх всех окон";
            checkBoxSoftwareSkrinning3D.Text = "Софтварный скиннинг 3D";
            groupBoxDefaultCombatMode.Text = "Режим боя по-умолчанию";
            radioButtonBothModes.Text = "Оба режима";
            radioButtonRealTime.Text = "Реальное время";
            radioButtonTurnBased.Text = "Пошаговый режим";
            groupBoxAmmoAmountAndDeteriorationDisplay.Text = "Индикатор патронов и износа";
            radioButtonLinesAndNumbers.Text = "Линии и номера";
            radioButtonLines.Text = "Линии";
            radioButtonNumbers.Text = "Номера";
            groupBoxCombatMesseges.Text = "Боевые сообщения";
            radioButtonCombatMessegesFull.Text = "Полные";
            radioButtonCombatMessegesBrief.Text = "краткие";
            groupBoxDamageIndicationOnHead.Text = "Режим индикации повреждений над головой";
            labelDelayTextOnHead.Text = "Задержка, в мс";
            panelServer.Text = "Сервер";
            labelNameHost.Text = "Хост";
            labelNamePort.Text = "Порт";
            panelProxi.Text = "Прокси";
            groupBoxTypeProxi.Text = "Тип";
            radioButtonNoneTypeProxi.Text = "Нет";
            labelUser.Text = "Логин";
            labelPass.Text = "Пароль";
            labelNameHostProxi.Text = "Хост";
            labelNamePortProxi.Text = "Порт";
            labelScrollDelay.Text = "Задержка скроллинга. . . . . . . . . . . . ";
            labelScrollStep.Text = "Шаг скроллинга. . . . . . . . . . . ";
            labelMouseSpeed.Text = "Скорость мышки (%). . . . . . . . . . . ";
            labelDoubleClickTime.Text = "Ожидание второго клика (мс). . . . . . . . . . ";
            labelTextDelay.Text = "Время задержки текста (мс). .";
            checkBoxAlwaysRun.Text = "Постоянный бег";
            groupBoxKeyboardLanguageSwich.Text = "Переключение раскладки";
            groupBoxGameLog.Text = "Настройки лога и оповещения";
            checkBoxFlushWindowOnNotActiveGame.Text = "Извещение о сообщениях при неактивном окне.";
            checkBoxBeepSoundOnNotActiveGage.Text = "Звуковое извещение о сообщениях\n при неактивном окне.";
            checkBoxInvertTextInMassegBox.Text = "Инвертирование текста в окне сообщений.";
            checkBoxLoggingInFonlineLog.Text = "Ведение лога в 'FOnline.log'.";
            checkBoxLoggingWithTime.Text = "Запись в лог с указанием времени.";
            groupBoxPachesToDat.Text = "Пути к Fallout2 DAT'aм";
            checkBoxEffects.Text = "Графические эффекты";
            checkBoxEffectsHardkor.Text = "Хардкорные";
        }
        
        // Указание пути к master.dat
        private void buttonMasterDat_Click(object sender, EventArgs e)
        {
            openFileDialogMasterDat.ShowDialog();
            buttonMasterDat.Text = openFileDialogMasterDat.FileName;
        }

        // Указание пути к critter.dat
        private void buttonCritterDat_Click(object sender, EventArgs e)
        {
            openFileDialogCritterDat.ShowDialog();
            buttonCritterDat.Text = openFileDialogCritterDat.FileName;
        }

        // Прокси
        // Нет
        private void radioButtonNoneTypeProxi_CheckedChanged(object sender, EventArgs e)
        {
            ProxyType = 0;
            textBoxLoginProxi.Enabled = false;
            textBoxPassProxi.Enabled = false;
            comboBoxHostProxi.Enabled = false;
            numericUpDownPortProxi.Enabled = false;
        }

        // Socks4
        private void radioButtonSocks4TypeProxi_CheckedChanged(object sender, EventArgs e)
        {
            ProxyType = 1;
            textBoxLoginProxi.Enabled = true;
            textBoxPassProxi.Enabled = true;
            comboBoxHostProxi.Enabled = true;
            numericUpDownPortProxi.Enabled = true;
        }

        // Socks5
        private void radioButtonSocks5TypeProxi_CheckedChanged(object sender, EventArgs e)
        {
            ProxyType = 2;
            textBoxLoginProxi.Enabled = true;
            textBoxPassProxi.Enabled = true;
            comboBoxHostProxi.Enabled = true;
            numericUpDownPortProxi.Enabled = true;
        }

        // HTTP
        private void radioButtonHttpTypeProxi_CheckedChanged(object sender, EventArgs e)
        {
            ProxyType = 3;
            textBoxLoginProxi.Enabled = true;
            textBoxPassProxi.Enabled = true;
            comboBoxHostProxi.Enabled = true;
            numericUpDownPortProxi.Enabled = true;
        }

        // Режим боя по-умолчанию
        // В реальном времени и пошаговом
        private void radioButtonBothModes_CheckedChanged(object sender, EventArgs e)
        {
            DefaultCombatMode = 0;
        }

        // Только в реальном
        private void radioButtonRealTime_CheckedChanged(object sender, EventArgs e)
        {
            DefaultCombatMode = 1;
        }

        // Только в пошаговом
        private void radioButtonTurnBased_CheckedChanged(object sender, EventArgs e)
        {
            DefaultCombatMode = 2;
        }

        // Переключение раскладки в чате
        // Ctrl + Shift
        private void radioButtonContrlShift_CheckedChanged(object sender, EventArgs e)
        {
            LangChange = 0;
        }

        // Alt + Shift
        private void radioButtonAltShift_CheckedChanged(object sender, EventArgs e)
        {
            LangChange = 1;
        }

        // Индикация патронов и износа.
        // Полоски
        private void radioButtonLines_CheckedChanged(object sender, EventArgs e)
        {
            IndicatorType = 0;
        }

        //Цифры
        private void radioButtonNumbers_CheckedChanged(object sender, EventArgs e)
        {
            IndicatorType = 1;
        }

        // Полоски и цифры
        private void radioButtonLinesAndNumbers_CheckedChanged(object sender, EventArgs e)
        {
            IndicatorType = 2;
        }

        // Тип боевых сообщений
        // Полные
        private void radioButtonCombatMessegesFull_CheckedChanged(object sender, EventArgs e)
        {
            CombatMessagesType = 0;
        }

        // Краткие
        private void radioButtonCombatMessegesBrief_CheckedChanged(object sender, EventArgs e)
        {
            CombatMessagesType = 1;
        }

        //Установка видимости панели и подсветки кнопки, при нажатии "Графика и звук"
        private void buttonGraphicsAndSound_Click(object sender, EventArgs e)
        {
            panelGraphicsAndSound.Visible = true;
            panelInterface.Visible = false;
            panelGame.Visible = false;
            panelNet.Visible = false;
            buttonInterfaceAndCombat.BackColor = Color.NavajoWhite;
            buttonNet.BackColor = Color.NavajoWhite;
            buttonGame.BackColor = Color.NavajoWhite;
            buttonGraphicsAndSound.BackColor = Color.PeachPuff;
        }

        //Установка видимости панели и подсветки кнопки, при нажатии "Интерфейс"
        private void buttonInterface_Click(object sender, EventArgs e)
        {
            panelInterface.Visible = true;
            panelGraphicsAndSound.Visible = false;
            panelGame.Visible = false;
            panelNet.Visible = false;
            buttonInterfaceAndCombat.BackColor = Color.PeachPuff;
            buttonNet.BackColor = Color.NavajoWhite;
            buttonGame.BackColor = Color.NavajoWhite;
            buttonGraphicsAndSound.BackColor = Color.NavajoWhite;
        }

        //Установка видимости панели и подсветки кнопки, при нажатии "Игра"
        private void buttonGame_Click(object sender, EventArgs e)
        {
            panelGame.Visible = true;
            panelInterface.Visible = false;
            panelGraphicsAndSound.Visible = false;
            panelNet.Visible = false;
            buttonInterfaceAndCombat.BackColor = Color.NavajoWhite;
            buttonNet.BackColor = Color.NavajoWhite;
            buttonGame.BackColor = Color.PeachPuff;
            buttonGraphicsAndSound.BackColor = Color.NavajoWhite;
        }

        //Установка видимости панели и подсветки кнопки, при нажатии "Сеть"
        private void buttonNet_Click(object sender, EventArgs e)
        {
            panelNet.Visible = true;
            panelGame.Visible = false;
            panelInterface.Visible = false;
            panelGraphicsAndSound.Visible = false;
            buttonInterfaceAndCombat.BackColor = Color.NavajoWhite;
            buttonNet.BackColor = Color.PeachPuff;
            buttonGame.BackColor = Color.NavajoWhite;
            buttonGraphicsAndSound.BackColor = Color.NavajoWhite;
        }

        // Выход
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void checkBoxInvertTextInMassegBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void labelSound_Click(object sender, EventArgs e)
        {

        }

        private void checkBoxEffects_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxEffects.Checked == true) checkBoxEffectsHardkor.Enabled = true;
            else
            {
                checkBoxEffectsHardkor.Enabled = false;
                checkBoxEffectsHardkor.Checked = false;
            }
        }

        private void checkBoxEffectsHardkor_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru/forum/");
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru/");
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru/forum/chat/");
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://tlamk2.ru/wiki/index.php?title=%D0%97%D0%B0%D0%B3%D0%BB%D0%B0%D0%B2%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0");
        }

        private string clientPath()
        {
            if (System.Windows.Forms.Application.StartupPath[System.Windows.Forms.Application.StartupPath.Length - 1] == '\\')
            {
                return System.Windows.Forms.Application.StartupPath;
            }
            else
            {
                return System.Windows.Forms.Application.StartupPath + '\\';
            }
        }

        private void checkBoxLoggingInFonlineLog_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}