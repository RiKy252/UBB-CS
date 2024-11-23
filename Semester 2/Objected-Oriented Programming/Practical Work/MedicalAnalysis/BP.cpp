//
// Created by Riki on 4/22/2024.
//

#include "BP.h"

BP::BP(std::string date, int systolicValue, int diastolicValue) {
    this->date = date;
    this->systolicValue = systolicValue;
    this->diastolicValue = diastolicValue;
}

bool BP::isResultOk() {
    return (this->systolicValue >= 90 && this->systolicValue <= 119) && (this->diastolicValue >= 60 && this->diastolicValue <= 79);
}

std::string BP::toString() {
    return "BP Analysis: " + this->date + " systolic value = " + std::to_string(systolicValue) + " diastolic value = " + std::to_string(diastolicValue);
}
