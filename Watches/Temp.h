#pragma once

class Temp
{
public:
	float Celse;
	float Farengaet;
	Temp(){}
	~Temp(){}
	Temp(float Celse) {
		this->Celse = Celse;
	}
	Temp(float Farengaet) {
		this->Farengaet = Farengaet;
	}
};

