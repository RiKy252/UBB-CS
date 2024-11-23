#pragma once
#include "MedicalAnalysis.h"

class BP : public MedicalAnalysis {
private:
    int systolicValue;
    int diastolicValue;
public:
    BP(std::string date, int systolicValue, int diastolicValue);
    bool isResultOk() override;
    std::string toString() override;
};
