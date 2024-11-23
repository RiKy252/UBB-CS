//
// Created by Riki on 6/21/2024.
//

#include "Service.h"

Service::Service() {
    this->repository = new Repository();
}

Repository *Service::getRepo() {
    return this->repository;
}

void Service::addPatient(Patient p) {
    this->repository->addPatient(p);
    this->notify();
}
