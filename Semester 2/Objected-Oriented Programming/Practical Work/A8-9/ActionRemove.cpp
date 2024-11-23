//
// Created by Riki on 5/25/2024.
//

#include "ActionRemove.h"

void ActionRemove::executeUndo() {
    this->repo.addMovie(this->removedMovie);
}

void ActionRemove::executeRedo() {
    this->repo.removeMovie(this->removedMovie.getTitle(), this->removedMovie.getGenre());
}
