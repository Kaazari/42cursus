#include "vect2.hpp"

vect2::vect2() : _v1(0), _v2(0) {}

vect2::vect2(const vect2& other) : _v1(other._v1), _v2(other._v2) {}

vect2::vect2(int i, int j) : _v1(i), _v2(j) {}

vect2& vect2::operator=(const vect2& other) {
	if (*this != other) {
		_v1 = other._v1;
		_v2 = other._v2;
	}
	return (*this);
}

vect2::~vect2() {}

const int& vect2::operator[](int index) const {
	if (index == 0)
		return _v1;
	return _v2;
}

int& vect2::operator[](int index) {
	if (index == 0)
		return _v1;
	return _v2;
}

vect2& vect2::operator++() {
	++_v1;
	++_v2;
	return (*this);
}

vect2& vect2::operator--() {
	--_v1;
	--_v2;
	return (*this);
}

vect2 vect2::operator++(int) {
	vect2 cp(*this);
	++_v1;
	++_v2;
	return (cp);
}

vect2 vect2::operator--(int) {
	vect2 cp(*this);
	--_v1;
	--_v2;
	return (cp);
}

vect2 vect2::operator-(){
	vect2 cp(*this);
	cp._v1 = -cp._v1;
	cp._v2 = -cp._v2;
	return (cp);
}

vect2 vect2::operator-(const vect2& other) const{
	vect2 cp(*this);
	cp._v1 -= _v1;
	cp._v2 -= _v2;
	return (cp);
}

vect2 vect2::operator+(const vect2& other) const{
	vect2 cp(*this);
	cp._v1 += other._v1;
	cp._v2 += other._v2;
	return (cp);
}

vect2 vect2::operator*(int scalar) const{
	vect2 cp(*this);
	cp._v1 *= scalar;
	cp._v2 *= scalar;
	return (cp);
}

vect2& vect2::operator+=(const vect2& other) {
	_v1 += other._v1;
	_v2 += other._v2;
	return (*this);
}

vect2& vect2::operator-=(const vect2& other) {
	_v1 -= other._v1;
	_v2 -= other._v2;
	return (*this);
}

vect2& vect2::operator*=(int scalar) {
	_v1 *= scalar;
	_v2 *= scalar;
	return (*this);
}

bool vect2::operator==(const vect2& other) const {return (_v1 == other._v1 || _v2 == other._v2); }

bool vect2::operator!=(const vect2& other) const {return (_v1 != other._v1 || _v2 != other._v2); }

vect2 operator*(int scalar, const vect2& other) {
	vect2 cp(other);
	cp *= scalar;
	return (cp);
}

std::ostream &operator<<(std::ostream &out, const vect2& other) {
	out << "{" << other[0] << ", " << other[1] << "}";
	return out;
}
