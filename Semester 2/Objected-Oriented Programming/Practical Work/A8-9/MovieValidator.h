#pragma once
#include "domain.h"
#include "MovieException.h"

class MovieValidator {
public:
    static void validateMovie(Movie movie) {
        if (movie.getTitle().empty())
            throw MovieException("Title cannot be empty!");
        if (movie.getGenre().empty())
            throw MovieException("Genre cannot be empty!");
        if (movie.getReleaseYear() < 0)
            throw MovieException("Year cannot be negative!");
        if (movie.getNumberOfLikes() < 0)
            throw MovieException("Number of likes cannot be negative!");
        if (movie.getTrailer().empty())
            throw MovieException("Trailer cannot be empty!");
    }
};
