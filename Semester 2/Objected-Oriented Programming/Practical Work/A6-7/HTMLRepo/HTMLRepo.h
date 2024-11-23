#pragma once
#include "Repo/repo.h"
class HTMLRepo : public Repository {
public:
    HTMLRepo(const std::string& filename);
    void writeToFile() override;
    void openFile() override;
};
