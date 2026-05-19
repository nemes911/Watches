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
void mainMenu_()
{
    int choice;
    User* currentUser = nullptr;   
    std::string newpath;// указатель на текущего пользователя

    while (true)
    {
        system("cls");
        string langCode = config["language"];
        DisplaySection("menu_" + langCode + ".txt", "=== LOG INF ===", "=== END LOG ===");
        cin >> newpath;
        if (newpath != "n") {
            continue;
        }
        else {
            logPath = newpath;
        }

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

        

        if (choice == 1)   // Создать пользователя + сценарии
        {
            if (currentUser == nullptr)
            {
                currentUser = new User("", 0, "");

                DisplaySection("menu_" + langCode + ".txt", "=== MAKE USER ===", "=== END USER ===");

                cout << "\nВаш выбор: ";
                getline(cin >> ws, currentUser->name);
                cout << "\nВведите GTM (смещение): ";
                cin >> currentUser->GTM;
                cin.ignore();
                cout << "\nВведите географическое положение: ";
                getline(cin, currentUser->Geografy);

                cout << "\nПользователь успешно создан!\n\n";
                currentUser->PrintWatches();
            }
            else
            {
                cout << "\nИспользуется текущий пользователь: " << currentUser->name << "\n\n";
            }

            // Выбор сценария
            DisplaySection("menu_" + langCode + ".txt", "=== SCENARIOS ===", "=== END SCENARIOS ===");
            int scen;
            PrintLang("Выбирите сценарий");
            cin >> scen;

            switch (scen)
            {
            case 1:
                FlightScenario(*currentUser);
                break;
            case 2:
                SwimingScenaries(*currentUser);
                break;
            case 3:
                DiveScenario(*currentUser);
                break;
            default:
                PrintLang("ERROR_INVALID_CHOICE");
                break;
            }

            system("pause");
        }
        else if (choice == 2)   // Выход
        {
            std::cout << "\nВыход из программы...\n";
            if (currentUser != nullptr)
            {
                delete currentUser;     
            }
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
     while (true)  
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

         
         while (true)
         {
             int key = _getch();

             if (key == 13)                    
             {
                 system("cls");
                 return;
             }
             else if (key == 9)               
             {
               
                 if (config["language"] == "ru")
                     config["language"] = "en";
                 else
                     config["language"] = "ru";

            
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
             else if (key == 27)               
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
             break;
         }

         if (diving)
             system("pause");
     }

     PrintLang("DIVE_FINISHED");
     dive->PrintStatus();
     dive->Save();

     AddLog("Dive finished. Total time: " + std::to_string(dive->DiveTime) + " min");
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

     cin.ignore();
     std::cout << "\n> ";
     getline(cin, destZone);

     std::cout << "\n> ";
     cin >> destOffset;

     GTMWatches* gtm = new GTMWatches(time, offset, zone);

     gtm->user_id = user.id;

     user.AddWatch(gtm);
     
     

     while (gtm->GetGTMOffset() != destOffset)
     {
         int segmentTime = 60 + rand() % 81;   
         gtm->SimulateFlightStep(segmentTime);
         (*gtm)++;
         gtm->NextGTM(gtm->GetGTMOffset());                       

         AddLog("GTM" + std::to_string(gtm->GetGTMOffset()) + "TIME:" + gtm->Time);
     }
     PrintLang("FLIGHT_FINISHED");
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
