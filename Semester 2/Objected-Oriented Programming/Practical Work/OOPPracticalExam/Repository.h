#pragma once
#include "Doctor.h"
#include "Patient.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Repository {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;
public:
    Repository();
    vector<Doctor>& getDoctors();
    vector<Patient>& getPatients();
    void addPatient(Patient p);
};
