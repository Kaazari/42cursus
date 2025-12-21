#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed {
private:
	int					_value;
	static const int	_fractionalBits = 8;

public:
	// OCF
	Fixed();
	Fixed(const int value);
	Fixed(const float value);
	Fixed(const Fixed& other);
	Fixed& operator=(const Fixed& other);
	~Fixed();

	// Conversions
	float	toFloat() const;
	int		toInt() const;
	int		getRawBits() const;
	void	setRawBits(int const raw);

	// Opérateurs de comparaison
	bool operator>(const Fixed& other) const;
	bool operator<(const Fixed& other) const;
	bool operator>=(const Fixed& other) const;
	bool operator<=(const Fixed& other) const;
	bool operator==(const Fixed& other) const;
	bool operator!=(const Fixed& other) const;

	// Opérateurs arithmétiques
	Fixed operator+(const Fixed& other) const;
	Fixed operator-(const Fixed& other) const;
	Fixed operator*(const Fixed& other) const;
	Fixed operator/(const Fixed& other) const;

	// Incrémentation/Décrémentation
	Fixed& operator++();		// Pré-incrémentation
	Fixed  operator++(int);		// Post-incrémentation
	Fixed& operator--();		// Pré-décrémentation
	Fixed  operator--(int);		// Post-décrémentation

	// Fonctions statiques min/max
	static Fixed& min(Fixed& a, Fixed& b);
	static const Fixed& min(const Fixed& a, const Fixed& b);
	static Fixed& max(Fixed& a, Fixed& b);
	static const Fixed& max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
