#pragma once
#include "BP.h"
#include "BMI.h"
#include "MedicalAnalysis.h"
#include <vector>
#include <fstream>

class Person {
private:
    std::string name;
    std::vector<MedicalAnalysis*> analyses;
public:
    Person(std::string name);

    Person();

    void addAnalysis(MedicalAnalysis* analysis);
    std::vector<MedicalAnalysis*> getAllAnalyses();
    std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);
    bool isIll(int month);
    std::vector<MedicalAnalysis*> getAnalysesBetweenDates(std::string date1, std::string date2);
    void writeToFile(std::string filename, std::string date1, std::string date2);
};
