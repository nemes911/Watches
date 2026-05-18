#include <iostream>
#include <string>
#include "Watcher.h"

#pragma once
class DivingWatches : public Watcher
{
protected:
	
	bool Type;
	int Depth;
	int Bezel;
public:
	

	
	std::string Time;
	static int nextid;
	static int count;

	static int GetCount();

	void SetDepth(int Depth);

	int GetDepth();

	void SetBezel(int bezel);

	int GetBezel();

	void BeginTheUnderwater();

	int GetDiveDuration(std::string currentTime);

	int ExtractMinutes(const std::string& time);

	int GetDiveTime();

	std::string GetCurrentTime() const;

	DivingWatches();

	DivingWatches(std::string Time, bool Type, int Depth, int Bezel);

	~DivingWatches();

	int GetAll() override;
	
	void Save() override;

	void Print() override;

	void CtreatedDivingWatches(const DivingWatches& w);

	void AddDiveTime(int minutes);

	void DescentToDepth(int targetDepth);   // Спуск на заданную глубину
	void AscendFromDepth(int meters);       // Всплытие
	int CalculateTimeByDepth(int depth) const;
};

