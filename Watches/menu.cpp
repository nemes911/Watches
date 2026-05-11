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
        cout << lang["ERROR_FILE"] << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
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
void mainMenu() {
    int choice;

    while (true) {
        system("cls");

        string langCode = config["language"];

        Display("menu_" + langCode + ".txt");

        cout << lang["ENTER_CHOICE"];
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << lang["ERROR_INPUT"] << endl;
            system("pause");
            continue;
        }

        if (choice == 1) {
            system("cls");

            string langCode = config["language"];
            string marker;

            DisplayMenuUntilMarker("menu_" + langCode + ".txt", marker);

            cout << "\n(y/n): ";

            char answer;
            cin >> answer;

            if (answer == 'y' || answer == 'Y') {
                
            }
            else if (answer == 'n' || answer == 'N') {
                system("cls");

                string name, geo;
                int gtm;

                cout << "Enter user name";
                cin >> name;

                cout << "Enter GTM";
                cin >> gtm;

                cout << "Enter GEO";
                cin >> geo;

                User user(name, gtm, geo);

                int scen;

                cout << "\nChoose scenario:\n";
                cout << "1. Flight\n";
                cout << "2. Diving (simple)\n";
                cout << "3. Dive Computer\n";
                cout << "Choice: ";
                cin >> scen;
                
                switch (scen) {
                    case 1:
                        FlightScenario(user);
                        break;
                    case 2:
                        SwimingScenaries(user);
                        break;
                    case 3:
                        DiveScenario(user);
                        break;
                    default:
                        cout << "Invalid scenario\n";
                        break;
                }
                cout << "\nUser watches:\n";
                user.PrintWatches();

            }
            else {
                cout << "Invalid input\n";
            }

            system("pause");
        }
        else if (choice == 2) {

        }
        else if (choice == 3) {

        }
        else if (choice == 4) {

        }
        else if (choice == 5) {
            break;
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
void zastavka_() {
    while (true) {
        system("cls");  

        cout << "\tДонецкий Национальный Технический Университет\n";
        cout << "Факультет ФИСП\n";
        cout << "Кафедра ПИ\n\n\n";

        cout << "\tКурсовой проект\n";
        cout << "\tпо дисциплине: \"ООП\"\n";
        cout << "\tна тему: \"Система Часы\"\n\n";

        cout << "Начать: ENTER\n";
        cout << "Сменить язык: L\n";
        cout << "Выход: ESC\n";
        cout << "Об авторе: A\n";
        cout << "Руководство: S\n";
        cout << "О программе: O\n";

        char ch = _getch();

        string langCode = config["language"];

        if (ch == 13) { 
            return;
        }
        else if (ch == 27) { 
            exit(0);
        }
        else if (ch == 'a' || ch == 'A') {
            Display("author_" + langCode + ".txt");
            system("pause");
        }
        else if (ch == 's' || ch == 'S') {
            Display("rykovodstvo_" + langCode + ".txt");
            system("pause");
        }
        else if (ch == 'o' || ch == 'O') {
            Display("o_programme_" + langCode + ".txt");
            system("pause");
        }
        else if (ch == 'l' || ch == 'L') {
            string newLang;
            cout << "\nВведите язык (ru/en): ";
            cin >> newLang;

            try {
                loadLanguage("lang_" + newLang + ".txt");
                config["language"] = newLang;
                saveConfig();
            }
            catch (...) {
                cout << "Ошибка загрузки языка\n";
                system("pause");
            }
        }
    }
}

// ================= SWIMING SCENARIES =================
 void SwimingScenaries(User& user) {
    std::string time;
    cout << "Задайте время\n";
    cin >> time;
    int typeInput;
    cout << "Тип часов (1 - цифровые, 0 - механические): ";
    cin >> typeInput; 
    bool type = (typeInput == 1);
    cout << "Цифровые или механ ические\n";
    cin >> type;
    int depth;
    cout << "Максимальная глубина\n";
    cin >> depth;
    int bezel;
    cout << "Безель\n";
    cin >> bezel;
    DivingWatches* dive = new DivingWatches(time, type, depth, bezel);

    dive->CtreatedDivingWatches(*dive);

    dive->user_id = user.id;

    dive->BeginTheUnderwater();

    dive->Save();

    user.AddWatch(dive);
}

// ================= SWIMING SCENARIES WITH DIVECOMP =================
 void DiveScenario(User& user) {

     string time;

     cout << "Enter time (HH:MM): ";
     cin >> time;

     int targetDepth;

     cout << "Enter target depth: ";
     cin >> targetDepth;

     int temp;

     cout << "Enter water temperature: ";
     cin >> temp;

     char* mix = (char*)"Air";
     char* mode = (char*)"Recreational";

     DiveComp* dive =
         new DiveComp(mode, 1, 60, 100, temp, 0, mix);

     dive->Time = time;
     dive->user_id = user.id;

     user.AddWatch(dive);

     cout << "\n--- Dive started ---\n";

     AddLog("Dive started");

     // ================= DESCENT =================

     cout << "\nDescending...\n";

     while (dive->CurDepth < targetDepth) {

         dive->CurDepth += 5;

         if (dive->CurDepth > targetDepth)
             dive->CurDepth = targetDepth;

         cout << "Depth: "
             << dive->CurDepth << " m\n";

         AddLog(
             "Depth reached: "
             + to_string(dive->CurDepth)
         );
     }

     cout << "\n--- Target depth reached ---\n";

     // ================= MAIN DIVE =================

     bool diving = true;

     int diveMinutes = 0;

     while (diving) {

         cout << "\n===== DIVE MENU =====\n";

         cout << "Depth: "
             << dive->CurDepth << " m\n";

         cout << "Dive time: "
             << diveMinutes << " min\n";

         cout << "1. Stay 15 minutes\n";
         cout << "2. Ascend 1 meter\n";
         cout << "3. Emergency ascent\n";
         cout << "4. Finish dive\n";

         int choice;
         cin >> choice;

         switch (choice) {

         case 1:

             diveMinutes += 15;

             cout << "\nStaying underwater...\n";

             AddLog(
                 "Stay underwater for 15 min"
             );

             break;

         case 2:

             if (dive->CurDepth > 0) {

                 (*dive)--;

                 cout << "\nAscending slowly...\n";

                 AddLog(
                     "Ascend to "
                     + to_string(dive->CurDepth)
                 );
             }
             else {
                 cout << "Already on surface\n";
             }

             break;

         case 3:

             cout << "\n!!! EMERGENCY ASCENT !!!\n";

             dive->CurDepth = 0;

             AddLog("Emergency ascent");

             diving = false;

             break;

         case 4:

             if (dive->CurDepth == 0) {

                 diving = false;
             }
             else {

                 cout << "\nAscend before finishing dive\n";
             }

             break;

         default:
             cout << "Invalid action\n";
             break;
         }

         dive->Calculate();

         // safety stop imitation

         if (dive->CurDepth == 5) {

             cout << "\nSAFETY STOP RECOMMENDED\n";

             AddLog("Safety stop at 5m");
         }
     }

     cout << "\n--- Dive finished ---\n";

     AddLog("Dive finished");

     dive->Save();
 }

// ================= FLY =================
 void FlightScenario(User& user) {
    string time;
    cout << "Enter local time (HH:MM): ";
    cin >> time;

    int offset;
    cout << "Enter GMT offset (e.g. +3, -5): ";
    cin >> offset;

    string zone;
    cout << "Enter second zone name: ";
    cin >> zone;

    GTMWatches* gtm = new GTMWatches(time, offset, zone);

    gtm->Time = time;
    gtm->user_id = user.id;

    user.AddWatch(gtm);

    gtm->CreatedGTMWatches(*gtm);

    cout << "\n--- Flight started ---\n";


    gtm->CalculateSecondTime();
    gtm->Print();

    for (int i = 0; i < 3; i++) {
        cout << "\nChanging timezone...\n"; 

        (*gtm)++; 

        gtm->CalculateSecondTime();
        gtm->Print();
    }

    cout << "\n--- Flight finished ---\n";

    gtm->Save();
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

