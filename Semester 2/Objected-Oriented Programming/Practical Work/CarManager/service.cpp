#include "service.h"

Service::Service()
{
	this->repo = new Repository();
}

Service::~Service()
{
	delete this->repo;
}

bool Service::addCar(Car car)
{
	if (this->repo->doesCarExist(car))
		return false;
	this->repo->addCar(car);
	return true;
}

bool Service::removeCar(Car car)
{
	if (!this->repo->doesCarExist(car))
		return false;
	this->repo->removeCar(car);
	return true;
}

void Service::sortByName()
{
	this->repo->sortByName();
}

void Service::sortByColor()
{
	this->repo->sortByColor();
}

string Service::allCars()
{
	string all = "";
	for (int i = 0; i < this->repo->getLength(); i++) {
		all += this->repo->getCar(i).toString();
		all += "\n";
	}
	if (all == "")
		return "Car repository is empty!";
	return all;
}

string Service::vintageCars()
{
	string vCars = "";
	for (int i = 0; i < this->repo->getLength(); i++) 
		if (this->repo->getCar(i).getYear() < 1979) {
			vCars += this->repo->getCar(i).toString();
			vCars += "\n";
		}
	if (vCars == "")
		return "No vintage cars in the repository!";
	return vCars;
}