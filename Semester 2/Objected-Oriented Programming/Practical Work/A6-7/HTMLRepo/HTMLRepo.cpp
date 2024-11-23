//
// Created by Riki on 4/17/2024.
//

#include "HTMLRepo.h"

HTMLRepo::HTMLRepo(const std::string& filename) : Repository(filename) {
    this->filename = filename;
}

void HTMLRepo::writeToFile() {
    std::ofstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");
    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "   <title>WatchList</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "   <tr>\n";
    file << "       <td>Movie Title</td>\n";
    file << "       <td>Genre</td>\n";
    file << "       <td>Year of Release</td>\n";
    file << "       <td>Number of Likes</td>\n";
    file << "       <td>Trailer Link</td>\n";
    file << "   </tr>\n";
    for (Movie m : *this->movies)
    {
        file << "   <tr>\n";
        file << "       <td>" << m.getTitle() << "</td>\n";
        file << "       <td>" << m.getGenre() << "</td>\n";
        file << "       <td>" << m.getReleaseYear() << "</td>\n";
        file << "       <td>" << m.getNumberOfLikes() << "</td>\n";
        file << "       <td><a href=\"" << m.getTrailer() << "\">Link</a></td>\n";
        file << "   </tr>\n";
    }
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";
    file.close();
}

void HTMLRepo::openFile() {
    std::string toBeOpened = "C:\\Users\\Riki\\Documents\\Facultate\\Sem-2\\OOP\\oop-a6-7-RiKy252\\cmake-build-debug\\WatchList.html";
    ShellExecuteA(NULL, NULL, "opera.exe", toBeOpened.c_str(), NULL, SW_SHOWMAXIMIZED);
}
