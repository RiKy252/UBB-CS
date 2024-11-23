#pragma once
#include <vector>
#include <algorithm>
#include "domain.h"
#include "FileException.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <codecvt>

class Repository {
    protected:
		std::vector<Movie>* movies;
        std::string filename;

	public:
		// Repository constructor
		Repository(std::string filename);
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
		unsigned int getLength();
		// This function increments the number of likes of a given movie
		void incrementLikes(const Movie& movie);
        // Returns true if a Movie exists in the current repository, false otherwise
        bool doesMovieExist(const Movie& movie);
        // Function that returns a string representing all movies in the repository
        std::string displayMovies();
        // Getter for the movies vector
        std::vector<Movie>& getMovies();
        // Returns a vector with filtered movies by genre
        std::vector<Movie> filterMoviesByGenre(const std::string& genre);
        // Writes to file allowing polymorphism
        virtual void writeToFile() = 0;
        // Opens file, polymorphism
        virtual void openFile() = 0;
        // Reads from file (admin list)
        void readFromFile();
};