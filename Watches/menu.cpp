#include "Logical.h"
#include "iostream"
#include <iomanip>
#include <string>
#include <fstream>
#include "conio.h"
#include "User.h"
#include "Watcher.h"
#include "DiveComp.h"
#include "DivingWatches.h"
#include "GTMWatches.h"
#include <sstream>


using namespace std;

map<string, string> lang;
map<string, string> config;

std::string logPath = "logs.txt";
std::string zastavka_path = "zastavka_ru.txt";

// ================= FILE DISPLAY =================
void Display(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << GetLang("ERROR_FILE") << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void DisplaySection(const std::string& path, const std::string& startMarker, const std::string& endMarker)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << GetLang("ERROR_FILE") << ": " << path << std::endl;
        return;
    }

    std::string line;
    bool printing = startMarker.empty();

    while (getline(file, line))
    {
        
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // === Начало секции ===
        if (!startMarker.empty() && line.find(startMarker) != std::string::npos)
        {
            printing = true;
            continue; // пропускаем строку с маркером
        }

        if (!printing) continue;

        if (!endMarker.empty() && line.find(endMarker) != std::string::npos)
        {
            break;
        }

        
        if (line.find("===") != std::string::npos)
        {
            continue;   
        }

  
        if (!line.empty()) {
            std::cout << line << std::endl;
        }
    }

    file.close();
}


// ================= LANGUAGE HELPERS =================
std::string GetLang(const std::string& key) {
    auto it = lang.find(key);
    return (it != lang.end()) ? it->second : "[" + key + "]";
}

void PrintLang(const std::string& key) {
    std::cout << GetLang(key) << std::endl;
}



// ================= LOAD LANGUAGE =================
void loadLanguage(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Language file not found");
    }
    lang.clear();
    string line;
    while (getline(file, line)) {
        int pos = line.find('=');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            lang[key] = value;
        }
    }
}

// ================= LOAD CONFIG =================
void LoadConfig() {
    ifstream file("config.txt");
    if (!file.is_open()) {
        throw runtime_error("Config file not found");
    }
    config.clear();
    string line;
    while (getline(file, line)) {
        int pos = line.find('=');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            config[key] = value;
        }
    }
}

// ================= SAVE CONFIG =================
void saveConfig() {
    ofstream file("config.txt");
    for (auto& pair : config) {
        file << pair.first << "=" << pair.second << endl;
    }
}
// ================= SETTINGS =================
void settingsMenu() {
    int choice;
    cout << lang["SETTINGS"] << endl;
    cout << lang["SETTINGS_1"] << endl;
    cout << lang["SETTINGS_2"] << endl;
    cout << lang["ENTER_CHOICE"];
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << lang["ERROR_INPUT"] << endl;
        return;
    }
    if (choice == 1) {
        string newLang;
        cout << lang["ENTER_LANG"];
        cin >> newLang;
        string file = "lang_" + newLang + ".txt";
        try {
            loadLanguage(file);
            config["language"] = newLang;
        }
        catch (...) {
            cout << lang["ERROR_FILE"] << endl;
        }
    }
    else if (choice == 2) {
        string path;
        cout << lang["ENTER_PATH"];
        cin >> path;
        config["data_file"] = path;
    }
    saveConfig();
}

