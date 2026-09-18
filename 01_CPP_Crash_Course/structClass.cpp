#include "structClass.h"
#include <iostream>
#include <vector>
// #include <cmath>

class ComplexNumber
{
public: // Below this it's public
	float real = 0;
	float imaginary = 0;

	ComplexNumber() {};
	ComplexNumber(float _real, float _imaginary)
	{
		real = _real;
		imaginary = _imaginary;
	}

	void add(const ComplexNumber &rhs)
	{
		real += rhs.real;
		imaginary += rhs.imaginary;
	}

	float magnitude() const
	{
		// return std::sqrt(real * real + imaginary * imaginary);
		return 0;
	}
};

class X
{
	std::string name = "default_name";

public:
	// It runs every time we create a new instance of the class
	X()
	{
		std::cout << "Constructor " << name << std::endl;
	}

	X(int value, const std::string &_name)
	{
		name = _name;
		std::cout << "Constructor with value: " << value << " " << name << std::endl;
	}

	// It runs when the instance's lifetime ends
	~X()
	{
		std::cout << "Destructor " << name << std::endl;
	}
};

void structClass()
{
	// Compared to C, a struct can have methods, static variables,
	// constructor, destructor etc.

	// In CPP, a new keyword was introduced: class.
	// In a struct, variables are public by default, whereas in a class, they are private; there are no other significant differences
	ComplexNumber n;
	n.imaginary = 1.0f;
	n.real = 0.0f;

	ComplexNumber n2(3.0f, 4.0f);
	n2.add(n);
	std::cout << "complex number magnitude: " << n2.magnitude() << std::endl;

	// The size of a class is fixed -> we can query their size during compilation
	std::cout << "ComplexNumber size: " << sizeof(ComplexNumber) << std::endl;
	// During compilation, we need to know the size of the classes -> we can query where each member is located within the class (byte offset)
	std::cout << "Offset of real: " << offsetof(ComplexNumber, real) << std::endl;
	std::cout << "Offset of imaginary: " << offsetof(ComplexNumber, imaginary) << std::endl;

	// Constructor, destructor example
	{
		X x1;
		X x2(100, "x2");
	}

	// size of char and int
	std::cout << "Char size: " << sizeof(char) << " Int size: " << sizeof(int) << std::endl;

	// Why does the size change if the member variables are in a different order?
	// struct S1 {
	// 	char c1;
	// 	char c2;
	// 	int i;
	// };
	// struct S2 {
	// 	char c1;
	// 	int i;
	// 	char c2;
	// };
	// std::cout << "S1: " << sizeof(S1) << " S2: " << sizeof(S2) << std::endl;
}