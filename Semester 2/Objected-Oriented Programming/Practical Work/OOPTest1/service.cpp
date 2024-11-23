#include "service.h"

Service::Service()
{
	this->repo = new Repository();
}

Service::~Service()
{
	delete this->repo;
}

void Service::addSchool(School school)
{
	this->repo->addSchool(school);
}

bool Service::removeSchool(School school)
{
	if (!this->repo->doesSchoolExist(school))
		return false;
	this->repo->removeSchool(school);
	return true;
}

void Service::testRemoveSchool()
{
	this->repo->testRemoveSchool();
}

string Service::allSchoolsSorted()
{
	this->repo->sortByName();
	return this->repo->allSchools();
}
