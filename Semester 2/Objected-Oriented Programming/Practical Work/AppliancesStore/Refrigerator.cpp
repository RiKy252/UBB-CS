//
// Created by Riki on 4/22/2024.
//

#include "Refrigerator.h"

Refrigerator::Refrigerator(string id, string usage, bool freezer) {
    this->id = id;
    this->usage = usage;
    this->freezer = freezer;
}

double Refrigerator::consumedElectricity() {
    double result = 0;
    if (this->usage == "A")
        result = 30 * 3;
    else
        result = 30 * 2;
    if (this->freezer)
        result += 20;
    return result;
}

string Refrigerator::toString() {
    return "Refrigerator: " + id + ", consumed electricity: " + to_string(consumedElectricity()) + " KW" + "class: " + usage + ", freezer: " + (freezer ? "yes" : "no");
}
