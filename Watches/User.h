#pragma once
#include <string>
#include <list>
#include "Watcher.h"
#include <vector> 

using namespace std;

class User
{
private:
	enum state {
		FLYING,
		SWIMING,
		STAY
	};
	state currentstate = STAY;
	std::vector<Watcher*> watches;

public:
	int id;
	std::string name;
	int GTM;
	static int count;
	std::string Geografy;
	User();
	~User();
	User(std::string name, int GTM, std::string Geografy);
	void ChangheState(state state);
	void CreatedUser(const User& u);
	int Trigger_Before_Create();
	void AddWatch(Watcher* w);
	const std::vector<Watcher*>& GetWatches() const;
	void PrintWatches();
	static int GetCount();
	int GetWatchCount() const;
	void ClearWatches(); 
};

