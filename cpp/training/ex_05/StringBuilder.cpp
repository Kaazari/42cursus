#include "StringBuilder.hpp"
#include <iostream>

StringBuilder::StringBuilder() {
	std::cout << "Initiated!" << std::endl;
}

StringBuilder::~StringBuilder() {
	std::cout << "Anihilation." << std::endl;
}

StringBuilder& StringBuilder::append(std::string text) {
	_str += text;
	return *this;
}

StringBuilder& StringBuilder::appendInt(int num) {
	std::stringstream ss;
	ss << num;
	_str += ss.str();
	return *this;
}

StringBuilder& StringBuilder::clear() {
	_str = "";
	return *this;
}

std::string StringBuilder::toString() const {
	return (_str);
}
