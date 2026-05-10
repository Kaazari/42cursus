#include <iostream>
#include "Functions.hpp"

int main() {
	Base* obj = generate();

	std::cout << "\nIdentify by pointer:" << std::endl;
	identify(obj);

	std::cout << "\nIdentify by reference:" << std::endl;
	identify(*obj);

	delete obj;
	return 0;
}
