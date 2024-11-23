#pragma once
#include <string>

class MedicalAnalysis
{
protected:
    std::string date;
public:
    virtual bool isResultOk() = 0;
    virtual std::string toString() = 0;
    int getMonth();
    std::string getDate();
};

int MedicalAnalysis::getMonth() {
    return std::stoi(date.substr(5, 2));
}

std::string MedicalAnalysis::getDate() {
    return date;
}
