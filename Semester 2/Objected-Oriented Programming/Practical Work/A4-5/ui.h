#pragma once
#include "service.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <codecvt>
using namespace std;

class UI
{
	private:
		Service* service;
		Service* userService;
	public:
		UI();
		~UI();
		bool validIntegerInput();
		void adminMenu();
		void userMenu();
		void startMessage();
		void startApp();
};