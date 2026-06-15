#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other) {
	std::cout << "Copy constructor called" << std::endl;
	_value = other._value;
}

Fixed& Fixed::operator=(const Fixed& other){
	// avoid useless a = a;
	// not very useful for Fixed (no allocations)
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		_value = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called." << std::endl;
	return _value;
}

void Fixed::setRawBits(int const raw) {
	_value = raw;
}
