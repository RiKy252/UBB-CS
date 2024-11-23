#include "ui.h"
#include "service.h"
#include "repo.h"
#include "tests.h"
#include <crtdbg.h>

int main()
{
	Tests::runTests();
	UI ui = UI();
	ui.startApp();
	// _CrtDumpMemoryLeaks();
	return 0;
}

// assignment 6 -> for 1. use STL
// assignment 6 -> for 2. overload << and >>  