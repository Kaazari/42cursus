#ifndef VECT2_hpp
# define VECT2_hpp

# include <iostream>

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

	const int& operator[](int index) const;
	int& operator[](int index);
	vect2& operator++();
	vect2& operator--();
	vect2 operator++(int);
	vect2 operator--(int);
	vect2 operator-();
	vect2 operator-(const vect2& other) const;
	vect2 operator+(const vect2& other) const;
	vect2 operator*(int scalar) const;
	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scalar);
	bool operator==(const vect2& other) const;
	bool operator!=(const vect2& other) const;
};

std::ostream &operator<<(std::ostream &out, const vect2& other);
vect2 operator*(int scalar, const vect2& v);

#endif
