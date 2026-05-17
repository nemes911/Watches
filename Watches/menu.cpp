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

using namespace std;

map<string, string> lang;
map<string, string> config;

std::string logPath = "logs.txt";

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
        std::cout << GetLang("ERROR_FILE") << std::endl;
        return;
    }

    std::string line;
    bool printing = startMarker.empty();

    while (getline(file, line)) {
        if (!startMarker.empty() && line.find(startMarker) != std::string::npos) {
            printing = true;
            continue;
        }
        if (printing) {
            if (!endMarker.empty() && line.find(endMarker) != std::string::npos) {
                break;
            }
            std::cout << line << std::endl;
        }
    }
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



// ================= MAIN MENU =================
void mainMenu()
{
    int choice;
    while (true)
    {
        system("cls");
        string langCode = config["language"];

        // Выводим ТОЛЬКО главное меню
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

        if (choice == 1)  // Новый пользователь + сценарий
        {
            system("cls");
            User user("", 0, "");

            PrintLang("ENTER_NAME");     cin >> user.name;
            PrintLang("ENTER_GTM");      cin >> user.GTM;
            PrintLang("ENTER_GEO");      cin >> user.Geografy;

            // Выводим только блок сценариев
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
            break; // Выход
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

        mainMenu();
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

            markerLine = line; // сохранили строку
            break;
        }
    }
}

