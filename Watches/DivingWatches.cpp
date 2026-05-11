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
	Bezel = ExtractMinutes(Time);
	cout << "Начало погружения\n";
}

int DivingWatches::GetDiveDuration(string currentTime) {
	int start = Bezel;
	int now = ExtractMinutes(currentTime);

	int duration = now - start;

	if (duration < 0) duration += 60;

	return duration;
}


int DivingWatches::ExtractMinutes(const std::string& time) {
	return stoi(time.substr(3, 2));
}

int DivingWatches::GetDiveTime() {
	int current = ExtractMinutes(Time);
	int diff = current - Bezel;

	if (diff < 0) diff += 60; 

	return diff;
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