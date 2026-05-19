#include "DiveComp.h"
#include <fstream>
#include "Logical.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm> 
#include "conio.h"

using namespace std;

int DiveComp::count = 0;
int DiveComp::nextid = 0;


void DiveComp::SetMix(std::string& Mix) {
    this->Mix = Mix;
}

std::string DiveComp::GetMix() {
    return this->Mix;
}

int DiveComp::GetTemp() {
    return this->Temp;
}

void DiveComp::SetTemp(int Temp) {
    this->Temp = Temp;
}

void DiveComp::SetMaxDepth(int depth) {
    this->MaxDepth = depth;
}

int DiveComp::GetMaxDepth() const {
    return this->MaxDepth;
}

int DiveComp::GetCount() {
    return count;
}

int DiveComp::GetAll() {
    return count;
}




DiveComp::DiveComp()
    : Vid("Recreational"), Mix("Air"), Count(0), TimeCicle(0), NumberDives(0),
    Temp(20), CurDepth(0), MaxDepth(0), DiveTime(0)
{
    id = GetNextWatchId();
    count++;
}


DiveComp::DiveComp(std::string Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, std::string Mix)
    : Vid(Vid), Count(Count), TimeCicle(TimeCicle), NumberDives(NumberDivers),
    Temp(Temp), CurDepth(CurDepth), MaxDepth(CurDepth), DiveTime(0), Mix(Mix)
{
    id = GetNextWatchId();
    count++;
    CreateDiveComp(*this);
}

DiveComp::~DiveComp() {
    count--;
    
}

// ================= ОПЕРАТОРЫ И УПРАВЛЕНИЕ ПОГРУЖЕНИЕМ =================


DiveComp DiveComp::operator--(int) {
    DiveComp temp = *this;
    if (CurDepth > 0) {
        CurDepth--;
    }
    return temp;
}


DiveComp& DiveComp::operator--() {
    if (CurDepth > 0) {
        CurDepth--;
        DiveTime += 1;
        Time = AddMinutesToTime(Time, 1);     
    }
    return *this;
}


void DiveComp::StartDescent() {

    int initialTemp = Temp;  // запоминаем начальную температуру

    while (CurDepth < MaxDepth)
    {
        int step = std::min(5, MaxDepth - CurDepth);
        CurDepth += step;

        // Уменьшаем температуру каждые 100 метров
        int depthHundreds = CurDepth / 100;           // сколько полных 100-метров прошло
        Temp = initialTemp - (depthHundreds * 2);

        // Не даём температуре уйти в отрицательные значения
        if (Temp < -2) Temp = -2;

        std::cout << "Глубина: " << std::setw(3) << CurDepth
            << " м | Температура: " << Temp << "°C\n";

        AddLog("Descent to " + std::to_string(CurDepth) + "m, Temp: "
            + std::to_string(Temp) + "C");

    }
}

bool DiveComp::Ascend(int meters)
{
    if (CurDepth == 0) {
        std::cout << "Вы уже на поверхности!\n";
        return false;
    }

    int oldDepth = CurDepth;
    CurDepth = std::max(0, CurDepth - meters);


    int timeAdded = ((meters + 4) / 5) * 2;
    DiveTime += timeAdded;

    Time = AddMinutesToTime(Time, timeAdded);   

    if (CurDepth == 0) {
        std::cout << ">>> Успешно всплыли на поверхность <<<\n";
    }
    else {
        std::cout << "Всплытие на " << meters << " м → Глубина: "
            << CurDepth << " м (+ " << timeAdded << " мин)\n";
    }

    AddLog("Ascended " + std::to_string(meters) + "m");
    return true;
}

void DiveComp::Stay(int minutes) {
    DiveTime += minutes;
    Time = AddMinutesToTime(Time, minutes);     

    std::cout << "Пребывание на глубине " << minutes << " минут...\n";
    AddLog("Stayed " + std::to_string(minutes) + " min at " + std::to_string(CurDepth) + "m");
}

// ================= АНАЛИЗ И ВЫВОД ДАННЫХ =================

void DiveComp::PrintStatus() const
{
    std::cout << "\n=== DiveComp Status ===\n";
    std::cout << "Время: " << Time << "\n"; 
    std::cout << "Глубина: " << CurDepth << " / " << MaxDepth << " м\n";
    std::cout << "Время под водой: " << DiveTime << " мин\n";
    std::cout << "Температура: " << Temp << "°C\n";


    std::cout << "Смесь: " << (Mix.empty() ? "Air" : Mix) << "\n";
    std::cout << "Режим: " << (Vid.empty() ? "Recreational" : Vid) << "\n";
    std::cout << "========================\n";
}

void DiveComp::Calculate() {
    cout << "\n=== Dive Analysis ===\n";
    cout << "Mode: " << Vid << endl;
    cout << "Depth: " << CurDepth << " m\n";
    cout << "Temperature: " << Temp << " C\n";
    cout << "Gas mix: " << Mix << endl;

    PrintStatus();

    if (CurDepth > 40)
        std::cout << "ВНИМАНИЕ: Большая глубина!\n";
    if (Temp < 10)
        std::cout << "ВНИМАНИЕ: Холодная вода!\n";

    if (CurDepth <= 20) {
        cout << "Safe recreational depth\n";
    }
    else if (CurDepth <= 40) {
        cout << "Medium depth - caution required\n";
    }
    else {
        cout << "DANGER: deep dive!\n";
    }

    if (Temp < 10) {
        cout << "WARNING: Cold water\n";
    }

    if ((Mix == "air" || Mix == "Air") && CurDepth > 30) {
        cout << "WARNING: Air not safe deeper than 30m\n";
    }
    else if (Mix == "nitrox" || Mix == "Nitrox") {
        cout << "Nitrox allows longer bottom time\n";
    }
    else if (Mix == "trimix" || Mix == "Trimix") {
        cout << "Trimix suitable for deep diving\n";
    }

    if (Vid == "freediving" || Vid == "Freediving") {
        cout << "Freediving mode: short dive expected\n";
    }
    else if (Vid == "technical" || Vid == "Technical") {
        cout << "Technical diving: decompression required\n";
    }

    cout << "=====================\n";
}

// ================= СОХРАНЕНИЕ В ФАЙЛЫ =================

void DiveComp::Save() {
    ofstream file("Watches.txt", ios::app);
    if (!file.is_open()) return;

    file << id << "|"
        << user_id << "|"
        << "DiveComp" << "|"
        << Vid << "|"
        << Count << "|"
        << TimeCicle << "|"
        << NumberDives << "|"
        << Temp << "|"
        << CurDepth << "|"
        << Mix << "|"
        << endl;
}

void DiveComp::CreateDiveComp(const DiveComp& d) {
    try {
        ofstream file("DiveComp.txt", ios::app);
        if (!file.is_open()) return;

        file << d.Vid << "|"
            << d.Count << "|"
            << d.TimeCicle << "|"
            << d.NumberDives << "|"
            << d.Temp << "|"
            << d.CurDepth << "|"
            << d.Mix << std::endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка сохранения лога DiveComp: " << e.what() << endl;
    }
}