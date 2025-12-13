#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(int w, int h) {
	setWidth(w);
	setHeight(h);
}

Rectangle::Rectangle() {
	_width = 1;
	_height = 1;
}

Rectangle::~Rectangle() {
	std::cout << "Anihilation." << std::endl;
}

int Rectangle::getArea() const {
	return _width * _height;
}

int Rectangle::getPerimeter() const{
	return 2 * (_width + _height);
}

void Rectangle::setWidth(int w) {
	_width = w;
}

void Rectangle::setHeight(int h) {
	_height = h;
}
