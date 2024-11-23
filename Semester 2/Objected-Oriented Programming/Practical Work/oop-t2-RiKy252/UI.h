#pragma once
#include <iostream>
#include "Service.h"

class UI {
private:
    Service service;
public:
    UI();
    static void menu();
    void startApp();
};
