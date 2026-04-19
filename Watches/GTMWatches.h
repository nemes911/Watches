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
    void SetSecondTime(std::string SecondZoneName) {
        this->SecondZoneName = SecondZoneName;
    }
    std::string GetSecondZoneName() {
        return this->SecondZoneName;
    }
    void SetGTMOffset(int GTMOffset) {
        this->GTMOffset = GTMOffset;
    }
    int GetGTMOffset() {
        return this->GTMOffset;
    }
    GTMWatches() {}
    GTMWatches(std::string SecondTime, int GTMOffset, std::string SecondZoneName) {
        this->SecondTime = SecondTime;
        this->GTMOffset = GTMOffset;
        this->SecondZoneName = SecondZoneName;
    }
    ~GTMWatches(){}
    std::list<Watcher*> GetAll() override {

    }
};

