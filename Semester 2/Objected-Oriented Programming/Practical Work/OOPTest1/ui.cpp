#include "ui.h"

UI::UI()
{
	this->service = new Service();
	Date date1 = { 15, 4, 2023 };
	this->service->addSchool(School("Avram_Iancu", "46.77,23.60", date1, true));
	Date date2 = { 8, 4, 2023 };
	this->service->addSchool(School("George_Cosbuc", "46.77,23.58", date2, false));
	Date date3 = { 23, 4, 2023 };
	this->service->addSchool(School("Alexandru_Vaida_Voievod", "46.77,23.63", date3, false));
	Date date4 = { 4, 5, 2023 };
	this->service->addSchool(School("Romulus_Guga", "46.53,24.57", date4, false));
	Date date5 = { 3, 5, 2023 };
	this->service->addSchool(School("Colegiul_Transilvania", "46.54,24.57", date5, false));
}

UI::~UI()
{
	delete this->service;
}

void UI::menu()
{
	cout << "1. Remove school\n";
	cout << "2. Show schools sorted by name\n";
	cout << "3. Mark schools\n";
	cout << "0. Exit\n";
}

void UI::start()
{
	// this->service->testRemoveSchool();
	string schoolName, schoolAddress;
	Date schoolDate;
	int day, month, year;
	bool visitedSchool;
	int userOption;
	while (1) {
		this->menu();
		cout << "Enter your option: ";
		cin >> userOption;
		if (userOption == 1) {
			cout << "Please enter the school name: ";
			cin >> schoolName;
			cout << "Please enter the school address: ";
			cin >> schoolAddress;
			cout << "Please enter the day of the planned date: ";
			cin >> day;
			cout << "Please enter the month of the planned date: ";
			cin >> month;
			cout << "Please enter the year of the planned date: ";
			cin >> year;
			cout << "Enter the boolean value (0 or 1) for visited school: ";
			cin >> visitedSchool;
			schoolDate.day = day;
			schoolDate.month = month;
			schoolDate.year = year;
			School schoolToBeRemoved(schoolName, schoolAddress, schoolDate, visitedSchool);
			if (this->service->removeSchool(schoolToBeRemoved))
				cout << "School removed!\n";
			else
				cout << "School does not exist!\n";
		}
		else if (userOption == 2) {
			cout << this->service->allSchoolsSorted();
		}
		else if (userOption == 3) {
			// mark
		}
		else if (userOption == 0)
			break;
		else
			cout << "Invalid option!\n";
	}
}