// ================= ZASTAVKA =================
 void zastavka_()
 {
     while (true)
     {
         system("cls");

         // Можно вынести шапку университета в lang-файл, но оставим как есть для красоты
         cout << "\tДонецкий Национальный Технический Университет\n";
         cout << "Факультет ФИСП\n";
         cout << "Кафедра ПИ\n\n\n";
         cout << "\tКурсовой проект\n";
         cout << "\tпо дисциплине: \"ООП\"\n";
         cout << "\tна тему: \"Система Часы\"\n\n";

         PrintLang("ZASTAVKA_START ENTER");           // "Начать: ENTER"
         PrintLang("ZASTAVKA_CHANGE_LANG L");     // "Сменить язык: L"
         PrintLang("ZASTAVKA_EXIT ESC");            // "Выход: ESC"
         PrintLang("ZASTAVKA_AUTHOR A");          // "Об авторе: A"
         PrintLang("ZASTAVKA_MANUAL S");          // "Руководство: S"
         PrintLang("ZASTAVKA_ABOUT O");           // "О программе: O"

         char ch = _getch();
         string langCode = config["language"];

         if (ch == 13)                  // ENTER
         {
             return;
         }
         else if (ch == 27)             // ESC
         {
             exit(0);
         }
         else if (ch == 'a' || ch == 'A')
         {
             Display("author_" + langCode + ".txt");
             system("pause");
         }
         else if (ch == 's' || ch == 'S')
         {
             Display("rykovodstvo_" + langCode + ".txt");
             system("pause");
         }
         else if (ch == 'o' || ch == 'O')
         {
             Display("o_programme_" + langCode + ".txt");
             system("pause");
         }
         else if (ch == 'l' || ch == 'L')
         {
             string newLang;
             PrintLang("ENTER_LANG");
             cin >> newLang;

             try
             {
                 loadLanguage("lang_" + newLang + ".txt");
                 config["language"] = newLang;
                 saveConfig();
                 PrintLang("LANGUAGE_CHANGED");
             }
             catch (...)
             {
                 PrintLang("ERROR_FILE");
             }
             system("pause");
         }
     }
 }

 // ================= SWIMING SCENARIES =================
 void SwimingScenaries(User& user)
 {
     std::string time;
     PrintLang("ENTER_TIME");
     cin >> time;

     int typeInput;
     PrintLang("WATCH_TYPE");
     cin >> typeInput;
     bool type = (typeInput == 1);

     PrintLang("WATCH_TYPE_CONFIRM");
     cin >> type;

     int depth;
     PrintLang("MAX_DEPTH");
     cin >> depth;

     int bezel;
     PrintLang("BEZEL");
     cin >> bezel;

     DivingWatches* dive = new DivingWatches(time, type, depth, bezel);
     dive->CtreatedDivingWatches(*dive);
     dive->user_id = user.id;
     dive->BeginTheUnderwater();
     dive->Save();
     user.AddWatch(dive);

     PrintLang("SIMPLE_DIVE_CREATED");
     SaveSession(user);
 }

 // ================= DIVE SCENARIO =================
 void DiveScenario(User& user)
 {
     system("cls");
     PrintLang("SCENARIO_DIVE");

     std::string time;
     PrintLang("DIVE_TIME");
     cin >> time;

     int maxDepth;
     PrintLang("DIVE_MAX_DEPTH");
     cin >> maxDepth;

     int temp;
     PrintLang("DIVE_TEMP");
     cin >> temp;

     char* mix = (char*)"Air";
     char* vid = (char*)"Recreational";

     DiveComp* dive = new DiveComp(vid, 1, 60, 1, temp, 0, mix);
     dive->Time = time;
     dive->MaxDepth = maxDepth;
     dive->CurDepth = 0;
     dive->user_id = user.id;
     user.AddWatch(dive);

     PrintLang("DIVE_STARTED");
     AddLog("Dive started");

     dive->StartDescent();

     bool diving = true;
     while (diving)
     {
         dive->PrintStatus();

         // Меню управления из файла menu_xx.txt
         DisplaySection("menu_" + config["language"] + ".txt",
             "=== DIVE_CONTROL ===", "=== END DIVE_CONTROL ===");

         int choice;
         PrintLang("ENTER_CHOICE");
         cin >> choice;

         switch (choice)
         {
         case 1:
             dive->Stay(15);
             break;
         case 2:
             --(*dive);
             break;
         case 3:
             dive->Ascend(5);
             break;
         case 4:
             std::cout << "!!! АВАРИЙНОЕ ВСПЛЫТИЕ !!!\n";
             dive->CurDepth = 0;
             diving = false;
             AddLog("Emergency ascent");
             break;
         case 5:
             if (dive->CurDepth != 0)
                 PrintLang("ERROR_ASCEND_FIRST");
             else
                 diving = false;
             break;
         default:
             PrintLang("ERROR_INVALID_CHOICE");
         }
     }

     PrintLang("DIVE_FINISHED");
     dive->PrintStatus();
     dive->Save();
     AddLog("Dive finished. Total time: " + std::to_string(dive->DiveTime) + " min");
     SaveSession(user);
 }

 // ================= FLIGHT SCENARIO =================
 void FlightScenario(User& user)
 {
     system("cls");
     PrintLang("SCENARIO_FLIGHT");

     std::string time;
     PrintLang("FLIGHT_LOCAL_TIME");
     cin >> time;

     int offset;
     PrintLang("FLIGHT_GMT_OFFSET");
     cin >> offset;

     std::string zone;
     PrintLang("FLIGHT_ZONE_NAME");
     cin >> zone;

     GTMWatches* gtm = new GTMWatches(time, offset, zone);
     gtm->Time = time;
     gtm->user_id = user.id;
     user.AddWatch(gtm);

     int flightDuration;
     PrintLang("FLIGHT_DURATION");
     cin >> flightDuration;

     std::string destZone;
     int destOffset;
     PrintLang("FLIGHT_DEST_ZONE");
     cin >> destZone;
     PrintLang("FLIGHT_DEST_OFFSET");
     cin >> destOffset;

     gtm->StartFlight(flightDuration);
     PrintLang("FLIGHT_STARTED");
     gtm->PrintStatus();

     bool flying = true;
     while (flying)
     {
         gtm->PrintStatus();

         DisplaySection("menu_" + config["language"] + ".txt",
             "=== FLIGHT_CONTROL ===", "=== END FLIGHT_CONTROL ===");

         int choice;
         PrintLang("ENTER_CHOICE");
         cin >> choice;

         switch (choice)
         {
         case 1:
             gtm->SimulateFlightStep(30);
             break;
         case 2:
             gtm->SimulateFlightStep(60);
             break;
         case 3:
         {
             int newOff;
             std::string newZone;
             PrintLang("FLIGHT_NEW_OFFSET");
             cin >> newOff;
             PrintLang("FLIGHT_NEW_ZONE");
             cin >> newZone;
             gtm->ChangeTimezone(newOff, newZone);
             break;
         }
         case 4:
             gtm->ChangeTimezone(destOffset, destZone);
             gtm->SimulateFlightStep(flightDuration - gtm->FlightTime);
             PrintLang("FLIGHT_ARRIVED");
             flying = false;
             break;
         case 5:
             flying = false;
             break;
         default:
             PrintLang("ERROR_INVALID_CHOICE");
         }
     }

     gtm->PrintFlightSummary();
     gtm->Save();
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

     // === 1. Данные пользователя ===
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

     // === 2. Количество часов ===
     const auto& watches = user.GetWatches();
     int watchCount = watches.size();
     file.write((char*)&watchCount, sizeof(watchCount));

     // === 3. Сохранение каждого объекта ===
     for (auto* w : watches)
     {
         if (GTMWatches* gtm = dynamic_cast<GTMWatches*>(w))
         {
             int type = 1;                                 
             file.write((char*)&type, sizeof(type));

             int offset = gtm->GTMOffset;
             size_t tLen = gtm->Time.length();
             size_t sLen = gtm->SecondTime.length();
             size_t zLen = gtm->SecondZoneName.length();

             file.write((char*)&offset, sizeof(offset));
             file.write((char*)&tLen, sizeof(tLen));
             file.write(gtm->Time.c_str(), tLen);
             file.write((char*)&sLen, sizeof(sLen));
             file.write(gtm->SecondTime.c_str(), sLen);
             file.write((char*)&zLen, sizeof(zLen));
             file.write(gtm->SecondZoneName.c_str(), zLen);
         }
         else if (DiveComp* dc = dynamic_cast<DiveComp*>(w))
         {
             int type = 2;                               
             file.write((char*)&type, sizeof(type));

             size_t timeLen = dc->Time.length();
             file.write((char*)&timeLen, sizeof(timeLen));
             file.write(dc->Time.c_str(), timeLen);

             file.write((char*)&dc->CurDepth, sizeof(dc->CurDepth));
             file.write((char*)&dc->Temp, sizeof(dc->Temp));

            
             size_t mixLen = dc->Mix ? strlen(dc->Mix) : 0;
             file.write((char*)&mixLen, sizeof(mixLen));
             if (dc->Mix) file.write(dc->Mix, mixLen);

             size_t vidLen = dc->Vid ? strlen(dc->Vid) : 0;
             file.write((char*)&vidLen, sizeof(vidLen));
             if (dc->Vid) file.write(dc->Vid, vidLen);
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
             gtm->GTMOffset = offset;

             file.read((char*)&tLen, sizeof(tLen));
             gtm->Time.resize(tLen);
             file.read(&gtm->Time[0], tLen);

             file.read((char*)&sLen, sizeof(sLen));
             gtm->SecondTime.resize(sLen);
             file.read(&gtm->SecondTime[0], sLen);

             file.read((char*)&zLen, sizeof(zLen));
             gtm->SecondZoneName.resize(zLen);
             file.read(&gtm->SecondZoneName[0], zLen);

             user.AddWatch(gtm);
         }
         else if (type == 2) // DiveComp
         {
             DiveComp* dc = new DiveComp((char*)"Recreational", 1, 60, 1, 15, 0, (char*)"Air");

             size_t timeLen;
             file.read((char*)&timeLen, sizeof(timeLen));
             dc->Time.resize(timeLen);
             file.read(&dc->Time[0], timeLen);

             file.read((char*)&dc->CurDepth, sizeof(dc->CurDepth));
             file.read((char*)&dc->Temp, sizeof(dc->Temp));

             
             size_t mixLen;
             file.read((char*)&mixLen, sizeof(mixLen));
             if (mixLen > 0) {
                 char* mix = new char[mixLen + 1];
                 file.read(mix, mixLen);
                 mix[mixLen] = '\0';
                 dc->SetMix(mix);
                 delete[] mix;
             }

             user.AddWatch(dc);
         }
     }

     file.close();
     std::cout << " Сессия успешно загружена (" << watchCount << " часов)\n";
     user.PrintWatches();
     return true;
 }

