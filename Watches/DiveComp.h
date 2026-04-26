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
    int CurDepth;
    char* Mix;
    void SetMix(char* Mix);
    char* GetMix();

    void SetTemp(int Temp);

    int GetTemp();

    DiveComp();
    DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix);
    ~DiveComp();
    DiveComp operator--(int);

    int GetAll();
};

