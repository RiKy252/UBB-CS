#pragma once
#include "MenuException.h"

class MenuValidator {
public:
    static void validateUserStartMenuOption(int option) {
        if (option < 0 || option > 2)
            throw MenuException("Invalid option!");
    }
    static void validateAdminMenuOption(int option) {
        if (option < 0 || option > 4)
            throw MenuException("Invalid option!");
    }
    static void validateUserMenuOption(int option) {
        if (option < 0 || option > 4)
            throw MenuException("Invalid option!");
    }
    static void validateLikedMenuOption(int option) {
        if (option < 1 || option > 2)
            throw MenuException("Invalid option!");
    }
    static void validateFileTypeOption(const std::string& option) {
        if (option != "CSV" && option != "HTML")
            throw MenuException("Invalid file type!");
    }
};