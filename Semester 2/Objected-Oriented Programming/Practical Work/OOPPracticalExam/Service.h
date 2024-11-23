#pragma once
#include "Subject.h"
#include "Repository.h"

class Service : public Subject {
private:
    Repository* repository;
public:
    Service();
    Repository* getRepo();
    void addPatient(Patient p);
};
