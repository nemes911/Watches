#pragma once
#include "Watcher.h"
#include <string>
class GTMWatches :
    public Watcher
{
private:

    int GTMOffset;
    std::string SecondZoneName;
public:
    
    
   
    static int count;
    static int nextid;
    int FlightTime = 0;
    int OriginalOffset;
    std::string SecondTime;
    static int GetCount();
    void SetSecondTime(std::string SecondZoneName);
    std::string GetSecondZoneName();
    void SetGTMOffset(int GTMOffset);
    int GetGTMOffset();
    int ExtractHours(const std::string& time);
    int ExtractMinutes(const std::string& time);
    void NextGTM(int gtm);
    void CalculateSecondTime();
    void StartFlight(int durationMinutes);
    void ChangeTimezone(int newOffset, std::string newZoneName);
    void SimulateFlightStep(int minutesPassed);
    void PrintStatus()const;
    void PrintFlightSummary() const;
    GTMWatches();
    GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName);
    ~GTMWatches();
    int GetAll() override;
    void Save() override;
    void Print() override;
    void operator++ (int);
    GTMWatches& operator++();
    void CreatedGTMWatches(const GTMWatches& gtm);

};

