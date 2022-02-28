#pragma once

//#define __DBG_TEST

#include <vector>
#include <string>

#include "dllHelpers.h"


//##################################################################################################
// C FUNCTIONS
//##################################################################################################
__LIB_FUNCTION_API(void, testFunc1);
__LIB_FUNCTION_API(void, testFunc2, int, a1);
__LIB_FUNCTION_API(int, testFunc3, int, a1);
__LIB_FUNCTION_API(int, testFunc4, int, a1, bool, a2);
__LIB_FUNCTION_API(int, testFunc5, char, a1, int&, a2, bool&, a3);


//##################################################################################################
// CPP FUNCTIONS
//##################################################################################################
namespace testNamespace
{
	__LIB_FUNCTION_API(void, testFunc1);
	__LIB_FUNCTION_API(void, testFunc2, std::string, a1);
	__LIB_FUNCTION_API(std::string, testFunc3, int, a1);
	__LIB_FUNCTION_API(std::string, testFunc4, int, a1, bool, a2);
	__LIB_FUNCTION_API(std::vector<int>, testFunc5, char, a1, std::string&, a2, bool&, a3);
}


