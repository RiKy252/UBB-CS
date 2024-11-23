#pragma once
#include "Service.h"
#include "WashingMachine.h"
#include "Refrigerator.h"
#include <iostream>

class UI {
private:
    Service service;
public:
    UI();
    static void menu();
    void run();
};
