#pragma once
#include "Action.h"

class ActionAdd : public Action {
private:
    Movie addedMovie;
    Repository& repo;
public:
    ActionAdd(Movie addedMovie, Repository& repo) : addedMovie{ addedMovie }, repo { repo } {}
    void executeUndo() override;
    void executeRedo() override;
};
