#pragma once
#include "Appliance.h"

class WashingMachine : public Appliance {
private:
    double consumedElectricityPerHour;
public:
    WashingMachine(string id, double consumedElectricityPerHour);
    double consumedElectricity() override;
    string toString() override;
};
