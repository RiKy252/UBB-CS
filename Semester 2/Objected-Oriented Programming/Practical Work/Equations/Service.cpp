//
// Created by Riki on 5/28/2024.
//

#include "Service.h"

Service::Service(std::string filename) {
    std::ifstream file(filename);
    Equations e;
    this->equations = new std::vector<Equations>;
    while (file >> e) {
        this->equations->push_back(e);
    }
}

Service::~Service() {
    delete[] this->equations;
}

std::vector<Equations> *Service::getEquations() {
    return this->equations;
}
