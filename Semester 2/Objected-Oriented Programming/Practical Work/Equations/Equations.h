#pragma once
#include <string>
#include <sstream>

class Equations {
private:
    int a, b, c;
public:
    Equations(int a, int b, int c);
    int getA();
    int getB();
    int getC();
    void setA(int newA);
    void setB(int newB);
    void setC(int newC);
    friend std::istream& operator>>(std::istream& input, Equations& equation);
    int delta();
    Equations();
};
