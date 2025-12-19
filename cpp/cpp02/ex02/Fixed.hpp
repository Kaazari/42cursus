#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed {
private:
	int					_value;
	static const int	_fractionalBits = 8;

public:
	Fixed();
	Fixed(const int value);
	Fixed(const float value);
	Fixed(const Fixed& other);
	Fixed& operator=(const Fixed& other);
	~Fixed();

	float toFloat() const;
	int toInt() const;

	int getRawBits() const;
	void setRawBits(int const raw);
}

std::ostream& operator<<(std::ostream os, const Fixed& fixed);

#endif
