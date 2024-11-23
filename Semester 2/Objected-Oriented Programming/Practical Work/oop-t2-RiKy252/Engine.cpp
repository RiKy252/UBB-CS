#include "Engine.h"

double Engine::getPrice() {
    return this->basePrice;
}

Engine::Engine() {
    this->basePrice = 0;
}
