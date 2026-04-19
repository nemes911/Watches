#pragma once
#include <string>
#include <list>
class User
{
public:
	std::string name;
	int GTM;
	std::string Geografy;
	User(){}
	~User(){}
	User(std::string name, int GTM, std::string Geografy) {
		this->name = name;
		this->GTM = GTM;
		this->Geografy = Geografy;
	}
	
};

