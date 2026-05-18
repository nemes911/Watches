#include "DivingWatches.h"
#include <fstream>
#include "iostream"
#include "conio.h"
#include <string>
#include "Logical.h"

using namespace std;

int DivingWatches::count = 0;
int DivingWatches::nextid = 0;


void DivingWatches::SetDepth(int Depth) {
	this->Depth = Depth;
}
int DivingWatches::GetDepth() {
	return this->Depth;
}

void DivingWatches::SetBezel(int Bezel) {
	this->Bezel = Bezel;
}

int DivingWatches::GetBezel() {
	return this->Bezel;
}

void DivingWatches::BeginTheUnderwater() {
	if (Time.empty()) {
		std::cout << "Ошибка: время не задано!\n";
		return;
	}

	Bezel = ExtractMinutes(Time);

	std::cout << "=== Погружение начато ===\n";
	std::cout << "Время старта: " << Time << "\n";

	// Автоматический спуск на заданную глубину
	if (Depth > 0) {
		DescentToDepth(Depth);
	}
}

int DivingWatches::GetDiveDuration(string currentTime) {
	if (currentTime.empty()) return 0;

	int start = Bezel;
	int now = ExtractMinutes(currentTime);
	int duration = now - start;
	if (duration < 0) duration += 60;

	return duration;
}


int DivingWatches::ExtractMinutes(const std::string& time) {
	return stoi(time.substr(3, 2));
}

std::string DivingWatches::GetCurrentTime() const {
	return Time;
}

int DivingWatches::GetDiveTime() {
	if (Time.empty() || Bezel == 0)
		return 0;

	int currentMinutes = ExtractMinutes(Time);
	int startMinutes = Bezel;

	int duration = currentMinutes - startMinutes;
	if (duration < 0) duration += 60;   // если перешли через час


	return duration;
}

DivingWatches::DivingWatches() { id = GetNextWatchId();  count++; }

int DivingWatches::GetCount() {
	return count;
}

DivingWatches::DivingWatches(std::string Time, bool Type, int Depth, int Bezel) 
	: Time(Time), Type(Type), Depth(Depth), Bezel(Bezel) {
	id = GetNextWatchId();
	count++;
	CtreatedDivingWatches(*this);
}

DivingWatches::~DivingWatches() { count--; }

int DivingWatches::GetAll(){
	return count;
}

void DivingWatches::Save() {
	ofstream file("Watches.txt", ios::app);

	file << id << "|"
		<< user_id << "|"
		<< "Diving" << "|"
		<< Time << "|"
		<< Type << "|"
		<< Depth << "|"
		<< Bezel << "|"
		<< endl;

}

void DivingWatches::Print() {

}

void DivingWatches::CtreatedDivingWatches(const DivingWatches& w) {
	

	try {
		ofstream file("DivingWatches.txt", ios::app);
		file << w.Time << "|"
			<< w.Type << "|"
			<< w.Depth << "|"
			<< w.Bezel << std::endl;
	}
	catch (exception& e) {
		cout << "Critical error: " << e.what() << endl;
	}
}

void DivingWatches::AddDiveTime(int minutes) {
	if (minutes <= 0) return;


	Time = AddMinutesToTime(Time, minutes);

	std::cout << "Прошло " << minutes << " минут под водой. Текущее время: " << Time << "\n";
}

int DivingWatches::CalculateTimeByDepth(int depth) const
{
	if (depth <= 0) return 0;


	if (depth <= 20)
		return (depth / 5) * 1 + (depth % 5 != 0 ? 1 : 0);
	else if (depth <= 40)
		return (depth / 5) * 2;
	else
		return (depth / 5) * 3;   
}


void DivingWatches::DescentToDepth(int targetDepth)
{
	if (targetDepth <= 0) return;

	int timeAdded = CalculateTimeByDepth(targetDepth);

	Depth = targetDepth;
	Time = AddMinutesToTime(Time, timeAdded);

	std::cout << "Спуск на " << targetDepth << " метров...\n";
	std::cout << "Затрачено времени: +" << timeAdded << " минут\n";
	std::cout << "Текущее время: " << Time << "\n";
}

// Всплытие
void DivingWatches::AscendFromDepth(int meters)
{
	if (meters <= 0 || Depth == 0) {
		std::cout << "Вы уже на поверхности.\n";
		return;
	}

	int timeAdded = (meters / 5) * 2 + (meters % 5 != 0 ? 1 : 0); 

	Depth = std::max(0, Depth - meters);
	Time = AddMinutesToTime(Time, timeAdded);

	std::cout << "Всплытие на " << meters << " метров...\n";
	std::cout << "Затрачено времени: +" << timeAdded << " минут\n";
	std::cout << "Текущая глубина: " << Depth << " м | Время: " << Time << "\n";
}