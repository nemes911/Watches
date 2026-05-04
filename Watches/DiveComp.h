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
    static int count;
    static int nextid;
    int CurDepth;
    char* Mix;

    static int GetCount();

    void SetMix(char* Mix);
    char* GetMix();

    void SetTemp(int Temp);

    int GetTemp();

    void Save() override;

    DiveComp();
    DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix);
    ~DiveComp();
    DiveComp operator--(int);

    int GetAll();

    void Calculate();

    void CreateDiveComp(const DiveComp& d);
};

