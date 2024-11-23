#pragma once
#include "DynamicVector.h"
#include "domain.h"
#include <assert.h>

class Repository
{
	private:
		DynamicVector<School>* schools;
	public:
		Repository();
		~Repository();
		void addSchool(School school);
		void removeSchool(School school);
		void testRemoveSchool();
		void sortByName();
		string allSchools();
		bool doesSchoolExist(School school);
		int getRepoLength();
		// Marks schools that have the planning date of visit before d
		void markSchools(Date d);
};