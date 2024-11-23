//
// Created by Riki on 6/21/2024.
//

#include "Doctor.h"

Doctor::Doctor(string name, string specialisation) {
    this->name = name;
    this->specialisation = specialisation;
}

string Doctor::getName() {
    return this->name;
}

string Doctor::getSpecialisation() {
    return this->specialisation;
}

Doctor::Doctor() {
    this->name = "";
    this->specialisation = "";
}
