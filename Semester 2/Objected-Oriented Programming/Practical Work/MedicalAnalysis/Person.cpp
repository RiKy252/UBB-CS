#include "Person.h"

Person::Person(std::string name) {
    this->name = name;
}

void Person::addAnalysis(MedicalAnalysis* analysis) {
    this->analyses.push_back(analysis);
}

std::vector<MedicalAnalysis*> Person::getAllAnalyses() {
    return this->analyses;
}

std::vector<MedicalAnalysis*> Person::getAnalysesByMonth(int month) {
    std::vector<MedicalAnalysis*> result;
    for (auto a : this->analyses) {
        if (a->getMonth() == month) {
            result.push_back(a);
        }
    }
    return result;
}

bool Person::isIll(int month) {
    std::vector<MedicalAnalysis*> a = this->getAnalysesByMonth(month);
    for (auto analysis : a) {
        if (!analysis->isResultOk())
            return true;
    }
    return false;
}

std::vector<MedicalAnalysis *> Person::getAnalysesBetweenDates(std::string date1, std::string date2) {
    std::vector<MedicalAnalysis*> new_v;
    for (auto a : this->analyses) {
        if (a->getDate() >= date1 && a->getDate()<=date2)
            new_v.push_back(a);
    }
    return new_v;
}

void Person::writeToFile(std::string filename, std::string date1, std::string date2) {
    std::ofstream f(filename);
    for (auto a : this->getAnalysesBetweenDates(date1,date2)) {
        f<<a->toString();
        f<<'\n';
    }
}

Person::Person() {
    this->name = "";
}

