#pragma once
#include "Engine.h"

class ElectricEngine : public Engine {
private:
    int autonomy;
public:
    ElectricEngine(int autonomy);
    double getPrice() override;
    string toString() override;
};
