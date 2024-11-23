#include "service.h"

Service::Service()
{
	this->repo = new Repository();
}

Service::~Service()
{
	delete this->repo;
}

bool Service::addMovie(const Movie& movie)
{
	if (doesMovieExist(movie))
		return false;
	this->repo->addMovie(movie);
	return true;
}

bool Service::removeMovie(const std::string& title, const std::string& genre)
{
	Movie movie{ title, genre, 0, 0, "" };
	if (!doesMovieExist(movie))
		return false;
	this->repo->removeMovie(title, genre);
	return true;
}

bool Service::updateMovie(const std::string& title, const std::string& genre, Movie& updatedMovie)
{
	Movie movie{ title, genre, 0, 0, "" };
	if (!doesMovieExist(movie))
		return false;
	if (doesMovieExist(updatedMovie))
		return false;
	this->repo->updateMovie(title, genre, updatedMovie);
	return true;
}

std::string Service::displayMovies()
{
	std::string result = "";
	for (int i = 0; i < this->repo->getLength(); i++) {
		result += this->repo->getMovie(i).toString();
		result += "\n";
	}
	return result;
}

bool Service::doesMovieExist(const Movie& movie)
{
	int len = this->repo->getLength();
	for (int i = 0; i < len; i++) {
		if (this->repo->getMovie(i).equalMovies(movie))
			return true;
	}
	return false;
}

int Service::getRepoLength()
{
	return this->repo->getLength();
}

Movie Service::getMovie(int position)
{
	return this->repo->getMovie(position);
}

void Service::incrementLikes(Movie movie)
{
	this->repo->incremLikes(movie);
}