#pragma once
#include "repo.h"
#include "CSVRepo.h"
#include <exception>
#include "RepoValidator.h"
#include <memory>
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"

class Service
{	
	private:
		Repository* repo;
        std::vector<std::unique_ptr<Action>> undoStack;
        std::vector<std::unique_ptr<Action>> redoStack;
	public:
		// Service constructor
		Service(Repository* repo);
		// Service destructor
		~Service();
		// Function that validates the movie and adds it if it does not exist, returns true on success, false otherwise
		void addMovie(const Movie& movie);
		// Function that validates the movie and removes it if it exists, returns true on success, false otherwise
		void removeMovie(const std::string& title, const std::string& genre);
		// Function that validates the movie and updates it if the movie exists, and the updatedMovie does not, returns true on success, false otherwise
		void updateMovie(const std::string& title, const std::string& genre, Movie& updatedMovie);
		// Function that returns a string representing all movies in the service repository
		std::string displayMovies();
		// Getter for the repository length
		unsigned int getRepoLength();
		// Getter for a movie on a specific position
		Movie getMovie(int position);
		// This function increments the number of likes of a given movie
		void incrementLikes(const Movie& movie);
        // Returns true if a Movie exists in the current repository, false otherwise
        bool doesMovieExist(const Movie& movie);
        // Getter for the movies vector
        std::vector<Movie>& getMovies();
        // Returns a filtered movie list by genre
        std::vector<Movie> filterMoviesByGenre(const std::string& genre);
        // Writes to file
        void writeToFile();
        // Opens the file
        void openFile();
        void undo();
        void redo();
};