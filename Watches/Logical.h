#pragma once
#include <map>
#include <string>
#include "iostream"
#include "User.h"

using namespace std;

extern map<string, string> lang;
extern map<string, string> config;

void start_program();
void loadLanguage(string filename);
void LoadConfig();
void saveConfig();

void mainMenu();
void DisplayMenuUntilMarker(const string& path, string& markerLine);
void settingsMenu();

void Display(const string& path);

void FlightScenario(User& user);
void SwimingScenaries(User& user);
void DiveScenario(User& user);
void zastavka_();
int GetNextWatchId();