#pragma once
#include "service.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <codecvt>
#include "MovieValidator.h"
#include "IntegerValidator.h"
#include "MenuValidator.h"
#include "RepoValidator.h"
#include "AdminCSVRepo.h"
#include "HTMLRepo.h"

using namespace std;

void openURL(const std::string &url);

class UI
{
	private:
		Service* service;
		Service* userService;
	public:
		UI(const std::string& fileType);
		~UI();
		static void adminMenu();
		static void userMenu();
		static void startMessage();
		void startApp();
};