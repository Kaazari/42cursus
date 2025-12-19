#include "Fixed.hpp"

Fixed::Fixed() {}

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
	*this = other;
}

Fixed& operator=(const Fixed& other) {
	if (this != &other) {
		_value - other.getRawBits();
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

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}

bool Fixed::operator>(const Fixed& other) const {
	return _value > other._value;
}

bool Fixed::operator<(const Fixed& other) const {
	return _value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const {
	return _value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const {
	return _value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const {
	return _value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const {
	return _value != other._value;
}

Fixed Fixed::operator+(const Fixed& other) const {
	Fixed result;
	result.setRawBits(_value + other._value);
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
	Fixed result;
	result.setRawBits(_value - other._value);
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const {
	Fixed result;
	// Multiplication en fixed-point
	result.setRawBits((_value * other._value) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const {
	Fixed result;
	// Division en fixed-point
	result.setRawBits((_value << _fractionalBits) / other._value);
	return result;
}

// Pré-incrémentation : ++a
Fixed& Fixed::operator++() {
	_value++;  // Incrémente de la plus petite valeur (1/256)
	return *this;
}

// Post-incrémentation : a++
Fixed Fixed::operator++(int) {
	Fixed temp(*this);  // Copie l'ancienne valeur
	++(*this);		  // Incrémente
	return temp;		// Retourne l'ancienne valeur
}

// Pré-décrémentation : --a
Fixed& Fixed::operator--() {
	_value--;
	return *this;
}

// Post-décrémentation : a--
Fixed Fixed::operator--(int) {
	Fixed temp(*this);
	--(*this);
	return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
	return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
	return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	return (a > b) ? a : b;
}
