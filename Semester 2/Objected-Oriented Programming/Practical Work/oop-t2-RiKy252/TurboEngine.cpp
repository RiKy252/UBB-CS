#include "TurboEngine.h"

double TurboEngine::getPrice() {
    return this->basePrice + 100;
}

string TurboEngine::toString() {
    return "Turbo engine with price = " + to_string(this->getPrice());
}

TurboEngine::TurboEngine() {
    this->basePrice = 3000;
}
