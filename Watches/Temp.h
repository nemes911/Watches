#pragma once

class Temp
{
public:
	float Celse;
	float Farengaet;
	Temp() : Celse(0), Farengaet(0) {}
	~Temp(){}
	Temp(float Celse, float Farengaet) {
		this->Celse = Celse;
		this->Farengaet = Farengaet;
	}
	static Temp fromCelsius(float c) {
		Temp t;
		t.Celse = c;
		t.Farengaet = c * 9 / 5 + 32;
		return t;
	}
	
	static Temp fromFarengate(float f) {
		Temp t;
		t.Farengaet = f;
		t.Celse = (f - 32) * 5 / 9;
		return t;
	}

	friend std::ostream& operator<<(std::ostream& os, const Temp& t) {
		os << t.Celse << " C";
		return os;
	}

	float toFarengaet() const {
		return Celse * 9 / 5 + 32;
	}
};

