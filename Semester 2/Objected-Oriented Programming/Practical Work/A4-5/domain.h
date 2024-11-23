#pragma once
#include <string>
#include <iostream>

class Movie
{
	private:
		std::string title;
		std::string genre;
		int releaseYear;
		int numberOfLikes;
		std::string trailer;

	public:
		// Explicit constructor of the Movie class
		Movie(const std::string& title, const std::string& genre, int releaseYear, int numberOfLikes, const std::string& trailer);
		// Default constructor of the Movie class, initializes all attributes
		Movie();
		// Getter for Movie title
		std::string getTitle();
		// Getter for Movie genre
		std::string getGenre();
		// Getter for Movie release year
		int getReleaseYear();
		// Getter for Movie likes counter
		int getNumberOfLikes();
		// Setter for Movie title
		void setTitle(std::string newTitle);
		// Setter for Movie genre
		void setGenre(std::string newGenre);
		// Setter for Movie release year
		void setReleaseYear(int newReleaseYear);
		// Setter for Movie likes counter
		void setNumberOfLikes(int newNumberOfLikes);
		// Setter for Movie trailer
		void setTrailer(std::string newTrailer);
		// Getter for Movie trailer
		std::string getTrailer();
		// Returns true if current movie and comparedMovie are equal (by title and genre)
		bool equalMovies(Movie comparedMovie);
		// Function that returns the string format of the Movie
		std::string toString();
		// Returns true if current movie and comparedMovie are equal (by title and genre)
		bool operator==(const Movie& otherMovie);
};
