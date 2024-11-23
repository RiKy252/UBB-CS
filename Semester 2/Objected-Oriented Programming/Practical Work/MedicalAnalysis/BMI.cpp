#include "BMI.h"

BMI::BMI(std::string date, double value){
    this->date = date;
    this->value = value;
}

bool BMI::isResultOk() {
    return this->value >= 18.5 && this->value <= 25;
}

std::string BMI::toString() {
    return "BMI Analysis: " + this->date + " value: " + std::to_string(this->value);
}
