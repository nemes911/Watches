#include "DiveComp.h"
#include <fstream>
#include "Logical.h"
#include "iostream"
#include <iomanip>
#include <string>
#include "conio.h"

using namespace std;

int DiveComp::count = 0;
int DiveComp::nextid = 0;

void DiveComp::SetMix(char* Mix) {
	this->Mix = Mix;
}

int DiveComp::GetCount() {
	return count;
}

char* DiveComp::GetMix() {
	return this->Mix;
}

int DiveComp::GetTemp() {
	return this->Temp;
}

void DiveComp::SetTemp(int Temp) {
	this->Temp = Temp;
}

DiveComp::DiveComp() { id = GetNextWatchId();  count++; }
DiveComp::DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix) 
	: Vid(Vid), Count(Count), TimeCicle(TimeCicle), NumberDives(NumberDivers), Temp(Temp), CurDepth(CurDepth), Mix(Mix)
{
	id = GetNextWatchId();
	count++;
	MaxDepth = CurDepth;
	CreateDiveComp(*this);
}

DiveComp::~DiveComp() { count--; }

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
	}
	return *this;
}

int DiveComp::GetAll() {
	return count;
}

void DiveComp::StartDescent() {
	std::cout << "\n=== Начинается спуск ===\n";
	while (CurDepth < MaxDepth) {
		CurDepth += std::min(5, MaxDepth - CurDepth);
		std::cout << "Глубина: " << CurDepth << " м\n";
		AddLog("Desecent to" + std::to_string(CurDepth) + "m");
	}
	std::cout << "Достигнута максимальная глубина!\n";
}

bool DiveComp::Ascend(int meters) {
	if (CurDepth == 0) {
		std::cout << "Вы уже на поверхности!\n";
		return false;
	}
	CurDepth = std::max(0, CurDepth - meters);
	DiveTime += 2;                     

	if (CurDepth == 0)
		std::cout << ">>> Всплыли на поверхность <<<\n";
	else
		std::cout << "Всплытие. Текущая глубина: " << CurDepth << " м\n";

	AddLog("Ascended to " + std::to_string(CurDepth) + "m");
	return true;
}

void DiveComp::Stay(int minutes) {
	DiveTime += minutes;
	std::cout << "Пребывание на глубине " << minutes << " минут...\n";
	AddLog("Stayed " + std::to_string(minutes) + " min at " + std::to_string(CurDepth) + "m");
}

void DiveComp::PrintStatus() const
{
	std::cout << "\n=== DiveComp Status ===\n";
	std::cout << "Время: " << Time << "\n";
	std::cout << "Глубина: " << CurDepth << " / " << MaxDepth << " м\n";
	std::cout << "Время под водой: " << DiveTime << " мин\n";
	std::cout << "Температура: " << Temp << "°C\n";
	std::cout << "Смесь: " << (Mix ? Mix : "Air") << "\n";
	std::cout << "Режим: " << (Vid ? Vid : "Recreational") << "\n";
	std::cout << "========================\n";
}

void DiveComp::SetMaxDepth(int depth) {
	this->MaxDepth = depth;
}

int DiveComp::GetMaxDepth() const{
	return this->MaxDepth;
}

void DiveComp::Save() {
	ofstream file("Watches.txt", ios::app);

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

	
	if (strcmp(Mix, "air") == 0 && CurDepth > 30) {
		cout << "WARNING: Air not safe deeper than 30m\n";
	}
	else if (strcmp(Mix, "nitrox") == 0) {
		cout << "Nitrox allows longer bottom time\n";
	}
	else if (strcmp(Mix, "trimix") == 0) {
		cout << "Trimix suitable for deep diving\n";
	}

	
	if (strcmp(Vid, "freediving") == 0) {
		cout << "Freediving mode: short dive expected\n";
	}
	else if (strcmp(Vid, "technical") == 0) {
		cout << "Technical diving: decompression required\n";
	}

	cout << "=====================\n";
}

void DiveComp::CreateDiveComp(const DiveComp& d) {
	try {
		ofstream file("DiveComp.txt", ios::app);
		file << d.Vid << "|"
			<< d.Count << "|"
			<< d.TimeCicle << "|"
			<< d.NumberDives << "|"
			<< d.Temp << "|"
			<< d.CurDepth << "|"
			<< d.Mix << std::endl;
			
	}
	catch (exception& e) {

	}
}
