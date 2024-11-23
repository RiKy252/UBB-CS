#pragma once
#include <string>
#include <sstream>

class Bill {
private:
    std::string companyName;
    std::string serialNumber;
    float sum;
    bool isPaid;
public:
    Bill();
    Bill(std::string companyName, std::string serialNumber, float sum, bool isPaid);
    std::string getCompanyName() const;
    float getSum() const;
    bool isItPaid() const;
    friend std::istream& operator>>(std::istream& in, Bill& bill);
};

