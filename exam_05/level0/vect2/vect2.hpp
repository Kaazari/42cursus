#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>

class vect2 {
private:
	int _v1;
	int _v2;

public:
	vect2();
	vect2(int i, int j);
	vect2(const vect2& other);
	vect2& operator=(const vect2& other);
	~vect2();

	int& operator[](int index);
	const int& operator[](int index) const;
	vect2 operator+(const vect2& other) const;
	vect2 operator-(const vect2& other) const;
	vect2 operator*(int scalar) const;
	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scalar);
	vect2& operator-();
	vect2& operator++();
	vect2& operator--();
	vect2 operator++(int);
	vect2 operator--(int);
	bool operator==(const vect2& other);
	bool operator!=(const vect2& other);
};

std::ostream& operator<<(std::ostream& out, const vect2& other);
vect2 operator*(int scalar, const vect2& other);

#endif
