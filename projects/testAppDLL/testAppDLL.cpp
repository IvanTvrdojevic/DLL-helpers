#include <iostream>

#include "testLib.h"

int main()
{
    std::cout << "-------------------------- testAppDLL --------------------------" << std::endl;
    int i1 = 1;
    int i2 = 2;
    bool b1 = true;
    char c1 = 'A';
    std::string s1 = "string";

    std::cout << "-------------------------- Mangled names --------------------------" << std::endl;
    std::cout << __GET_MANGLED_NAME(::, testFunc1) << std::endl;
    std::cout << __GET_MANGLED_NAME(::, testFunc2, i1) << std::endl;
    std::cout << __GET_MANGLED_NAME(::, testFunc3, i1) << std::endl;
    std::cout << __GET_MANGLED_NAME(::, testFunc4, i1, b1) << std::endl;
    std::cout << __GET_MANGLED_NAME(::, testFunc5, c1, i1, b1) << std::endl;
    std::cout << __GET_MANGLED_NAME(testNamespace::, testFunc1) << std::endl;
    std::cout << __GET_MANGLED_NAME(testNamespace::, testFunc2, s1) << std::endl;
    std::cout << __GET_MANGLED_NAME(testNamespace::, testFunc3, i1) << std::endl;
    std::cout << __GET_MANGLED_NAME(testNamespace::, testFunc4, i1, b1) << std::endl;
    std::cout << __GET_MANGLED_NAME(testNamespace::, testFunc5, c1, s1, b1) << std::endl;

    std::cout << "-------------------------- testDynamicLink --------------------------" << std::endl;
    std::cout << "-------------------------- C functions --------------------------" << std::endl;
    testFunc1();
    testFunc2(i1);
    std::cout << "testDynamicLink testFunc3: " << testFunc3(i1) << std::endl;
    std::cout << "testDynamicLink testFunc4: " << testFunc4(100, true) << std::endl;
    std::cout << "testDynamicLink testFunc5: " << testFunc5(c1, i1, b1) << std::endl;
    std::cout << "testDynamicLink testFunc5 i1: " << i1 << ", b1: " << b1 << std::endl;

    std::cout << "-------------------------- CPP functions --------------------------" << std::endl;
    testNamespace::testFunc1();
    testNamespace::testFunc2(s1);
    std::cout << "testDynamicLink testNamespace::testFunc3: " << testNamespace::testFunc3(i1) << std::endl;
    std::cout << "testDynamicLink testNamespace::testFunc4: " << testNamespace::testFunc4(i1, false) << std::endl;
    std::vector<int> v = testNamespace::testFunc5('A', s1, b1);
    for(unsigned int i = 0; i < v.size(); i++) std::cout << v[i]; std::cout << std::endl;


    // Artificial pause to simulate delayed/dinamic load
    system("pause");


    std::cout << "-------------------------- testDynamicLoad --------------------------" << std::endl;
    std::cout << "-------------------------- C functions --------------------------" << std::endl;
    auto lib = LoadLibrary(L"testLibDLL");

    i1 = 1;
    i2 = 2;
    b1 = true;
    c1 = 'A';
    s1 = "string";

    __CALL_DLL_FUNCTION(lib, ::, testFunc1);
    __CALL_DLL_FUNCTION(lib, ::, testFunc2, i1);
    std::cout << "testDynamicLoad testFunc3: " << __CALL_DLL_FUNCTION(lib, ::, testFunc3, i1) << std::endl;
    std::cout << "testDynamicLoad testFunc4: " << __CALL_DLL_FUNCTION(lib, ::, testFunc4, 100, true) << std::endl;
    std::cout << "testDynamicLoad testFunc5: " << __CALL_DLL_FUNCTION(lib, ::, testFunc5, c1, i1, b1) << std::endl;
    std::cout << "testDynamicLoad testFunc5 i1: " << i1 << ", b1: " << b1 << std::endl;

    std::cout << "-------------------------- CPP functions --------------------------" << std::endl;
    __CALL_DLL_FUNCTION(lib, testNamespace::, testFunc1);
    __CALL_DLL_FUNCTION(lib, testNamespace::, testFunc2, s1);
    std::cout << "testDynamicLoad testNamespace::testFunc3: " << __CALL_DLL_FUNCTION(lib, testNamespace::, testFunc3, i1) << std::endl;
    std::cout << "testDynamicLoad testNamespace::testFunc4: " << __CALL_DLL_FUNCTION(lib, testNamespace::, testFunc4, i1, false) << std::endl;
    v = __CALL_DLL_FUNCTION(lib, testNamespace::, testFunc5, c1, s1, b1);
    for(unsigned int i = 0; i < v.size(); i++) std::cout << v[i]; std::cout << std::endl;


    return 0;
}

