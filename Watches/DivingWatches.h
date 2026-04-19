#include <iostream>
#include <string>
#include "Watcher.h"

#pragma once
class DivingWatches : public Watcher
{
public:
	std::string Time;
	bool Type;
	int Depth;
	int Bezel;

	void SetDepth(int Depth) {
		this->Depth = Depth;
	}

	int GetDepth() {
		return this->Depth;
	}

	void SetBezel(int bezel) {
		if (bezel > 0 && bezel < 60) {
			this->Bezel = bezel;
		}
	}

	int GetBezel() {
		return this->Bezel;
	}

	DivingWatches(){}

	DivingWatches(std::string Time, bool Type, int Depth, int Bezel) {
		this->Time = Time;
		this->Type = Type;
		this->Depth = Depth;
		this->Bezel = Bezel;
	}
	~DivingWatches(){}

	std::list<Watcher*> GetAll() override {
		
	}

};

