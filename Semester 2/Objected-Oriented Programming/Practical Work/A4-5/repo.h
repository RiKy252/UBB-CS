#pragma once
#include "dynamicvector.h"
#include "domain.h"

class Repository {
	private:
		DynamicVector<Movie>* movies;

	public:
		// Repository constructor
		Repository();
		// Repository destructor
		~Repository();
		// Adds a movie to the current repository
		void addMovie(const Movie& movie);
		// Removes a movie from the current repository
		void removeMovie(const std::string& title, const std::string& genre);
		// Updates a movie from the current repository
		void updateMovie(const std::string& title, const std::string& genre, Movie& newMovie);
		// Gets a movie from a given index
		Movie getMovie(int index);
		// Getter for length of repository
		int getLength();
		// This function increments the number of likes of a given movie
		void incremLikes(Movie movie);
};