#include "pointers.h"
#include <iostream>

void pointers()
{
    // Some easy exercises to practice using pointers

    // What is the value of A?
    int A = 3;
    int* pA = &A;
    *pA = 2;
    //std::cout << "a: " << A << std::endl;

    // What are the values in b?
    // Help: ++i == i += 1 -> use i
    //       i++ == use i -> i += 1
    int b[] = { 0,1,2 };
    int* bp = b;
    *(bp++) = 3;
    /*
    std::cout << "b: ";
    for (int i = 0; i < 3; ++i) std::cout << b[i] << " ";
    std::cout << std::endl;
    */

    // Const values can not be modified
    const int c = 0;
    //c = 1; // Compilation error
    //int* cp = &c; // Compilation error
    const int* cp = &c;

    // What is the difference, if any?
    int d = 1;

    int* dp1                = &d;
    int const* dp2          = &d;
    int* const dp3          = &d;
    int const* const dp4    = &d;
    const int* dp5          = &d;
    const int* const dp6    = &d;

    // Rewrite the function toFahrenheit to modify the value of the variable
    float temperature = 10.0f;
    std::cout << "Temperature in Celsius: " << temperature << std::endl;
    toFahrenheit(temperature);
    std::cout << "Temperature in Fahrenheit: " << temperature << std::endl;
}

void toFahrenheit(float inCelsius) {
    inCelsius = (inCelsius * 9.0f / 5.0f) + 32.0f;
}