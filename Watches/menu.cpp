#include "Logical.h"
#include "iostream"
#include <iomanip>
#include <string>
#include <fstream>
#include "conio.h"

using namespace std;

map<string, string> lang;
map<string, string> config;

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