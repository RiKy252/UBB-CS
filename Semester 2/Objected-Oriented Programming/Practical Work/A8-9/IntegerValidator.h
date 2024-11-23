#pragma once
#include <iostream>

class IntegerValidator {
public:
    static void validateInteger() {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::invalid_argument("Please insert a valid integer!");
        }
    }
};
