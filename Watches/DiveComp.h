#pragma once
#include "DivingWatches.h"
#include <list>
#include "Temp.h"
class DiveComp :
    public DivingWatches
{
public:
    char* Vid;
    int Count;
    int TimeCicle;
    int NumberDives;
    int Temp;
    Temp Temp_;
    int CurDepth;
    char* Mix;
    void SetMix(char* Mix) {
        this->Mix = Mix;
    }
    char* GetMix() {
        return this->Mix;
    }

    void SetTemp(int Temp) {
        this->Temp = Temp;
    }

    int GetTemp() {
        return this->Temp;
    }

    DiveComp() {}
    DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix) {
        this->Vid = Vid;
        this->Count = Count;
        this->TimeCicle = TimeCicle;
        this->Temp = Temp;
        this->CurDepth = CurDepth;
        this->Mix = Mix;
    }
    ~DiveComp(){}

    std::list<Watcher*> GetAll() override {

    }
    DiveComp operator--(int) {
        DiveComp temp = *this;
        if (CurDepth > 0) {
            CurDepth--;
        }
        return temp;
    }
};

