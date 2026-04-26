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

	static int count;

	void SetDepth(int Depth);

	int GetDepth();

	void SetBezel(int bezel);

	int GetBezel();

	DivingWatches();

	DivingWatches(std::string Time, bool Type, int Depth, int Bezel);

	~DivingWatches();

	int GetAll() override;
	

};

