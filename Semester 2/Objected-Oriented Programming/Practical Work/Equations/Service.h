#pragma once
#include "Equations.h"
#include <vector>
#include <fstream>

class Service {
private:
    std::vector<Equations>* equations;
public:
    Service(std::string filename);
    std::vector<Equations>* getEquations();
    ~Service();
};
