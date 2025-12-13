#include "Point.hpp"
#include <iostream>

Point::Point(int x, int y) : _x(x), _y(y) {
	std::cout << "Initiated!" << std::endl;
}

Point::~Point() {
	std::cout << "Anihilation..." << std::endl;
}

int Point::getX() const {
	return (_x);
}

int Point::getY() const {
	return (_y);
}

double Point::distanceTo(const Point& other) const {
	int dx = (other._x - _x);
	int dy = (other._y - _y);
	return (sqrt(dx * dx + dy * dy));
}
