#pragma once
#include "Appliance.h"
#include <vector>
#include <fstream>

class Service {
private:
    vector<Appliance*> appliances;
public:
    Service();
    void addAppliance(Appliance* appliance);
    vector<Appliance*> getAllAppliances();
    vector<Appliance*> getAppliancesConsumingMoreThan(double electricity);
    void writeToFile(string filename, double value);
};
