#pragma once
#include "domain.h"
#include "repo.h"


class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};