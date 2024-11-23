//
// Created by Riki on 5/25/2024.
//

#include "ActionAdd.h"

void ActionAdd::executeUndo() {
    this->repo.removeMovie(this->addedMovie.getTitle(), this->addedMovie.getGenre());
}

void ActionAdd::executeRedo() {
    this->repo.addMovie(this->addedMovie);
}
