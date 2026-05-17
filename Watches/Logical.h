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

void DisplaySection(const std::string& path, const std::string& startMarker = "", const std::string& endMarker = "");
std::string GetLang(const std::string& key);
void PrintLang(const std::string& key);

void FlightScenario(User& user);
void SwimingScenaries(User& user);
void DiveScenario(User& user);
void zastavka_();
int GetNextWatchId();
void SetPathForLogs(std::string path);
void CreateLogFile(std::string path);
void AddLog(std::string message);

void SaveSession(User& user);
bool LoadSession(User& user);