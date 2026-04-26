#pragma once
#include <map>
#include <string>
#include "iostream"

using namespace std;

extern map<string, string> lang;
extern map<string, string> config;

void start_program();
void loadLanguage(string filename);
void LoadConfig();
void saveConfig();

void mainMenu();
void settingsMenu();

void Display(const string& path);

void zastavka_();