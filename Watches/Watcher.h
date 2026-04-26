#include <iostream>
#include <list>

#pragma once
class  Watcher
{
public:
	std::string Time;
	bool Type_time;
	virtual int GetAll() = 0;

	virtual ~Watcher() = default;
};

