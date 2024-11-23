//
// Created by Riki on 4/22/2024.
//

#include "WashingMachine.h"

WashingMachine::WashingMachine(string id, double consumedElectricityPerHour) {
    this->id = id;
    this->consumedElectricityPerHour = consumedElectricityPerHour;
}

double WashingMachine::consumedElectricity() {
    return 20 * consumedElectricityPerHour;
}

string WashingMachine::toString() {
    return "Washing machine: " + id + ", consumed electricity: " + to_string(consumedElectricity()) + " KW" + " consumed per hour: " + to_string(consumedElectricityPerHour) + " KW";
}
