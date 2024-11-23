#include "Car.h"

double Car::computePrice() {
    double bodyStylePrice = 0;
    if (bodyStyle == "Sedan")
        bodyStylePrice += 8000;
    else if (bodyStyle == "Convertible")
        bodyStylePrice += 9000;
    return bodyStylePrice + this->engine->getPrice();
}

Car::Car(string bodyStyle, Engine *engine) {
    this->bodyStyle = bodyStyle;
    this->engine = engine;
}

string Car::toString() {
    return this->bodyStyle + " car, " + this->engine->toString() + ", total car price = " + to_string(this->computePrice());
}
