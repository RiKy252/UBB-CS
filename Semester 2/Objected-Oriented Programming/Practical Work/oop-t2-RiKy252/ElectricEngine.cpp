#include "ElectricEngine.h"

double ElectricEngine::getPrice() {
    return this->basePrice + (this->autonomy * 0.01);
}

ElectricEngine::ElectricEngine(int autonomy) {
    this->autonomy = autonomy;
    this->basePrice = 3000;
}

string ElectricEngine::toString() {
    return "Electric engine with autonomy = " + to_string(autonomy) + " and price = " + to_string(this->getPrice());
}
