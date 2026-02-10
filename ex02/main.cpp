#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Functions.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing generate() and identify() ===" << std::endl;
	std::cout << std::endl;

	// Test 1: Generate random objects and identify them
	std::cout << "--- Test 1: Random generation ---" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base* obj = generate();
		std::cout << "Identify by pointer: ";
		identify(obj);
		std::cout << "Identify by reference: ";
		identify(*obj);
		delete obj;
		std::cout << std::endl;
	}

	std::cout << "--- Test 2: Specific types ---" << std::endl;
	
	// Test with A
	std::cout << "Creating A:" << std::endl;
	Base* a = new A();
	std::cout << "Identify by pointer: ";
	identify(a);
	std::cout << "Identify by reference: ";
	identify(*a);
	delete a;
	std::cout << std::endl;

	// Test with B
	std::cout << "Creating B:" << std::endl;
	Base* b = new B();
	std::cout << "Identify by pointer: ";
	identify(b);
	std::cout << "Identify by reference: ";
	identify(*b);
	delete b;
	std::cout << std::endl;

	// Test with C
	std::cout << "Creating C:" << std::endl;
	Base* c = new C();
	std::cout << "Identify by pointer: ";
	identify(c);
	std::cout << "Identify by reference: ";
	identify(*c);
	delete c;
	std::cout << std::endl;

	std::cout << "=== All tests completed ===" << std::endl;

	return 0;
}
