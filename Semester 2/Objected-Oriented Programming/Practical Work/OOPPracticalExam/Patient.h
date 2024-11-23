#pragma once
#include <string>

using namespace std;

class Patient {
private:
    string name;
    string diagnosis;
    string specialisationNeeded;
    string currentDoctor;
    string admissionDate;
public:
    Patient(string name, string diagnosis, string specialisationNeeded, string currentDoctor, string admissionDate);
    string getName();
    string getDiagnosis();
    string getSpecialisationNeeded();
    string getCurrentDoctor();
    string getAdmissionDate();
    void setDiagnosis(string newDiagnosis);
    void setSpecialisation(string newSpec);
    void setCurrentDoctor(string newDoctor);
    string toString();
};
