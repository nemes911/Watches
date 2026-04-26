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
    void SetSecondTime(std::string SecondZoneName);
    std::string GetSecondZoneName();
    void SetGTMOffset(int GTMOffset);
    int GetGTMOffset();
    GTMWatches();
    GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName);
    ~GTMWatches();
    int GetAll() override;

    GTMWatches operator++ (int);


};

