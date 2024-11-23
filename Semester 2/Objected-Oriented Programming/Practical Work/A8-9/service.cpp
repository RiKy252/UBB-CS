#include "service.h"

Service::Service(Repository* repo)
{
	this->repo = repo;
}

Service::~Service()
{
	delete this->repo;
}

void Service::addMovie(const Movie& movie)
{
	RepoValidator(this->repo).validateMovieExist(movie);
	this->repo->addMovie(movie);
    this->undoStack.push_back(std::make_unique<ActionAdd>(movie, *repo));
}

void Service::removeMovie(const std::string& title, const std::string& genre)
{
    Movie movie{ title, genre, 0, 0, "" };
    for (int i = 0; i < this->getRepoLength(); i++) {
        if (this->repo->getMovie(i) == movie) {
            movie = this->repo->getMovie(i);
            break;
        }
    }
	RepoValidator(this->repo).validateMovieNotExist(movie);
	this->repo->removeMovie(title, genre);
    this->undoStack.push_back(std::make_unique<ActionRemove>(movie, *repo));
}

void Service::updateMovie(const std::string& title, const std::string& genre, Movie& updatedMovie)
{
	Movie oldMovie{ title, genre, 0, 0, "" };
    for (int i = 0; i < this->getRepoLength(); i++) {
        if (this->repo->getMovie(i) == oldMovie) {
            oldMovie = this->repo->getMovie(i);
            break;
        }
    }
    RepoValidator(this->repo).validateMovieNotExist(oldMovie);
	this->repo->updateMovie(title, genre, updatedMovie);
    this->undoStack.push_back(std::make_unique<ActionUpdate>(oldMovie, updatedMovie, *repo));
}

std::string Service::displayMovies()
{
	return this->repo->displayMovies();
}

unsigned int Service::getRepoLength()
{
	return this->repo->getLength();
}

Movie Service::getMovie(int position)
{
	return this->repo->getMovie(position);
}

void Service::incrementLikes(const Movie& movie)
{
	this->repo->incrementLikes(movie);
}

bool Service::doesMovieExist(const Movie &movie) {
    return this->repo->doesMovieExist(movie);
}

std::vector<Movie>& Service::getMovies() {
    return this->repo->getMovies();
}

void Service::writeToFile() {
    this->repo->writeToFile();
}

std::vector<Movie> Service::filterMoviesByGenre(const std::string &genre) {
    return this->repo->filterMoviesByGenre(genre);
}

void Service::openFile() {
    this->repo->openFile();
}

void Service::undo() {
    if (this->undoStack.empty())
        throw RepoException("Undo list empty!");;
    auto action = std::move(this->undoStack.back());
    action->executeUndo();
    this->undoStack.pop_back();
    this->redoStack.push_back(std::move(action));
}

void Service::redo() {
    if (this->redoStack.empty())
        throw RepoException("Redo list empty!");;
    auto action = std::move(this->redoStack.back());
    action->executeRedo();
    this->redoStack.pop_back();
    this->undoStack.push_back(std::move(action));
}
