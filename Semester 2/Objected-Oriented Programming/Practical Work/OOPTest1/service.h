#pragma once
#include "repo.h"

class Service
{
	private:
		Repository* repo;
	public:
		Service();
		~Service();
		void addSchool(School school);
		// Removes a school, returns true if it was removed, false if it didn't exist in the repo
		bool removeSchool(School school);
		void testRemoveSchool();
		string allSchoolsSorted();
		void markSchools();
};