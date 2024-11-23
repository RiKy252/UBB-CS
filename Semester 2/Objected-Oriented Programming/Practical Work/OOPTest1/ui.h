#pragma once
#include "service.h"
#include <iostream>

class UI
{
	private:
		Service* service;
	public:
		UI();
		~UI();
		void menu();
		void start();
};