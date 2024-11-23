#pragma once
#include "MedicalAnalysis.h"
class BMI : public MedicalAnalysis {
private:
    double value;
public:
    BMI(std::string date, double value);
    bool isResultOk() override;
    std::string toString() override;
};
