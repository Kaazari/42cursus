#include "vect2.hpp"

vect2::vect2(): v1(0), v2(0) {}

vect2::vect2(int i, int j): v1(i), v2(j) {}

vect2& vect2::operator=(const vect2& other) {
	if (*this != other) {
		v1 = other.v1;
		v2 = other.v2;
	}
}


