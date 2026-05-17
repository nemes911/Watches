#include "User.h"
#include <fstream>
#include "iostream"
#include "conio.h"
#include <string>
#include "GTMWatches.h"
#include "DiveComp.h"
#include "DivingWatches.h"
#include "Watcher.h"
#include <vector>

using namespace std;

int User::count = 0;

User::User() { count++; }
User::User(std::string name, int GTM, std::string Geografy) {
	this->id = 0;//Trigger_Before_Create();
	this->name = name;
	this->GTM = GTM;
	this->Geografy = Geografy;
	this->currentstate = STAY;
	count++;
	//CreatedUser(*this);
}
User::~User() { count--;

for (auto w : watches) {
	delete w;
	}
}

void User::ChangheState(state state) {
	this->currentstate = state;
}
/*Записать созданного Юзера в файл*/
void User::CreatedUser(const User& u) {
	try {
		ofstream file("User.txt", ios::app);
		file << u.id << "|"
			<< u.name << "|"
			<< u.Geografy << "|"
			<< u.currentstate
			<< std::endl;
	}
	catch (exception &e) {
		cout << "Critical error: " << e.what() << endl;
	}
}
/* Тригер для задачи id пользователя */
int User::Trigger_Before_Create() {
	ifstream file("User.txt");

	if (!file.is_open()) {
		return 0;
	}

	string line;
	int LastId = -1;

	while (getline(file, line)) {
		if (line.empty()) continue;

		size_t pos = line.find('|');
		if (pos != string::npos) {
			int id = stoi(line.substr(0, pos));
			LastId = id;
		}
	}

	return LastId + 1;
}
/* Добавить часы Юзеру*/

void User::AddWatch(Watcher* w) {
	w->user_id = this->id;
	watches.push_back(w);

	w->Save();
}

void User::PrintWatches() {
	/*User print*/ cout << "USer:" << User::GetCount() << endl;
	cout << "GTMWatches:" << GTMWatches::GetCount() << endl;
	cout << "DiveComp:" << DiveComp::GetCount() << endl;
	cout << "DivingWatches" << DivingWatches::GetCount() << endl;
}

 const std::vector<Watcher*>& User::GetWatches() const{
	return watches;
}

 int User::GetCount() {
	 return count;
}

 int User::GetWatchCount() const{
	 return watches.size();
 }

 void User::ClearWatches() {
	 for (auto* w : watches) 
		 delete w;
	 watches.clear();
 }