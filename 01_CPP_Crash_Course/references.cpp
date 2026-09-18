#include "references.h"
#include <iostream>

void references()
{
	// We've seen that pointers are not always the most user-friendly
	// Instead, we use references in most places,
	// but we'll use pointers and pointer arithmetics as well

	// Why do we use pointers?
	int number = 0;
	increase(number);
	std::cout << "number: " << number << std::endl;
	// As we can see it doesn't work, instead:
	increasePointer(&number);
	std::cout << "number: " << number << std::endl;
	// How would it look with references?
	increaseReference(number);
	std::cout << "number: " << number << std::endl;

	// So, are references just syntactic sugar for pointers?
	// NO

	// For example, we can have a nullptr, but we can't have a null reference
	// Actually, references can't be uninitialized

	int a = 5;
	int* ap;
	ap = nullptr;
	ap = &a;

	//int& ar;		// Compilation error
	int& ar = a;	// Good

	// With references, you cannot change what they reference
	int b = 0;
	ar = b;	// it changes the value of a

	// Does it compile?
	int aNumber = 7;
	const int constNumber = 8;

	// int& ref0;
	// int& ref1 = aNumber;
	// int& ref2 = constNumber;
	// int& ref3 = 9;

	// const int& ref4;
	// const int& ref5 = aNumber;
	// const int& ref6 = constNumber;
	// const int& ref7 = 9;
}

void increase(int n)
{
	// n is beeing copied
	n++;
}

void increasePointer(int* np)
{
	// here we copy np, after dereferencing it
	// we get the number
	(*np)++;
}

void increaseReference(int& n)
{
	n++;
}