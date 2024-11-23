#pragma once
#include <string>

using namespace std;

class Doctor {
private:
    string name;
    string specialisation;
public:
    Doctor();
    Doctor(string name, string specialisation);
    string getName();
    string getSpecialisation();
};
