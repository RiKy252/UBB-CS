#pragma once
#include <stdexcept>
#include <string>

class RepoException : public std::runtime_error {
public:
    RepoException(const std::string& message) : std::runtime_error(message) {}
};