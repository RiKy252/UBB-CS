#pragma once
#include "CSVRepo/CSVRepo.h"
class AdminCSVRepo : public CSVRepo{
public:
    AdminCSVRepo(std::string filename);
};
