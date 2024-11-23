#include "repo.h"

Repository::Repository()
{
	this->schools = new DynamicVector<School>(10);
}

Repository::~Repository()
{
	delete this->schools;
}

void Repository::addSchool(School school)
{
	this->schools->add(school);
}

void Repository::removeSchool(School school)
{
	this->schools->remove(school);
}

void Repository::testRemoveSchool()
{
	Date date1 = { 15, 4, 2023 };
	this->addSchool(School("Avram_Iancu", "46.77,23.60", date1, true));
	Date date2 = { 23, 4, 2023 };
	this->addSchool(School("Alexandru_Vaida_Voievod", "46.77,23.63", date2, false));
	assert(this->schools->getLength() == 2);
	this->removeSchool(School("Avram_Iancu", "46.77,23.60", date1, true));
	assert(this->schools->getLength() == 1);
	this->removeSchool(School("Romulus_Guga", "46.53,24.57", date1, false));
	assert(this->schools->getLength() == 1);
}

void Repository::sortByName()
{
	for (int i = 0; i < this->schools->getLength(); i++) {
		for (int j = i + 1; j < this->schools->getLength(); j++) {
			if (this->schools->getElement(i).getName() > this->schools->getElement(j).getName()) {
				School aux = this->schools->getElement(i);
				this->schools->getElement(i) = this->schools->getElement(j);
				this->schools->getElement(j) = aux;
			}
		}
	}
}

string Repository::allSchools()
{
	string result = "";
	for (int i = 0; i < this->schools->getLength(); i++) {
		result += (this->schools->getElement(i).toString());
		result += "\n";
	}
	if (result == "")
		return "The school repository is empty!\n";
	return result;
}

bool Repository::doesSchoolExist(School school)
{
	for (int i = 0; i < this->schools->getLength(); i++)
		if (this->schools->getElement(i) == school)
			return true;
	return false;
}

int Repository::getRepoLength()
{
	return this->schools->getLength();
}

void Repository::markSchools(Date d)
{
	for (int i = 0; i < this->schools->getLength(); i++) {
		Date date = this->schools->getElement(i).getDate();
		if (date.year < d.year) {
			this->schools->getElement(i).setVisited();
		}
		if (date.year == d.year && date.month < d.month) {
			this->schools->getElement(i).setVisited();
		}
		if (date.year == d.year && date.month == d.month && date.day < d.day)
			this->schools->getElement(i).setVisited();
	}
}
