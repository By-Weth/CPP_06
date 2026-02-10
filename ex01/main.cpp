#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
	Data* original = new Data;
	
	original->value = 42;
	original->name = "Test Data";
	original->price = 19.99;

	std::cout << "=== Original Data ===" << std::endl;
	std::cout << "Address: " << original << std::endl;
	std::cout << "Value: " << original->value << std::endl;
	std::cout << "Name: " << original->name << std::endl;
	std::cout << "Price: " << original->price << std::endl;
	std::cout << std::endl;

	std::cout << "=== Serialization ===" << std::endl;
	uintptr_t raw = Serializer::serialize(original);
	std::cout << "Serialized (uintptr_t): " << raw << std::endl;
	std::cout << std::endl;

	std::cout << "=== Deserialization ===" << std::endl;
	Data* deserialized = Serializer::deserialize(raw);
	std::cout << "Address: " << deserialized << std::endl;
	std::cout << "Value: " << deserialized->value << std::endl;
	std::cout << "Name: " << deserialized->name << std::endl;
	std::cout << "Price: " << deserialized->price << std::endl;
	std::cout << std::endl;

	std::cout << "=== Verification ===" << std::endl;
	if (deserialized == original)
	{
		std::cout << "✓ Success! Pointers are equal." << std::endl;
		std::cout << "Original address:      " << original << std::endl;
		std::cout << "Deserialized address:  " << deserialized << std::endl;
	}
	else
	{
		std::cout << "✗ Error! Pointers are different." << std::endl;
		std::cout << "Original address:      " << original << std::endl;
		std::cout << "Deserialized address:  " << deserialized << std::endl;
	}

	delete original;

	return 0;
}
