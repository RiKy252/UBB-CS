#include "repo.h"

Repository::Repository(std::string filename)
{
    this->movies = new std::vector<Movie>();
    this->filename = filename;
    // this->readFromFile();
}

Repository::Repository() {
    this->movies = new std::vector<Movie>();
}

Repository::~Repository()
{
	delete this->movies;
}

void Repository::addMovie(const Movie& movie)
{
	this->movies->push_back(movie);
}

void Repository::removeMovie(const std::string& title, const std::string& genre) // stl algo
{
    auto newEnd = std::remove_if(this->movies->begin(), this->movies->end(),
                                 [&title, &genre](const Movie& movie) {
                                     return movie.getTitle() == title && movie.getGenre() == genre;
                                 });
    this->movies->erase(newEnd, this->movies->end());
}

void Repository::updateMovie(const std::string& title, const std::string& genre, Movie& updatedMovie) // stl algo
{
    auto it = std::find_if(this->movies->begin(), this->movies->end(),
                           [&title, &genre](const Movie& movie) {
                               return movie.getTitle() == title && movie.getGenre() == genre;
                           });

    if (it != this->movies->end()) {
        *it = updatedMovie;
    } else {
        throw std::runtime_error("Movie not found");
    }
}

Movie Repository::getMovie(int index)
{
	return this->movies->at(index);
}

unsigned int Repository::getLength()
{
	return this->movies->size();
}

void Repository::incrementLikes(const Movie& movie)
{
    for (Movie& currentMovie : *this->movies) {
        if (currentMovie == movie) {
            currentMovie.setNumberOfLikes(currentMovie.getNumberOfLikes() + 1);
            return;
        }
    }
}

bool Repository::doesMovieExist(const Movie& movie) // stl algo
{
    return std::find_if(this->movies->begin(), this->movies->end(), [&movie](Movie currentMovie) {
        return currentMovie == movie;
    }) != this->movies->end();
}

std::string Repository::displayMovies() {
    std::string result;
    result = "";
    for (Movie& movie : *this->movies) {
        result += movie.toString() + "\n";
    }
    if (result.empty())
        result = "Movie repository is empty!\n";
    return result;
}

std::vector<Movie>& Repository::getMovies() {
    return *this->movies;
}

void Repository::readFromFile() {
    std::fstream file(this->filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Movie m;
    while (file >> m)
        this->movies->push_back(m);

    file.close();
}

std::vector<Movie> Repository::filterMoviesByGenre(const std::string &genre) {
    std::vector<Movie> filteredMovies;
    for (const Movie& movie : *this->movies) {
        if (movie.getGenre() == genre) {
            filteredMovies.push_back(movie);
        }
    }
    return filteredMovies;
}
