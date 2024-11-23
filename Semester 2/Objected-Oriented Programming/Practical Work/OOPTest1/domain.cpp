#include "domain.h"

School::School(string name, string address, Date date, bool visited)
{
	this->name = name;
	this->address = address;
	this->date = date;
	this->visited = visited;
}

School::School()
{
	this->name = "";
	this->address = "";
	Date emptyDate;
	emptyDate.day = 0;
	emptyDate.month = 0;
	emptyDate.year = 0;
	this->date = emptyDate;
	this->visited = false;
}

bool School::operator==(School another)
{
	return this->name == another.name && this->address == another.address;
}

string School::toString()
{
	return this->name + " | " + this->address + " | " + to_string(this->date.year) + "." + to_string(this->date.month) + "." + to_string(this->date.day) + " | " + to_string(this->visited);
}

string School::getName()
{
	return this->name;
}

Date School::getDate()
{
	return this->date;
}

void School::setVisited()
{
	this->visited = true;
}
