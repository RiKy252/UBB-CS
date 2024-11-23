//
// Created by Riki on 6/21/2024.
//

#include "Patient.h"

Patient::Patient(string name, string diagnosis, string specialisationNeeded, string currentDoctor, string admissionDate) {
    this->name = name;
    this->diagnosis = diagnosis;
    this->specialisationNeeded = specialisationNeeded;
    this->currentDoctor = currentDoctor;
    this->admissionDate = admissionDate;
}

string Patient::getName() {
    return this->name;
}

string Patient::getDiagnosis() {
    return this->diagnosis;
}

string Patient::getSpecialisationNeeded() {
    return this->specialisationNeeded;
}

string Patient::getCurrentDoctor() {
    return this->currentDoctor;
}

string Patient::getAdmissionDate() {
    return this->admissionDate;
}

string Patient::toString() {
    return this->name + ", " + this->diagnosis + ", " + this->specialisationNeeded + ", " + this->currentDoctor + ", " + this->admissionDate;
}

void Patient::setDiagnosis(string newDiagnosis) {
    this->diagnosis = newDiagnosis;
}

void Patient::setSpecialisation(string newSpec) {
    this->specialisationNeeded = newSpec;
}

void Patient::setCurrentDoctor(string newDoctor) {
    this->currentDoctor = newDoctor;
}
