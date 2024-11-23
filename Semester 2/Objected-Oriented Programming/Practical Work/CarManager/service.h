#pragma once
#include "repository.h"

class Service
{
	private:
		Repository* repo;
	public:
		Service();
		~Service();
		bool addCar(Car car);
		bool removeCar(Car car);
		void sortByName();
		void sortByColor();
		string allCars();
		// Returns a string containing all vintage cars, separatede by newlines
		string vintageCars();
		string testVintageCars();
};