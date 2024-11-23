//
// Created by Riki on 4/17/2024.
//

#include "CSVRepo.h"

CSVRepo::CSVRepo(std::string filename) : Repository(filename) {
    this->filename = filename;
}

CSVRepo::CSVRepo() {
    this->filename = "";
}

void CSVRepo::writeToFile() {
    std::ofstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (const Movie& m : *this->movies)
    {
        file << m << std::endl;
    }

    file.close();
}

void CSVRepo::openFile() {
    std::string toBeOpened = "C:\\Users\\Riki\\Documents\\Facultate\\Sem-2\\OOP\\a8-9\\cmake-build-debug\\WatchList.CSV";
    ShellExecuteA(NULL, NULL, "EXCEL.EXE", toBeOpened.c_str(), NULL, SW_SHOWMAXIMIZED);
}
