#include <iostream>
#include <string>
#include "iter.hpp"

// Test functions
template <typename T>
void printElement(T const& x) {
	std::cout << x << " ";
}

void incrementInt(int& x) {
	x++;
}

void toUpperChar(char& c) {
	if (c >= 'a' && c <= 'z')
		c = c - 32;
}

void doubleValue(double& x) {
	x *= 2;
}

int main() {
	// Test 1: Int array with const function
	std::cout << "=== Test 1: Int array (print) ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	size_t intLen = sizeof(intArray) / sizeof(intArray[0]);
	iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	// Test 2: Int array with non-const function (modify)
	std::cout << "\n=== Test 2: Int array (increment) ===" << std::endl;
	std::cout << "Before: ";
	iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	iter(intArray, intLen, incrementInt);

	std::cout << "After:  ";
	iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	// Test 3: Char array
	std::cout << "\n=== Test 3: Char array (uppercase) ===" << std::endl;
	char charArray[] = {'h', 'e', 'l', 'l', 'o'};
	size_t charLen = sizeof(charArray) / sizeof(charArray[0]);

	std::cout << "Before: ";
	iter(charArray, charLen, printElement<char>);
	std::cout << std::endl;

	iter(charArray, charLen, toUpperChar);

	std::cout << "After:  ";
	iter(charArray, charLen, printElement<char>);
	std::cout << std::endl;

	// Test 4: Double array
	std::cout << "\n=== Test 4: Double array (double values) ===" << std::endl;
	double doubleArray[] = {1.5, 2.5, 3.5};
	size_t doubleLen = sizeof(doubleArray) / sizeof(doubleArray[0]);

	std::cout << "Before: ";
	iter(doubleArray, doubleLen, printElement<double>);
	std::cout << std::endl;

	iter(doubleArray, doubleLen, doubleValue);

	std::cout << "After:  ";
	iter(doubleArray, doubleLen, printElement<double>);
	std::cout << std::endl;

	// Test 5: String array
	std::cout << "\n=== Test 5: String array ===" << std::endl;
	std::string stringArray[] = {"Hello", "World", "42"};
	size_t stringLen = sizeof(stringArray) / sizeof(stringArray[0]);
	iter(stringArray, stringLen, printElement<std::string>);
	std::cout << std::endl;

	return 0;
}
