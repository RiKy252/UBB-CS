#pragma once
#include"car.h"
#include <assert.h>	
#include "DynamicVector.h"
class Repository
{
	private:
		DynamicVector<Car>* cars;
	public:
		Repository();
		~Repository();
		// Adds a car to the repository.
		void addCar(Car car);
		void testAddCar();
		void removeCar(Car car);
		Car getCar(int index);
		bool doesCarExist(Car car);
		int getLength();
		void sortByName();
		void sortByColor();
};