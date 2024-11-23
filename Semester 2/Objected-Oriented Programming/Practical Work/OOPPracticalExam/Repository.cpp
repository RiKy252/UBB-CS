//
// Created by Riki on 6/21/2024.
//

#include "Repository.h"

Repository::Repository() {
    ifstream file("doctors.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, specialisation;
        getline(ss, name, ',');
        getline(ss, specialisation, ',');
        Doctor d(name, specialisation);
        doctors.push_back(d);
    }
    file.close();
    ifstream file2("patients.txt");
    string line2;
    while (getline(file2, line2)) {
        stringstream ss(line2);
        string name2, diagnosis, specialisationNeeded, currentDoctor, admissionDate;
        getline(ss, name2, ',');
        getline(ss, diagnosis, ',');
        getline(ss, specialisationNeeded, ',');
        getline(ss, currentDoctor, ',');
        getline(ss, admissionDate, ',');
        Patient p(name2, diagnosis, specialisationNeeded, currentDoctor, admissionDate);
        patients.push_back(p);
    }
    file2.close();
    for (int i = 0; i < patients.size(); i++) {
        for (int j = i + 1; j < patients.size(); j++) {
            if (patients.at(i).getAdmissionDate() > patients.at(j).getAdmissionDate()) {
                swap(patients.at(i), patients.at(j));
            }
        }
    }
}

vector<Doctor>& Repository::getDoctors() {
    return doctors;
}

vector<Patient>& Repository::getPatients() {
    return patients;
}

void Repository::addPatient(Patient p) {
    this->patients.push_back(p);
}

