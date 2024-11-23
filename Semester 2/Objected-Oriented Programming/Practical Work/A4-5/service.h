#pragma once
#include "repo.h"
class Service
{	
	private:
		Repository* repo;
	public:
		// Service constructor
		Service();
		// Service destructor
		~Service();
		// Function that validates the movie and adds it if it does not exist, returns true on success, false otherwise
		bool addMovie(const Movie& movie);
		// Function that validates the movie and removes it if it exist, returns true on success, false otherwise
		bool removeMovie(const std::string& title, const std::string& genre);
		// Function that validates the movie and updates it if the movie exists, and the updatedMovie does not, returns true on success, false otherwise
		bool updateMovie(const std::string& title, const std::string& genre, Movie& updatedMovie);
		// Function that returns a string representing all movies in the service repository
		std::string displayMovies();
		// Returns true if a Movie exists in the current repository, false otherwise
		bool doesMovieExist(const Movie& movie);
		// Getter for the repository length
		int getRepoLength();
		// Getter for a movie on a specific position
		Movie getMovie(int position);
		// This function increments the number of likes of a given movie
		void incrementLikes(Movie movie);
};