#pragma once
#include <string>
using namespace std;
class Car
{
	private:
		string name, model, color;
		int year;
	public:
		Car(string name, string model, int year, string color);
		Car();
		bool operator==(Car another);
		string toString();
		string getName();
		int getYear();
		string getColor();
		void setName(string name);
		void setModel(string model);
		string getModel();
};