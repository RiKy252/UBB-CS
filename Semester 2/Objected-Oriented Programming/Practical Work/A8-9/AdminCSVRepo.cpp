//
// Created by Riki on 4/17/2024.
//

#include "AdminCSVRepo.h"

AdminCSVRepo::AdminCSVRepo(std::string filename) {
    this->filename = filename;
    this->readFromFile();

}
