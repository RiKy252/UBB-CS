#include "domain.h"

Movie::Movie()
{
	this->title = "";
	this->genre = "";
	this->releaseYear = 0;
	this->numberOfLikes = 0;
	this->trailer = "";
}

Movie::Movie(const std::string& title, const std::string& genre, int releaseYear, int numberOfLikes, const std::string& trailer)
{
	this->title = title;
	this->genre = genre;
	this->releaseYear = releaseYear;
	this->numberOfLikes = numberOfLikes;
	this->trailer = trailer;
}

std::string Movie::getTitle() const {
	return this->title;
}

std::string Movie::getGenre() const {
	return this->genre;
}

int Movie::getReleaseYear() const
{
	return this->releaseYear;
}

int Movie::getNumberOfLikes() const
{
	return this->numberOfLikes;
}

std::string Movie::getTrailer()
{
	return this->trailer;
}

void Movie::setTitle(std::string newTitle)
{
	this->title = newTitle;
}
void Movie::setGenre(std::string newGenre)
{
	this->genre = newGenre;
}
void Movie::setReleaseYear(int newReleaseYear)
{
	this->releaseYear = newReleaseYear;
}
void Movie::setNumberOfLikes(int newNumberOfLikes)
{
	this->numberOfLikes = newNumberOfLikes;
}
void Movie::setTrailer(std::string newTrailer)
{
	this->trailer = newTrailer;
}

bool Movie::equalMovies(const Movie& comparedMovie)
{
	return this->title == comparedMovie.title && this->genre == comparedMovie.genre;
}

bool Movie::operator==(const Movie& otherMovie)
{
	return this->title == otherMovie.title && this->genre == otherMovie.genre;
}

std::string Movie::toString()
{
	return "Title: " + this->title + ", genre: " + this->genre + ", released in: " + std::to_string(this->releaseYear) + ", likes: " + std::to_string(this->numberOfLikes) + ", trailer URL: " + this->trailer;
}

std::ostream &operator<<(std::ostream &output, const Movie &movie) {
    output << movie.title << "," << movie.genre << "," << movie.releaseYear << "," << movie.numberOfLikes << "," << movie.trailer;
    return output;
}

std::istream &operator>>(std::istream &input, Movie &movie) {
    std::string line;
    std::getline(input, line);
    if (line.empty())
        return input;
    std::stringstream stream(line);
    std::string title, genre, trailer, year, likes;
    std::getline(stream, title, ',');
    movie.title = title;
    std::getline(stream, genre, ',');
    movie.genre = genre;
    std::getline(stream, year, ',');
    movie.releaseYear = std::stoi(year);
    std::getline(stream, likes, ',');
    movie.numberOfLikes = std::stoi(likes);
    std::getline(stream, trailer, ',');
    movie.trailer = trailer;
    return input;
}
