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

std::string Movie::getTitle()
{
	return this->title;
}

std::string Movie::getGenre()
{
	return this->genre;
}

int Movie::getReleaseYear()
{
	return this->releaseYear;
}

int Movie::getNumberOfLikes()
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

bool Movie::equalMovies(Movie comparedMovie)
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