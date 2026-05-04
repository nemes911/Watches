#include <iostream>
#include <list>

#pragma once
class  Watcher
{
public:
	std::string Time;
	bool Type_time;
	virtual int GetAll() = 0;
	int id;
	int user_id;
	virtual void Save() = 0;
	virtual void Print() = 0;
	virtual ~Watcher() = default;
};

