#include "DivingWatches.h"

int DivingWatches::count = 0;


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

DivingWatches::DivingWatches() { count++; }

DivingWatches::DivingWatches(std::string Time, bool Type, int Depth, int Bezel) {
	this->Time = Time;
	this->Type = Type;
	this->Depth = Depth;
	this->Bezel = Bezel;
	count++;
}

DivingWatches::~DivingWatches() { count--; }

int DivingWatches::GetAll(){
	return count;
}
