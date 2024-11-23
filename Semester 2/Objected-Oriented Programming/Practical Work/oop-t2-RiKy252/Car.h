#pragma once
#include "Engine.h"
#include <string>

using namespace std;

class Car {
private:
    string bodyStyle;
    Engine* engine;
public:
    Car(string bodyStyle, Engine* engine);
    double computePrice();
    string toString();
};
