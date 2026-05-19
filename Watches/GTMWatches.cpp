#include "GTMWatches.h"
#include <fstream>
#include "Logical.h"

using namespace std;

int GTMWatches::count = 0;
int GTMWatches::nextid = 0;

void GTMWatches::SetSecondTime(std::string SecondZoneName) {
	this->SecondTime = SecondZoneName;
}
std::string GTMWatches::GetSecondZoneName() {
	return this->SecondZoneName;
}
void GTMWatches::SetGTMOffset(int GTMOffset) {
	this->GTMOffset = GTMOffset;
}

int GTMWatches::GetGTMOffset() {
	return this->GTMOffset;
}	
int GTMWatches::ExtractHours(const std::string& time) {
	return stoi(time.substr(0, 2));
}
int GTMWatches::ExtractMinutes(const std::string& time) {
	return stoi(time.substr(3, 2));
}

int GTMWatches::GetCount() {
	return count;
}

void GTMWatches::CalculateSecondTime(){
	int h = ExtractHours(Time);
	int m = ExtractMinutes(Time);

	h += GTMOffset;

	if (h >= 24) h -= 24;
	if (h < 0) h += 24;

	SecondTime = (h < 10 ? "0" : "") + to_string(h) + ":" +
		(m < 10 ? "0" : "") + to_string(m);
}
GTMWatches::GTMWatches()  { id = GetNextWatchId(); count++; }
GTMWatches::~GTMWatches() { count--; }
GTMWatches::GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName) 
	: SecondTime(SecondTime), GTMOffset(GTMOffset), SecondZoneName(SecondZoneName)
{
	id = GetNextWatchId();
	count++;
	CreatedGTMWatches(*this);
}

int GTMWatches::GetAll() {
	return count;
}

void GTMWatches::operator++ (int) {
	GTMOffset++;
}

void GTMWatches::Save() {
	ofstream file("Watches.txt", ios::app);

	file << id << "|"
		<< user_id << "|"
		<< "GTM" << "|"
		<< SecondTime << "|"
		<< GTMOffset << "|"
		<< SecondZoneName
		<< endl;
}

void GTMWatches::Print() {
	cout << "\n=== GTM WATCH ===\n";
	cout << "Local time" << Time << endl;
	cout << "Second Zone:" << SecondZoneName << endl;
	cout << "GTM Offset:" << GTMOffset << endl;
	cout << "Second Time" << SecondTime << endl;
	cout << "==============\n";
}

void GTMWatches::StartFlight(int durationMinutes) {
	

    FlightTime = 0;      
    OriginalOffset = GTMOffset;        

    std::cout << "\n=== Полёт успешно начат ===\n";
	std::cout << "Время отправления: " << Time
		<< " | GMT" << (GTMOffset >= 0 ? "+" : "") << GTMOffset << "\n";
	std::cout << "==========================================\n";
    

}

void GTMWatches::ChangeTimezone(int newOffset, std::string newZoneName) {
	int oldOffset = GTMOffset;
	GTMOffset = newOffset;
	SecondZoneName = newZoneName;

	CalculateSecondTime();

	std::cout << "\n>>> Смена часового пояса ===\n";
	std::cout << "Было: GMT" << (oldOffset >= 0 ? "+" : "") << oldOffset
		<< "  →  Стало: GMT" << (newOffset >= 0 ? "+" : "") << newOffset
		<< " (" << newZoneName << ")\n";
}

void GTMWatches::NextGTM(int gtm) {
	SetGTMOffset(gtm);
}

void GTMWatches::SimulateFlightStep(int minutesPassed)
{
	if (minutesPassed <= 0) return;

	FlightTime += minutesPassed;

	
	int h = ExtractHours(SecondTime);
	int m = ExtractMinutes(SecondTime);

	m += minutesPassed;
	h += m / 60;
	m %= 60;

	if (h >= 24) h -= 24;
	if (h < 0)   h += 24;

	Time = (h < 10 ? "0" : "") + std::to_string(h) + ":" +
		(m < 10 ? "0" : "") + std::to_string(m);

	CalculateSecondTime();
	
}

void GTMWatches::PrintStatus() const
{
	std::cout << "\n=== GTM Watches — Полёт ===\n";
	std::cout << "Текущее время     : " << Time
		<< " (GMT" << (GTMOffset >= 0 ? "+" : "") << GTMOffset << ")\n";
	std::cout << "Второе время      : " << SecondTime
		<< " (" << SecondZoneName << ")\n";
	std::cout << "Время в полёте    : " << FlightTime << " минут\n";
	std::cout << "==================================\n";
}

void GTMWatches::CreatedGTMWatches(const GTMWatches& gtm) {
	try {
		ofstream file("GTMWatches.txt", ios::app);
		file << gtm.SecondTime << "|"
			<< gtm.GTMOffset << "|"
			<< gtm.SecondZoneName << "|"
			<< std::endl;
	}
	catch (exception& e) {
		cout << "Critical error: " << e.what() << endl;
	}
}


void GTMWatches::PrintFlightSummary() const {

}