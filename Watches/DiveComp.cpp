#include "DiveComp.h"

int DiveComp::count = 0;


void DiveComp::SetMix(char* Mix) {
	this->Mix = Mix;
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

DiveComp::DiveComp() { count++; }
DiveComp::DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix) {
	this->Vid = Vid;
	this->Count = Count;
	this->TimeCicle = TimeCicle;
	this->NumberDives = NumberDivers;
	this->Temp = Temp;
	this->CurDepth = Depth;
	this->Mix = Mix;
	count++;
}

DiveComp::~DiveComp() { count--; }

DiveComp DiveComp::operator--(int) {
	DiveComp temp = *this;
	if (CurDepth > 0) {
		CurDepth--;
	}
	return temp;
}

int DiveComp::GetAll() {
	return count;
}
