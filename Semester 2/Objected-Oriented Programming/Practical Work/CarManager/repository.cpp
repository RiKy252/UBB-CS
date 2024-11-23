#include "repository.h"

Repository::Repository()
{
	this->cars = new DynamicVector<Car>(10);
}

Repository::~Repository()
{
	delete this->cars;
}

void Repository::addCar(Car car)
{
	this->cars->add(car);
}

void Repository::removeCar(Car car)
{
	this->cars->remove(car);
}

Car Repository::getCar(int index)
{
	return this->cars->getElement(index);
}

bool Repository::doesCarExist(Car car)
{
	for (int i = 0; i < this->getLength(); i++)
		if (this->cars->getElement(i) == car)
			return true;
	return false;
}

int Repository::getLength()
{
	return this->cars->getLength();
}

void Repository::sortByName()
{
	for (int i = 0; i < this->cars->getLength(); i++)
		for (int j = i + 1; j < this->cars->getLength(); j++) {
			if (this->cars->getElement(i).getName() > this->cars->getElement(j).getName()) {
				Car aux = this->cars->getElement(i);
				this->cars->getElement(i) = this->cars->getElement(j);
				this->cars->getElement(j) = aux;
			}
			if (this->cars->getElement(i).getName() == this->cars->getElement(j).getName() && this->cars->getElement(i).getModel() > this->cars->getElement(j).getModel()) {
				Car aux = this->cars->getElement(i);
				this->cars->getElement(i) = this->cars->getElement(j);
				this->cars->getElement(j) = aux;
			}
		}
}

void Repository::sortByColor()
{
	for (int i = 0; i < this->cars->getLength(); i++)
		for (int j = i + 1; j < this->cars->getLength(); j++)
			if (this->cars->getElement(i).getColor() > this->cars->getElement(j).getColor()) {
				Car aux = this->cars->getElement(i);
				this->cars->getElement(i) = this->cars->getElement(j);
				this->cars->getElement(j) = aux;
			}
}

void testAddCar()
{
	Repository repo;
	Car car1("Audi", "A4", 2010, "black");
	Car car2("BMW", "X5", 2015, "white");
	Car car3("Mercedes", "E200", 2018, "blue");
	repo.addCar(car1);
	repo.addCar(car2);
	repo.addCar(car3);
	assert(repo.getLength() == 3);
	assert(repo.getCar(0) == car1);
	assert(repo.getCar(1) == car2);
	assert(repo.getCar(2) == car3);
}