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
    int MaxDepth;
    int DiveTime;
    char* Mix;

    static int GetCount();

    void SetMaxDepth(int depth);
    int GetMaxDepth() const;

    void StartDescent();

    bool Ascend(int meters = 1);

    void Stay(int minutes);

    void Calculate();

    void PrintStatus() const;

    void SetMix(char* Mix);
    char* GetMix();

    void SetTemp(int Temp);

    int GetTemp();

    void Save() override;

    DiveComp();
    DiveComp(char* Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, char* Mix);
    ~DiveComp();
    DiveComp operator--(int);
    DiveComp& operator--();

    int GetAll();



    void CreateDiveComp(const DiveComp& d);
};

