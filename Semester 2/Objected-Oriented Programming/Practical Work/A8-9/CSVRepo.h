#pragma once
#include "repo.h"

class CSVRepo : public Repository {
public:
    CSVRepo(std::string filename);
    void writeToFile() override;
    void openFile() override;
    CSVRepo();
};
