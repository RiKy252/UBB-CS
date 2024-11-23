#pragma once
#include "Action.h"

class ActionRemove : public Action {
private:
    Movie removedMovie;
    Repository& repo;
public:
    ActionRemove(Movie removedMovie, Repository& repo) : removedMovie { removedMovie }, repo { repo } {}
    void executeUndo() override;
    void executeRedo() override;
};
