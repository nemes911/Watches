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
	if (durationMinutes <= 0)
    {
        std::cout << "Ошибка: продолжительность полёта должна быть больше 0.\n";
        return;
    }

    FlightTime = durationMinutes;      // Общая продолжительность полёта
    OriginalOffset = GTMOffset;        // Запоминаем исходный пояс

    std::cout << "\n=== Полёт успешно начат ===\n";
    std::cout << "Продолжительность: " << durationMinutes << " минут ("
              << durationMinutes / 60 << " ч " << durationMinutes % 60 << " мин)\n";
    std::cout << "Отправление: " << Time << " | " 
              << " (GMT" << (GTMOffset >= 0 ? "+" : "") << GTMOffset << ")\n";
    
    // Можно добавить небольшую паузу или разделитель
    std::cout << std::string(50, '-') << "\n";
}

void GTMWatches::ChangeTimezone(int newOffset, std::string newZoneName) {
	GTMOffset = newOffset;
	SecondZoneName = newZoneName;
	CalculateSecondTime();
	std::cout << "\n>>> Смена часового пояса на " << newZoneName
		<< " (GMT " << (newOffset >= 0 ? "+" : "") << newOffset << ") <<<\n";
}

void GTMWatches::SimulateFlightStep(int minutesPassed)
{
	FlightTime += minutesPassed;

	// Простая симуляция сдвига местного времени
	int h = ExtractHours(Time);
	int m = ExtractMinutes(Time);
	m += minutesPassed;
	h += m / 60;
	m %= 60;
	if (h >= 24) h -= 24;

	Time = (h < 10 ? "0" : "") + std::to_string(h) + ":" +
		(m < 10 ? "0" : "") + std::to_string(m);

	CalculateSecondTime();
}

void GTMWatches::PrintStatus() const
{
	std::cout << "\n=== GTM Watches - Полёт ===\n";
	std::cout << "Местное время:     " << Time << "\n";
	std::cout << "Второе время:      " << SecondTime << " (" << SecondZoneName << ")\n";
	std::cout << "Текущий GTM:       " << GTMOffset << "\n";
	std::cout << "Время в полёте:    " << FlightTime << " мин\n";
	std::cout << "===========================\n";
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