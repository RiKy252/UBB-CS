#pragma once
#include "Engine.h"

class TurboEngine : public Engine {
public:
    TurboEngine();
    double getPrice() override;
    string toString() override;
};
