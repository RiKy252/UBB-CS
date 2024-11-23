#pragma once
#include <string>
using namespace std;

class Appliance {
protected:
    string id;
public:
    //Appliance(string id);

    Appliance();

    virtual double consumedElectricity() = 0;
    virtual string toString() = 0;
    string getId();
};
