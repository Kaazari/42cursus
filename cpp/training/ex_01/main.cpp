#include "Rectangle.hpp"
#include <iostream>

int main() {

	Rectangle r1;               // 1x1
	Rectangle r2(5, 3);         // 5x3

	std::cout << r1.getArea() << std::endl;       // 1
	std::cout << r2.getArea() << std::endl;       // 15
	std::cout << r2.getPerimeter() << std::endl;  // 16

	return 0;
}
