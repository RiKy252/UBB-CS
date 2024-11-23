#pragma once
#include <string>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

class School
{
	private:
		string name, address;
		Date date;
		bool visited;
	public:
		School(string name, string address, Date date, bool visited);
		School();
		bool operator==(School another);
		string toString();
		string getName();
		Date getDate();
		void setVisited();
};