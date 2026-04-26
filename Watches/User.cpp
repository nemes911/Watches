#include "User.h"

int User::count = 0;

User::User() { count++; }
User::User(int id, std::string name, int GTM, std::string Geografy) {
	this->id = id;
	this->name = name;
	this->GTM = GTM;
	this->Geografy = Geografy;
	count++;
}
User::~User() { count--; }

void User::ChangheState(state state) {
	this->currentstate = state;
}
