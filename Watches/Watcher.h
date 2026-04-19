#include <iostream>
#include <list>

#pragma once
class  Watcher
{
public:
	std::string Time;
	bool Type_time;
	virtual std::list<Watcher*> GetAll() = 0;

	virtual ~Watcher() {}
};

