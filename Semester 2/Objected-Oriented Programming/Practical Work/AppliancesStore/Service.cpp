//
// Created by Riki on 4/22/2024.
//

#include "Service.h"
#include "Refrigerator.h"
#include "WashingMachine.h"

Service::Service() {
    this->appliances.push_back(new Refrigerator("1", "A", true));
    this->appliances.push_back(new Refrigerator("2", "A++", false));
    this->appliances.push_back(new WashingMachine("3", 2.5));
}

vector<Appliance*> Service::getAllAppliances() {
    return this->appliances;
}

vector<Appliance*> Service::getAppliancesConsumingMoreThan(double electricity) {
    vector <Appliance*> res;
    for (auto appliance : this->appliances) {
        if (appliance->consumedElectricity() > electricity) {
            res.push_back(appliance);
        }
    }
    return res;
}

void Service::writeToFile(string filename, double value) {
    vector <Appliance*> res;
    ofstream file(filename);
    for (auto appliance : this->appliances) {
        if (appliance->consumedElectricity() < value)
            res.push_back(appliance);
    }

    for (int i = 0; i < res.size(); i++) {
        for (int j = i + 1; j < res.size(); j++) {
            string iId = res[i]->getId();
            string jId = res[j]->getId();
            if (stoi(iId) > stoi(jId)) {
                Appliance* aux = res[i];
                res[i] = res[j];
                res[j] = aux;
            }
        }
    }


    for (auto appliance : res) {
        file << appliance->toString() << endl;
    }
    file.close();
}

void Service::addAppliance(Appliance* appliance) {
    this->appliances.push_back(appliance);
}
