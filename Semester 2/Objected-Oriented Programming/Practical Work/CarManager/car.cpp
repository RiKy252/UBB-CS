#include "car.h"

Car::Car(string name, string model, int year, string color)
{
	this->name = name;
	this->model = model;
	this->year = year;
	this->color = color;
}

Car::Car()
{
	this->name = "";
	this->model = "";
	this->year = 0;
	this->color = "";
}

bool Car::operator==(Car another)
{
	return this->model == another.model && this->year == another.year;
}

string Car::toString()
{
	string result = "";
	result = name + " | " + model + " | " + to_string(year) + " | " + color + "\n";
	return result;
}

string Car::getName()
{
	return this->name;
}

int Car::getYear()
{
	return this->year;
}

string Car::getColor()
{
	return this->color;
}

string Car::getModel()
{
	return this->model;
}

void Car::setName(string name)
{
	this->name = name;
}

void Car::setModel(string model)
{
	this->model = model;
}
