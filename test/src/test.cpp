#include "test.h"

#include <iostream>

int func1(int a, int b)
{
    return a + b;
}

int func2(const char* str)
{
    std::cout << str << " is asdf\n";
    return 123;
}