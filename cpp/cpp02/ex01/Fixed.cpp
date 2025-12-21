#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int value) {
	_value = value << _fractionalBits;
}

Fixed::Fixed(const float value) {
	_value = roundf(value * (1 << _fractionalBits));
}

// divide by 256 (1 << 8 = 2^8 = 256)
float Fixed::toFloat() const {
	return (float)_value / (1 << _fractionalBits);
}

// bitshift raw bits w/ 8
int Fixed::toInt() const {
	return _value >> _fractionalBits;
}

Fixed::Fixed(const Fixed& other) {
	_value = other.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& other) {
	if (this != &other) {
		_value = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {}

int Fixed::getRawBits() const {
	return _value;
}

void Fixed::setRawBits(int const raw) {
	_value = raw;
}

// surcharge <<
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}
