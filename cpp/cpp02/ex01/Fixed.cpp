#include "Fixed.hpp"

Fixed::Fixed() {
	std::cout << "Called default constructor." << std::endl;
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Called copy constructor." << std::endl;
	*this = other;
}

// avoid crashes and double free if an assignation is made without.
// Fixed a; a = b; would result to a copy at the same adress if new is being used somewhere in the class.
Fixed& operator=(const Fixed& other){
	std::cout << "Called copy assignment operator." << std::endl;
	if (this != &other) {
		_value - other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Called destructor." << std::endl;
}

int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called." << std::endl;
	return _value;
}

void Fixed::setRawBits(int const raw) {
	_value = raw;
}
