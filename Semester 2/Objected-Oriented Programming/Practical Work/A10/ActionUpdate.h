#pragma once
#include "Action.h"

class ActionUpdate : public Action {
private:
    Movie oldMovie;
    Movie newMovie;
    Repository& repo;
public:
    ActionUpdate(Movie oldMovie, Movie newMovie, Repository& repo) : oldMovie { oldMovie }, newMovie { newMovie }, repo { repo } {}
    void executeUndo() override;
    void executeRedo() override;
};
