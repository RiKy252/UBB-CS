#include "ui.h"
#include <iostream>

UI::UI()
{
	this->service = new Service();
	this->service->addCar({ "Fiat", "Idea", 2003, "black" });
	this->service->addCar({ "Ford", "Fiesta", 1976, "yellow" });
	this->service->addCar({ "Audi", "A5", 2007, "blue" });
	this->service->addCar({"BMW", "Coupe", 2013, "pink"});
	this->service->addCar({ "Fiat", "Bravo", 2007, "red" });
}

UI::~UI()
{
	delete this->service;
}

void UI::menu()
{
	cout << "1. Add car\n";
	cout << "2. Remove car\n";
	cout << "3. Show all cars\n";
	cout << "4. Show vintage cars\n";
	cout << "0. Exit\n";
}

void UI::start()
{
	int userOption;
	string carName, carModel, carColor;
	int carYear;
	while (1) {
		menu();
		cout << "Enter your option: ";
		cin >> userOption;
		if (userOption == 1) {
			cout << "Enter the car name: ";
			cin >> carName;
			cout << "Enter the car model: ";
			cin >> carModel;
			cout << "Enter the car fabrication year: ";
			cin >> carYear;
			cout << "Enter the car color: ";
			cin >> carColor;
			Car userCar(carName, carModel, carYear, carColor);
			if (this->service->addCar(userCar))
				cout << "Car added!\n";
			else
				cout << "Car already exists!\n";
		}
		else if (userOption == 2) {
			cout << "Enter the car name: ";
			cin >> carName;
			cout << "Enter the car model: ";
			cin >> carModel;
			cout << "Enter the car fabrication year: ";
			cin >> carYear;
			cout << "Enter the car color: ";
			cin >> carColor;
			Car userCar(carName, carModel, carYear, carColor);
			if (this->service->removeCar(userCar))
				cout << "Car removed!\n";
			else
				cout << "Car doesn't exist!\n";
		}
		else if (userOption == 3) {
			this->service->sortByName();
			cout << this->service->allCars();
		}
		else if (userOption == 4) {
			this->service->sortByColor();
			cout << this->service->vintageCars();
		}
		else if (userOption == 0)
			break;
		else
			cout << "Invalid option!\n";
	}
}