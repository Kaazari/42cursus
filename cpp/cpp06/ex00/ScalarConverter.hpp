#ifndef SCALAR_CONVERTER
# define SCALAR_CONVERTER

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <sstream>

class ScalarConverter {
private:
	ScalarConverter();

	// Print
	static void PrintChar(const std::string& input);
	static void PrintInt(const std::string& input);
	static void PrintFloat(const std::string& input);
	static void PrintDouble(const std::string& input);

	// Canonical
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

public:
	static void Convert(const std::string& input);
};










#endif
