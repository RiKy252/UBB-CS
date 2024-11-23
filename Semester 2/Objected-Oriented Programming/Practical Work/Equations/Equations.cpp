//
// Created by Riki on 5/28/2024.
//

#include "Equations.h"

Equations::Equations(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

int Equations::getA() {
    return this->a;
}

int Equations::getB() {
    return this->b;
}

int Equations::getC() {
    return this->c;
}

void Equations::setA(int newA) {
    this->a = newA;
}

void Equations::setB(int newB) {
    this->b = newB;
}

void Equations::setC(int newC) {
    this->c = newC;
}

std::istream &operator>>(std::istream &input, Equations &equation) {
    std::string line;
    std::getline(input, line);
    if (line.empty())
        return input;
    std::stringstream stream(line);
    std::string a, b ,c;
    std::getline(stream, a, ',');
    equation.setA(std::stoi(a));
    std::getline(stream, b, ',');
    equation.setB(std::stoi(b));
    std::getline(stream, c, ',');
    equation.setC(std::stoi(c));
    return input;
}

Equations::Equations() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
}

int Equations::delta() {
    return (b*b - 4*a*c);
}
