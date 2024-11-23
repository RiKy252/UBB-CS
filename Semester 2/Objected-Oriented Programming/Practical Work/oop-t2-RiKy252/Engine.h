#pragma once
#include <string>
using namespace std;

class Engine {
protected:
    double basePrice;
public:
    Engine();
    virtual double getPrice() = 0;
    virtual string toString() = 0;
};
