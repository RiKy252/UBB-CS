//
// Created by Riki on 5/24/2024.
//

#include "Service.h"

Service::Service(std::string fileName) {
    this->fileName = fileName;
    this->bills = new std::vector<Bill>;

    std::fstream file(this->fileName);

    Bill b;

    while (file >> b)
        this->bills->push_back(b);

    for (int i = 0; i < bills->size(); i++) {
        for (int j = i + 1; j < bills->size(); j++) {
            if (bills->at(i).getCompanyName() > bills->at(j).getCompanyName())
                std::swap(bills->at(i), bills->at(j));
        }
    }

    file.close();
}

Service::~Service() {
    delete[] this->bills;
}

std::vector<Bill> *Service::getBills() const {
    return this->bills;
}

float Service::calculateUnpaidBills(std::string companyName) {
    float res = 0;
    for (auto& bill : *bills) {
        if (bill.getCompanyName() == companyName && !bill.isItPaid()) {
            res += bill.getSum();
        }
    }
    return res;
}