// ================= MAIN MENU_ =================
void mainMenu_() {
    int choice;
    while (true) {
        system("cls");
        string langCode = config["language"];
        DisplaySection("menu_" + langCode + ".txt", "=== MAIN MENU ===", "=== END MAIN MENU ===");
        PrintLang("Выберите пункт");
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            PrintLang("ERROR_INPUT");
            system("pause");
            continue;
        }
        if (choice == 1) {
            system("cls");

            User user("", 0, "");

         
            DisplaySection("menu_" + langCode + ".txt", "=== MAKE USER ===", "=== END USER ===");

          
            cout << "\nВаш выбор: ";
            getline(cin >> ws, user.name);           

            cout << "\nВведите GTM (смещение): ";
            cin >> user.GTM;

            cin.ignore(); 
            cout << "\nВведите географическое положение: ";
            getline(cin, user.Geografy);

            cout << "\nПользователь успешно создан!\n\n";
            user.PrintWatches();


            DisplaySection("menu_" + langCode + ".txt", "=== SCENARIOS ===", "=== END SCENARIOS ===");

            int scen;
            PrintLang("Выбирите сценарий");
            cin >> scen;
            switch (scen) {
            case 1: FlightScenario(user); break;
            case 2: SwimingScenaries(user); break;
            case 3: DiveScenario(user); break;
            default: PrintLang("ERROR_INVALID_CHOICE"); break;
            }

            SaveSession(user);
            system("pause");

        }
        else if (choice == 2) {

        }
    }
}
// ================= MAIN MENU =================
void mainMenu()
{
    int choice;
    while (true)
    {
        system("cls");
        string langCode = config["language"];


        DisplaySection("menu_" + langCode + ".txt", "=== MAIN MENU ===", "=== END MAIN MENU ===");

        PrintLang("ENTER_CHOICE");
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            PrintLang("ERROR_INPUT");
            system("pause");
            continue;
        }

        if (choice == 1)  
        {
            system("cls");
            User user("", 0, "");

            PrintLang("ENTER_NAME");     cin >> user.name;
            PrintLang("ENTER_GTM");      cin >> user.GTM;
            PrintLang("ENTER_GEO");      cin >> user.Geografy;

         
            DisplaySection("menu_" + langCode + ".txt", "=== SCENARIOS ===", "=== END SCENARIOS ===");

            int scen;
            PrintLang("ENTER_SCENARIO_CHOICE");
            cin >> scen;

            switch (scen)
            {
            case 1: FlightScenario(user); break;
            case 2: SwimingScenaries(user); break;
            case 3: DiveScenario(user); break;
            default: PrintLang("ERROR_INVALID_CHOICE"); break;
            }

            cout << "\n";
            user.PrintWatches();
            SaveSession(user);
            system("pause");
        }
        else if (choice == 2)
        {
            Display("author_" + langCode + ".txt");
            system("pause");
        }
        else if (choice == 3)
        {
            Display("rykovodstvo_" + langCode + ".txt");
            system("pause");
        }
        else if (choice == 4)
        {
            Display("o_programme_" + langCode + ".txt");
            system("pause");
        }
        else if (choice == 5)
        {
            settingsMenu();
        }
        else if (choice == 6)
        {
            PrintLang("LOADING_SESSION");
            User loadedUser("Loaded", 0, "Unknown");
            if (LoadSession(loadedUser))
                PrintLang("SESSION_LOADED_SUCCESS");
            system("pause");
        }
        else if (choice == 7)
        {
            break; 
        }
        else
        {
            PrintLang("ERROR_INVALID_CHOICE");
            system("pause");
        }
    }
}

// ================= START =================
void start_program() {
    try{
        LoadConfig();
        string langFile = "lang_" + config["language"] + ".txt";
        loadLanguage(langFile);

        zastavka_();
        mainMenu_();
        //mainMenu();
    }
    catch (exception& e) {
        cout << "Critical error: " << e.what() << endl;
    }
}

// ================= NEXTID =================
 int GetNextWatchId() {
    ifstream file("Watches.txt");

    if (!file.is_open()) return 0;

    string line;
    int lastId = -1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = line.find('|');
        if (pos != string::npos) {
            int id = stoi(line.substr(0, pos));
            lastId = id;
        }
    }

    return lastId + 1;
}
// ================= MAINMENUUNTILMARKET =================
 void DisplayMenuUntilMarker(const string& path, string& markerLine) {
    ifstream file(path);
    string line;

    while (getline(file, line)) {
        cout << line << endl;

        if (line.find("Want do import file?") != string::npos ||
            line.find("Хотите загрузить файл?") != string::npos) {

            markerLine = line; 
            break;
        }
    }
}

