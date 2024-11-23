//
// Created by Riki on 4/23/2024.
//

#include "Service.h"

Service::Service() {
    Car* car1 = new Car("Sedan", new ElectricEngine(500));
    this->cars.push_back(car1);
    Car* car2 = new Car("Convertible", new TurboEngine());
    this->cars.push_back(car2);
    Car* car3 = new Car("Convertible", new ElectricEngine(900));
    this->cars.push_back(car3);
}

void Service::addCar(string bodyStyle, string engineType, int autonomy) {
    Car* newCar;
    if (engineType == "ElectricEngine")
        newCar = new Car(bodyStyle, new ElectricEngine(autonomy));
    else
        newCar = new Car(bodyStyle, new TurboEngine());
    this->cars.push_back(newCar);
}

vector<Car *> Service::getAllCars() {
    return this->cars;
}

vector<Car*> Service::getCarsWithMaxPrice(double maxPrice) {
    vector<Car*> result;
    for (auto car : this->cars) {
        if (car->computePrice() < maxPrice) {
            result.push_back(car);
        }
    }
    return result;
}

void Service::writeToFile(string filename, vector<Car *> cars) {
    ofstream file(filename);
    for (int i = 0; i < cars.size(); i++) {
        for (int j = i + 1; j < cars.size(); j++) {
            if (cars[i]->computePrice() > cars[j]->computePrice()) {
                Car* aux = cars[i];
                cars[i] = cars[j];
                cars[j] = aux;
            }
        }
    }
    for (auto car : cars) {
        file << car->toString();
        file << "\n";
    }
}
