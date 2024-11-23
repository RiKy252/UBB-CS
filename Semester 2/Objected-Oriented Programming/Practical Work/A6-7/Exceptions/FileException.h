#pragma once
#include <stdexcept>
#include <string>

class FileException : public std::runtime_error
{
public:
    FileException(const std::string& message) : std::runtime_error(message) {}
};