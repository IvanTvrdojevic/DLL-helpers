//#include "pch.h"


#include <iostream>

#include "testLib.h"


//##################################################################################################
// C FUNCTIONS
//##################################################################################################
void testFunc1()
{
	std::cout << "testFunc1" << std::endl;
}

void testFunc2(int a1)
{
	std::cout << "testFunc2 a1: " << a1 << std::endl;
}

int testFunc3(int a1)
{
	std::cout << "testFunc3 a1: " << a1 << std::endl;
	return a1 + 1;
}

int testFunc4(int a1, bool a2)
{
	if(a2)
		std::cout << "testFunc4 a1: " << a1 << std::endl;
	else
		std::cout << "testFunc4" << std::endl;

	return a1 + (int)a2 * 2;
}

int testFunc5(char a1, int& a2, bool& a3)
{
	std::cout << "testFunc5" << std::endl;

	if (a1 == 'A')
		a2 = 100;
	else
		a2 = 200;

	a3 = true;

	return (int)a1 + a2 + a3;
}


//##################################################################################################
// CPP FUNCTIONS
//##################################################################################################
namespace testNamespace
{
	void testFunc1()
	{
		std::cout << "testNamespace::testFunc1" << std::endl;
	}


	void testFunc2(std::string a1)
	{
		std::cout << "testNamespace::testFunc2 a1: " << a1 << std::endl;
	}

	std::string testFunc3(int a1)
	{
		std::cout << "testNamespace::testFunc3 a1: " << a1 << std::endl;
		return std::to_string(a1);
	}

	std::string testFunc4(int a1, bool a2)
	{
		std::cout << "testNamespace::testFunc4 a1: " << a1 << std::endl;

		if(a2)
			return std::to_string(a1);
		else
			return std::string("NO");
	}

	std::vector<int> testFunc5(char a1, std::string& a2, bool& a3)
	{
		std::cout << "testNamespace::testFunc5 a1: " << a1 << std::endl;

		a2 = "testNamespace::testFunc5";
		a3 = false;

		return std::vector({ 1, 2, 3 });
	}
}