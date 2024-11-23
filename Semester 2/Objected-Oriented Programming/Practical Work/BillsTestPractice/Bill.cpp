//
// Created by Riki on 5/24/2024.
//

#include "Bill.h"

Bill::Bill(std::string companyName, std::string serialNumber, float sum, bool isPaid) {
    this->companyName = companyName;
    this->serialNumber = serialNumber;
    this->sum = sum;
    this->isPaid = isPaid;
}

std::string Bill::getCompanyName() const {
    return this->companyName;
}

float Bill::getSum() const {
    return this->sum;
}

bool Bill::isItPaid() const {
    return this->isPaid;
}

Bill::Bill() {
    this->companyName = "";
    this->serialNumber = "";
    this->sum = 0;
    this->isPaid = false;
}

std::istream &operator>>(std::istream &in, Bill &bill) {
    std::string line;
    std::getline(in, line);
    if (line.empty())
        return in;
    std::stringstream stream(line);
    std::string companyName, serialNumber, sum, isPaid;
    std::getline(stream, companyName, ';');
    bill.companyName = companyName;
    std::getline(stream, serialNumber, ';');
    bill.serialNumber = serialNumber;
    std::getline(stream, sum, ';');
    bill.sum = std::stof(sum);
    std::getline(stream, isPaid, ';');
    if (isPaid == "true")
        bill.isPaid = true;
    else
        bill.isPaid = false;
    return in;
}
