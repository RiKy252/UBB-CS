#include "tests.h"

void Tests::testDynamicVector()
{
	DynamicVector<Movie> vector(2);
	assert(vector.getCapacity() == 2);
	assert(vector.getLength() == 0);
	Movie movie1{ "title1", "genre1", 2010, 100, "link1" };
	vector.add(movie1);
	assert(vector.getLength() == 1);
	assert(vector.getCapacity() == 2);
	Movie movie2{ "title2", "genre2", 2011, 101, "link2" };
	vector.add(movie2);
	assert(vector.getLength() == 2);
	Movie movie3{ "title3", "genre3", 2012, 102, "link3" };
	vector.add(movie3);
	assert(vector.getLength() == 3);
	assert(vector.getCapacity() == 4);
	vector.remove(movie2);
	assert(vector.getLength() == 2);
	assert(vector.getCapacity() == 4);
	assert(vector.search(movie1) == 0);
	assert(vector.search(movie2) == -1);
	assert(vector.search(movie3) == 1);
	assert(vector.getElement(0) == movie1);
	assert(vector.getElement(1) == movie3);
}

void Tests::testDomain()
{
	Movie movie{ "title", "genre", 2010, 100, "link" };
	assert(movie.getTitle() == "title");
	assert(movie.getGenre() == "genre");
	assert(movie.getReleaseYear() == 2010);
	assert(movie.getNumberOfLikes() == 100);
	assert(movie.getTrailer() == "link");
	Movie movie2{ "title2", "genre2", 2011, 101, "link2" };
	assert(movie.equalMovies(movie2) == false);
	Movie movie3{ "title", "genre", 2005, 300, "link3" };
	assert(movie.equalMovies(movie3) == true);
	movie.setTitle("newTitle");
	assert(movie.getTitle() == "newTitle");
	movie.setGenre("newGenre");
	assert(movie.getGenre() == "newGenre");
	movie.setReleaseYear(2000);
	assert(movie.getReleaseYear() == 2000);
	movie.setNumberOfLikes(200);
	assert(movie.getNumberOfLikes() == 200);
	movie.setTrailer("newLink");
	assert(movie.getTrailer() == "newLink");
	assert(movie.toString() == "Title: newTitle, genre: newGenre, released in: 2000, likes: 200, trailer URL: newLink");
}

void Tests::testRepository()
{
	Repository repository;
	Movie movie{ "title", "genre", 2010, 100, "link" };
	repository.addMovie(movie);
	assert(repository.getMovie(repository.getLength() - 1) == movie);
	repository.incremLikes(movie);
	assert(repository.getMovie(0).getNumberOfLikes() == 101);
	Movie movie2{ "title2", "genre2", 2011, 101, "link2" };
	repository.addMovie(movie2);
	assert(repository.getMovie(repository.getLength() - 1) == movie2);
	repository.removeMovie(movie.getTitle(), movie.getGenre());
	assert(repository.getLength() == 1);
	assert(repository.getMovie(0) == movie2);
	Movie movie3{ "title3", "genre3", 2005, 300, "link3" };
	repository.updateMovie(movie2.getTitle(), movie2.getGenre(), movie3);
	assert(repository.getMovie(0) == movie3);
}

void Tests::testService()
{
	Service service;
	Movie movie{ "title", "genre", 2010, 100, "link" };
	assert(service.addMovie(movie) == true);
	assert(service.getRepoLength() == 1);
	assert(service.getMovie(0) == movie);
	Movie movie2{ "title2", "genre2", 2011, 101, "link2" };
	assert(service.addMovie(movie2) == true);
	assert(service.displayMovies() == "Title: title, genre: genre, released in: 2010, likes: 100, trailer URL: link\nTitle: title2, genre: genre2, released in: 2011, likes: 101, trailer URL: link2\n");
	assert(service.addMovie(movie) == false);
	assert(service.removeMovie(movie.getTitle(), movie.getGenre()) == true);
	assert(service.removeMovie(movie.getTitle(), movie.getGenre()) == false);
	assert(service.updateMovie(movie2.getTitle(), movie2.getGenre(), movie) == true);
	assert(service.updateMovie(movie2.getTitle(), movie2.getGenre(), movie) == false);
	assert(service.updateMovie(movie.getTitle(), movie.getGenre(), movie) == false);
	service.incrementLikes(movie);
	assert(service.getMovie(0).getNumberOfLikes() == 101);
}

void Tests::runTests()
{
	Tests::testDynamicVector();
	Tests::testDomain();
	Tests::testRepository();
	Tests::testService();
}
