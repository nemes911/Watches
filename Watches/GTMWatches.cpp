#include "GTMWatches.h"

int GTMWatches::count = 0;


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

GTMWatches::GTMWatches() { count++; }
GTMWatches::~GTMWatches() { count--; }
GTMWatches::GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName) {
	this->SecondTime = SecondTime;
	this->GTMOffset = GTMOffset;
	this->SecondZoneName = SecondZoneName;
	count++;
}

int GTMWatches::GetAll() {
	return count;
}

GTMWatches GTMWatches::operator++ (int) {
	GTMWatches gtm = *this;
	gtm++;
	return gtm;
}