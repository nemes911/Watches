#pragma once
#include "Watcher.h"
#include <string>
class GTMWatches :
    public Watcher
{
public:
    std::string SecondTime;
    int GTMOffset;
    std::string SecondZoneName;
    static int count;
    static int nextid;
    static int GetCount();
    void SetSecondTime(std::string SecondZoneName);
    std::string GetSecondZoneName();
    void SetGTMOffset(int GTMOffset);
    int GetGTMOffset();
    int ExtractHours(const std::string& time);
    int ExtractMinutes(const std::string& time);
    void CalculateSecondTime();
    GTMWatches();
    GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName);
    ~GTMWatches();
    int GetAll() override;
    void Save() override;
    void Print() override;
    void operator++ (int);

    void CreatedGTMWatches(const GTMWatches& gtm);

};

