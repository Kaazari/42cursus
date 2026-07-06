#ifndef VECT2_HPP
#define VECT2_HPP

// # include <stdio>
// # include <sstream>

class vect2 {
private:
	int v1;
	int v2;

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
	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);
	vect2 operator-() const;
	bool operator==(const vect2& other) const;
	bool operator!=(const vect2& other) const;
};


std::ostream& operator<<(std::ostream&, const vect2& v);
vect2 operator*(int scalar, const vect2&);


#endif
