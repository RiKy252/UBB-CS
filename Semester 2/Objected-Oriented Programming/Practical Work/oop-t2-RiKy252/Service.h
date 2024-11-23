#pragma once
#include "Car.h"
#include "TurboEngine.h"
#include "ElectricEngine.h"
#include <vector>
#include <fstream>

class Service {
private:
    vector<Car*> cars;
public:
    Service();
    void addCar(string bodyStyle, string engineType, int autonomy);
    vector<Car*> getAllCars();
    vector<Car*> getCarsWithMaxPrice(double maxPrice);
    void writeToFile(string filename, vector<Car*> cars);
};
