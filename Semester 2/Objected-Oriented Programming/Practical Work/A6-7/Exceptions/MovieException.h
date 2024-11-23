#pragma once
#include <stdexcept>
#include <string>

class MovieException : public std::runtime_error{
public:
    MovieException(const std::string& message) : std::runtime_error(message) {}
};