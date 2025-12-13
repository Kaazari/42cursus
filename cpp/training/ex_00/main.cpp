#include "Counter.hpp"
#include <iostream>

int main() {
	Counter c;

	c.increment();
	c.increment();
	c.increment();

	std::cout << "Value: " << c.getValue() << std::endl;  // Doit afficher 3

	c.decrement();

	std::cout << "Value: " << c.getValue() << std::endl;  // Doit afficher 2

	return 0;
}
