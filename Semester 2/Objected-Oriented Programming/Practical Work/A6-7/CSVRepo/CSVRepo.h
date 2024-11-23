#pragma once
#include "Repo/repo.h"

class CSVRepo : public Repository {
public:
    CSVRepo(std::string filename);
    void writeToFile() override;
    void openFile() override;
    CSVRepo();
};
