#include "containers.h"
#include <vector>
#include <array>
#include <iostream>

void printVector(const std::vector<int>& vec);

void containers()
{
	// We have seen that manually allocating memory is not the most convenient  
	// or maintaining a separate variable for iteration.  
	// This is what container libraries are intended for:
	// to provide various data structures  
	// https://en.cppreference.com/w/cpp/container

	// Throughout the semester, the most commonly used class is std::vector,
	// which should not be confused with vectors in mathematics.
	// It's located in #include <vector>

	std::vector<int> emptyVector; // Initialize empy vector: <int> -> contains int
	std::vector<int> vectorWithValues = { 0,1,2 };			// Initialized with 0,1,2
	std::vector<int> vectorFromVector1 = vectorWithValues;	// Copy constructor (deep copy)
	std::vector<int> vectorFromVector2(vectorWithValues);	// also  copy constructor (deep copy)

	// Push back, the vector is dynamically sized, it stores data on the heap
	emptyVector.push_back(3);
	emptyVector.push_back(2);

	std::cout << "vector with for loop: ";
	for (int i = 0; i < emptyVector.size(); ++i) // .size()  how many element it has
	{
		std::cout << emptyVector[i] << " "; // can be indexed with [] operator
	}
	std::cout << std::endl;

	// If we want a pointer to the elements of the data array
	int* p = vectorWithValues.data();
	// int* p = &vectorWithValues[0]; // It works too
	*p = 10;

	printVector(vectorWithValues);

	// There is a container for arrays on the stack
	std::array<double, 6> doubleArr{ 0,0,0,0,0,0 }; // <data type, size>
	std::cout << "Array size/capacity: " << doubleArr.size() << std::endl;
}

void printVector(const std::vector<int>& vec)
{
	// for each is an alternative
	// What is the difference between them?
	// Which one works here, which one doesn't? Why?
	std::cout << "vector with for each: ";
	for (const int& v : vec)
	//for (int& v : vec)
	//for (int v : vec)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}