#pragma once
#include "Observer.h"
#include <vector>

using namespace std;

class Subject {
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }
};