#pragma once
#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

class UI {
private:
    Person p;
public:
    UI();
    static void menu();
    void startApp();
};
