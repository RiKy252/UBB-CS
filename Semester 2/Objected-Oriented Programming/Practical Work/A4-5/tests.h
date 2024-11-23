#pragma once
#include "service.h"
#include <assert.h>
class Tests {
	private:
		static void testDynamicVector();
		static void testDomain();
		static void testRepository();
		static void testService();
	public:
		static void runTests();
};