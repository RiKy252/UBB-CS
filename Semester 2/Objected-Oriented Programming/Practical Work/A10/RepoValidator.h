#pragma once
#include "repo.h"
#include "RepoException.h"

class RepoValidator {
private:
    Repository* repo;
public:
    RepoValidator(Repository* repo) {
        this->repo = repo;
    }
    void validateMovieExist(const Movie& movie) {
        if (this->repo->doesMovieExist(movie))
            throw RepoException("Movie already exists!");
    }
    void validateMovieNotExist(const Movie& movie) {
        if (!this->repo->doesMovieExist(movie))
            throw RepoException("Movie does not exist!");
    }
};
