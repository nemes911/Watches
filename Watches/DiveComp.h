#pragma once
#include "DivingWatches.h"
#include "Temp.h"
#include <string>

class DiveComp : public DivingWatches
{
private:
    // Заменили char* на std::string для безопасности
 
    std::string Mix;


    int NumberDives;
    int Temp;

    int MaxDepth;
 

public:
    static int count;
    static int nextid;
    int CurDepth;
    int DiveTime;
    int Count;
    int TimeCicle;
    std::string Vid;
    static int GetCount();

    void SetMaxDepth(int depth);
    int GetMaxDepth() const;
    void SetMix(std::string& Mix);
    std::string GetMix();
    void SetTemp(int Temp);
    int GetTemp();

    void StartDescent();
    bool Ascend(int meters = 1);
    void Stay(int minutes);
    void Calculate();
    void PrintStatus() const;

 
    DiveComp();
   
    DiveComp(std::string Vid, int Count, int TimeCicle, int NumberDivers, int Temp, int CurDepth, std::string Mix);
    ~DiveComp() override;

  
    DiveComp operator--(int);
    DiveComp& operator--();

    int GetAll() override;
    void Save() override;
    void CreateDiveComp(const DiveComp& d);
};