// ================= ZASTAVKA =================
 void zastavka_()
 {
     while (true)  // Для возможности смены языка
     {
         system("cls");

         std::string langCode = config["language"];
         std::string filename = "zastavka_" + langCode + ".txt";

         std::ifstream fin(filename);
         if (!fin.is_open())
         {
             // Если файл текущего языка не найден — открываем русский
             fin.open("zastavka_ru.txt");
             if (!fin.is_open())
             {
                 std::cout << "Не удалось открыть файл заставки!\n";
                 system("pause");
                 return;
             }
         }

         std::string line;
         while (std::getline(fin, line))
         {
             std::cout << line << std::endl;
         }
         fin.close();

         // Ожидание нажатия клавиши (без вывода текста)
         while (true)
         {
             int key = _getch();

             if (key == 13)                    // ENTER — начать
             {
                 system("cls");
                 return;
             }
             else if (key == 9)                // TAB — смена языка
             {
                 // Смена языка
                 if (config["language"] == "ru")
                     config["language"] = "en";
                 else
                     config["language"] = "ru";

                 // Перезагружаем язык
                 try
                 {
                     std::string langFile = "lang_" + config["language"] + ".txt";
                     loadLanguage(langFile);
                     saveConfig();
                 }
                 catch (...) {
                 
                 }

                 break;      
             }
             else if (key == 27)               // ESC — выход
             {
                 exit(0);
             }
             else if (key == 'a' || key == 'A')
             {
                 Display("author_" + config["language"] + ".txt");
                 system("pause");
                 break;
             }
             else if (key == 's' || key == 'S')
             {
                 Display("rykovodstvo_" + config["language"] + ".txt");
                 system("pause");
                 break;
             }
             else if (key == 'd' || key == 'D')
             {
                 Display("o_programme_" + config["language"] + ".txt");
                 system("pause");
                 break;
             }
         }
     }
 }

 // ================= SWIMING SCENARIES =================
 void SwimingScenaries(User& user)
 {
     
     system("cls");
     
     DisplaySection("menu_" + config["language"] + ".txt", "=== MAKE DIVE ===", "=== END DIVE ===");

     std::string time;

     int depth, bezel, typeInput;
     bool type;

     std::cout << "\n> ";
     getline(cin >> ws, time);

     std::cout << "\n";
     cin >> depth;

     std::cout << "\n";
     cin >> bezel;

     std::cout << "\n";
     cin >> typeInput;

     if (typeInput == 1) {
         type = true;
     }
     else {
         type = false;
     }

     DivingWatches* dive = new DivingWatches(time, type, depth, bezel);

     dive->user_id = user.id;
     dive->BeginTheUnderwater();
     dive->Save();
     user.AddWatch(dive);

     std::cout << "\n=== Простое погружение начато ===\n";
     SaveSession(user);

     system("pause"); 
     
 }

 // ================= DIVE SCENARIO =================
 void DiveScenario(User& user)
 {
     system("cls");

     DisplaySection("menu_" + config["language"] + ".txt",
         "=== DIVE COMP ===", "=== END DIVE COMP ===");

     std::string time;
     int maxDepth = 0;
     int temp = 0;

     std::cout << "\n> ";
     getline(cin >> ws, time);

     std::cout << "\n> ";
     cin >> maxDepth;

     std::cout << "\n> ";
     cin >> temp;

     
     DiveComp* dive = new DiveComp("Recreational", 1, 60, 1, temp, 0, "Air");

     dive->Time = time;
     dive->SetMaxDepth(maxDepth);
     dive->user_id = user.id;

     user.AddWatch(dive);

     std::cout << "\n=== Погружение успешно инициализировано ===\n";
     PrintLang("DIVE_STARTED");
     AddLog("Dive started");

     dive->StartDescent();

     // === Цикл управления ===
     bool diving = true;
     while (diving)
     {
         system("cls");
         dive->PrintStatus();

         DisplaySection("menu_" + config["language"] + ".txt",
             "=== DIVE_CONTROL ===", "=== END DIVE_CONTROL ===");

         int choice;
         std::cout << "\nВаш выбор: ";
         cin >> choice;

         switch (choice)
         {
         case 1:
             dive->Stay(15);
             break;
         case 2:
             --(*dive);                    // всплытие на 1 метр
             break;
         case 3:
             dive->Ascend(5);             
             break;
         case 4: // Аварийное всплытие
             std::cout << "!!! АВАРИЙНОЕ ВСПЛЫТИЕ !!!\n";
             dive->CurDepth = 0;
             diving = false;
             AddLog("Emergency ascent");
             break;
         case 5: // Завершить погружение
             if (dive->CurDepth != 0)
                 PrintLang("ERROR_ASCEND_FIRST");
             else
                 diving = false;
             break;
         default:
             PrintLang("ERROR_INVALID_CHOICE");
             break;
         }

         if (diving)
             system("pause");
     }

     PrintLang("DIVE_FINISHED");
     dive->PrintStatus();
     dive->Save();

     AddLog("Dive finished. Total time: " + std::to_string(dive->DiveTime) + " min");
     SaveSession(user);

     std::cout << "\nСценарий погружения завершён.\n";
     system("pause");
 }

 // ================= FLIGHT SCENARIO =================
 void FlightScenario(User& user)
 {
     system("cls");

     DisplaySection("menu_" + config["language"] + ".txt",
         "=== MAKE FLIGHT ===", "=== END FLIGHT ===");
     std::string time;

 
     int flightduration = 0;
     std::string destZone;
     int destOffset = 0;

     std::cout << "\n> ";
     getline(cin >> ws, time);

     int offset = user.GTM;

     std::string zone = user.Geografy;

     std::cout << "\n> ";
     cin >> flightduration;

     cin.ignore();
     std::cout << "\n> ";
     getline(cin, destZone);

     std::cout << "\n> ";
     cin >> destOffset;

     GTMWatches* gtm = new GTMWatches(time, offset, zone);

     gtm->user_id = user.id;

     user.AddWatch(gtm);
     
     std::cout << "\nПолёт успешно инициализирован!\n\n";
     gtm->StartFlight(flightduration);

     PrintLang("FLIGHT_FINISHED");
     SaveSession(user);
 }

 void CreateLogFile(std::string path) {
     if (path.empty()) {
         path = "logs.txt";
     }
     std::ofstream file(path, ios::app);

     if (!file.is_open()) {
         cout << "Log file create error\n";
         return;
     }

     file << "=== LOG FILE CREATED ===\n";

     file.close();
 }

 void SetPathForLogs(std::string path) {
     
     
     if (path.empty()) {
         logPath = "logs.txt";
     }
     else {
         logPath = path;
     }
}

 void AddLog(std::string message) {
     std::ofstream file(logPath, ios::app);

     if (!file.is_open()) {
         cout << "Log open error\n";
         return;
     }

     file << message << std::endl;

     file.close();

 }

 void SaveSession(User& user)
 {
     std::ofstream file("session.bin", std::ios::binary | std::ios::trunc);
     if (!file.is_open()) {
         std::cout << "Ошибка создания session.bin\n";
         return;
     }


     int userId = user.id;
     int gtmOffset = user.GTM;
     size_t nameLen = user.name.length();
     size_t geoLen = user.Geografy.length();

     file.write((char*)&userId, sizeof(userId));
     file.write((char*)&gtmOffset, sizeof(gtmOffset));
     file.write((char*)&nameLen, sizeof(nameLen));
     file.write(user.name.c_str(), nameLen);
     file.write((char*)&geoLen, sizeof(geoLen));
     file.write(user.Geografy.c_str(), geoLen);


     const auto& watches = user.GetWatches();
     int watchCount = watches.size();
     file.write((char*)&watchCount, sizeof(watchCount));

     for (auto* w : watches)
     {
         if (GTMWatches* gtm = dynamic_cast<GTMWatches*>(w))
         {
             int type = 1;                                 
             file.write((char*)&type, sizeof(type));

             int offset = gtm->GetGTMOffset();
             size_t tLen = gtm->Time.length();
             size_t sLen = gtm->SecondTime.length();
             size_t zLen = gtm->GetSecondZoneName().length();//SecondZoneName.length();

             file.write((char*)&offset, sizeof(offset));
             file.write((char*)&tLen, sizeof(tLen));
             file.write(gtm->Time.c_str(), tLen);
             file.write((char*)&sLen, sizeof(sLen));
             file.write(gtm->SecondTime.c_str(), sLen);
             file.write((char*)&zLen, sizeof(zLen));
             file.write(gtm->GetSecondZoneName().c_str(), zLen);
         }
         else if (DiveComp* dc = dynamic_cast<DiveComp*>(w))
         {
             int type = 2;                               
             file.write((char*)&type, sizeof(type));

             size_t timeLen = dc->Time.length();
             file.write((char*)&timeLen, sizeof(timeLen));
             file.write(dc->Time.c_str(), timeLen);

             file.write((char*)&dc->CurDepth, sizeof(dc->CurDepth));
             int tempVal = dc->GetTemp();
             file.write((char*)&tempVal, sizeof(tempVal));

            

             std::string mixStr = dc->GetMix();
             size_t mixLen = mixStr.length();
             file.write((char*)&mixLen, sizeof(mixLen));
             if (mixLen > 0) {
                 file.write(mixStr.c_str(), mixLen);
             }
             
             std::string vidStr = dc->Vid;
             size_t vidlen = vidStr.length();
             file.write((char*)&vidlen, sizeof(vidlen));
             if (vidlen > 0) {
                 file.write(vidStr.c_str(), vidlen);
             }
         }
     }

     file.close();
     std::cout << " Сессия успешно сохранена (" << watchCount << " часов)\n";
 }

 // ====================== LOAD SESSION ======================
 bool LoadSession(User& user)
 {
     std::ifstream file("session.bin", std::ios::binary);
     if (!file.is_open()) {
         std::cout << "Файл session.bin не найден.\n";
         return false;
     }

     user.ClearWatches();        

    
     int userId, gtmOffset;
     size_t nameLen, geoLen;

     file.read((char*)&userId, sizeof(userId));
     file.read((char*)&gtmOffset, sizeof(gtmOffset));
     file.read((char*)&nameLen, sizeof(nameLen));

     user.name.resize(nameLen);
     file.read(&user.name[0], nameLen);

     file.read((char*)&geoLen, sizeof(geoLen));
     user.Geografy.resize(geoLen);
     file.read(&user.Geografy[0], geoLen);

     user.id = userId;
     user.GTM = gtmOffset;

   
     int watchCount;
     file.read((char*)&watchCount, sizeof(watchCount));

   
     for (int i = 0; i < watchCount; ++i)
     {
         int type;
         file.read((char*)&type, sizeof(type));

         if (type == 1) 
         {
             GTMWatches* gtm = new GTMWatches();
             int offset;
             size_t tLen, sLen, zLen;

             file.read((char*)&offset, sizeof(offset));
             gtm->SetGTMOffset(offset);
        

             file.read((char*)&tLen, sizeof(tLen));
             gtm->Time.resize(tLen);
             file.read(&gtm->Time[0], tLen);

             file.read((char*)&sLen, sizeof(sLen));
             gtm->SecondTime.resize(sLen);
             file.read(&gtm->SecondTime[0], sLen);

             file.read((char*)&zLen, sizeof(zLen));
             std::string tempZoneName;
             tempZoneName.resize(zLen);
             if (zLen > 0) {
                 file.read(&tempZoneName[0], zLen);
             }
             gtm->SetSecondTime(tempZoneName);


             user.AddWatch(gtm);
         }
         else if (type == 2) 
         {
             DiveComp* dc = new DiveComp("Recreational", 1, 60, 1, 15, 0, "Air");

     
             size_t timeLen = 0;
             file.read((char*)&timeLen, sizeof(timeLen));
             std::string timeStr;
             timeStr.resize(timeLen);
             if (timeLen > 0) {
                 file.read(&timeStr[0], timeLen);
             }
             dc->Time = timeStr;

             file.read((char*)&dc->CurDepth, sizeof(dc->CurDepth));


             int tempVal = 0;
             file.read((char*)&tempVal, sizeof(tempVal));
             dc->SetTemp(tempVal);

          
             size_t mixLen = 0;
             file.read((char*)&mixLen, sizeof(mixLen));
             std::string mixStr;
             mixStr.resize(mixLen);
             if (mixLen > 0) {
                 file.read(&mixStr[0], mixLen);
             }
             dc->SetMix(mixStr); 

           
             size_t vidLen = 0;
             file.read((char*)&vidLen, sizeof(vidLen));
             std::string vidStr;
             vidStr.resize(vidLen);
             if (vidLen > 0) {
                 file.read(&vidStr[0], vidLen);
             }
             dc->Vid = vidStr; 

             user.AddWatch(dc);
         }
     }

     file.close();
     std::cout << " Сессия успешно загружена (" << watchCount << " часов)\n";
     user.PrintWatches();
     return true;
 }



 std::string AddMinutesToTime(const std::string& currentTime, int minutesToAdd) {
     if (currentTime.empty() || minutesToAdd <= 0)
         return currentTime;

     int hours = 0, minutes = 0;
     char colon;

     std::istringstream iss(currentTime);
     iss >> hours >> colon >> minutes;

     minutes += minutesToAdd;

     hours += minutes / 60;
     minutes = minutes % 60;

     hours = hours % 24;

     std::ostringstream oss;
     oss << std::setw(2) << std::setfill('0') << hours << ":"
         << std::setw(2) << std::setfill('0') << minutes;

     return oss.str();

 }
