#include <iostream>

#include "testLib.h"

int main()
{
    std::cout << "-------------------------- testAppLIB --------------------------" << std::endl;
    int i1 = 1;
    int i2 = 2;
    bool b1 = true;
    char c1 = 'A';
    std::string s1 = "string";

    std::cout << "-------------------------- C functions --------------------------" << std::endl;
    testFunc1();
    testFunc2(i1);
    std::cout << "testStatcLink testFunc3: " << testFunc3(i1) << std::endl;
    std::cout << "testStatcLink testFunc4: " << testFunc4(100, true) << std::endl;
    std::cout << "testStatcLink testFunc5: " << testFunc5(c1, i1, b1) << std::endl;
    std::cout << "testStatcLink testFunc5 i1: " << i1 << ", b1: " << b1 << std::endl;

    std::cout << "-------------------------- CPP functions --------------------------" << std::endl;
    testNamespace::testFunc1();
    testNamespace::testFunc2(s1);
    std::cout << "testStatcLink testNamespace::testFunc3: " << testNamespace::testFunc3(i1) << std::endl;
    std::cout << "testStatcLink testNamespace::testFunc4: " << testNamespace::testFunc4(i1, false) << std::endl;
    std::vector<int> v = testNamespace::testFunc5('A', s1, b1);
    for (unsigned int i = 0; i < v.size(); i++) std::cout << v[i]; std::cout << std::endl;
}

