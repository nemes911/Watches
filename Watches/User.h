#pragma once
#include <string>
#include <list>
class User
{
private:
	enum state {
		FLYING,
		SWIMING,
		STAY
	};
	state currentstate = STAY;

public:
	int id;
	std::string name;
	int GTM;
	static int count;
	std::string Geografy;
	User();
	~User();
	User(int id, std::string name, int GTM, std::string Geografy);
	void ChangheState(state state);
	void CreatedUser();

};

