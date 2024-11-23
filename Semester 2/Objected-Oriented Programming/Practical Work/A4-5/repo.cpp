#include "repo.h"

Repository::Repository()
{
	this->movies = new DynamicVector<Movie>(10);
}

Repository::~Repository()
{
	delete this->movies;
}

void Repository::addMovie(const Movie& movie)
{
	this->movies->add(movie);
}

void Repository::removeMovie(const std::string& title, const std::string& genre)
{
	Movie temp{ title, genre, 0, 0, "" };
	for (int i = 0; i < this->movies->getLength(); i++)
		if (this->movies->getElement(i).equalMovies(temp)) {
			this->movies->remove(this->movies->getElement(i));
			break;}
}

void Repository::updateMovie(const std::string& title, const std::string& genre, Movie& newMovie)
{
	Movie temp{ title, genre, 0, 0, "" };
	this->movies->remove(temp);
	this->movies->add(newMovie);
}

Movie Repository::getMovie(int index)
{
	return this->movies->getElement(index);
}

int Repository::getLength()
{
	return this->movies->getLength();
}

void Repository::incremLikes(Movie movie)
{
	for (int i = 0; i < this->getLength(); i++)
		if (this->movies->getElement(i) == movie)
			this->movies->getElement(i).setNumberOfLikes(this->movies->getElement(i).getNumberOfLikes() + 1);
}
