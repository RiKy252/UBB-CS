#pragma once
#include "Bill.h"
#include <vector>
#include <fstream>

class Service {
private:
    std::vector<Bill>* bills;
    std::string fileName;
public:
    Service(std::string fileName);
    ~Service();
    std::vector<Bill>* getBills() const;
    float calculateUnpaidBills(std::string companyName);
};
