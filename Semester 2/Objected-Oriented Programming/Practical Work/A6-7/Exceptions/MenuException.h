#pragma once
#include <stdexcept>
#include <string>

class MenuException : public std::runtime_error {
public:
    MenuException(const std::string& message) : std::runtime_error(message) {}
};