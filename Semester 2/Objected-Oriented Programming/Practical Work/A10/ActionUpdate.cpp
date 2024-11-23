//
// Created by Riki on 5/25/2024.
//

#include "ActionUpdate.h"

void ActionUpdate::executeUndo() {
    this->repo.updateMovie(this->newMovie.getTitle(), this->newMovie.getGenre(), this->oldMovie);
}

void ActionUpdate::executeRedo() {
    this->repo.updateMovie(this->oldMovie.getTitle(), this->oldMovie.getGenre(), this->newMovie);
}
