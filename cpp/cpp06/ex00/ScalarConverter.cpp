#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::Convert(const std::string& input) {
	if (input == "nan" || input == "nanf") {
		std::cout << "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan" << std::endl;
	}
	else if (input == "+inf" || input == "+inff" || input == "inf" || input == "inff") {
		std::cout << "char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf" << std::endl;
	}
	else if (input == "-inf" || input == "-inff") {
		std::cout << "char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf" << std::endl;
	}
	else {
		ScalarConverter::PrintChar(input);
		ScalarConverter::PrintInt(input);
		ScalarConverter::PrintFloat(input);
		ScalarConverter::PrintDouble(input);
	}
}

void ScalarConverter::PrintChar(const std::string& input) {
	if (input.length() == 1 && !isdigit(input[0])) {
		char c = input[0];
		if (c >= 32 && c <= 126)
			std::cout << "char: " << "'" << c << "'";
		else
			std::cout << "Non displayable";
		std::cout << std::endl;
		return ;
	}
	int n;
	std::istringstream iss(input);
	iss >> n;
	char c = static_cast<char>(n);
	if (c >= 32 && c <= 127) {
		std::cout << "char: " << "'" << c << "'" << std::endl;
	}
	else if (n < 0 || n > 127)  // ← AJOUTE CE CHECK
		std::cout << "impossible" << std::endl;
	else {
		std::cout << "char: " << "Non displayable" << std::endl;
	}
}

void ScalarConverter::PrintInt(const std::string& input) {
	if (input.length() == 1 && !isdigit(input[0])) {
		std::cout << "int: " << static_cast<int>(input[0]);
		std::cout << std::endl;
	}
	else {
		float i;
		std::istringstream iss(input);
		if (iss >> i)
			std::cout << "int: " << static_cast<int>(i) << std::endl;
		else
			std::cout << "impossible" << std::endl;
	}
}

void ScalarConverter::PrintFloat(const std::string& input) {
	if (input.length() == 1 && !isdigit(input[0])) {
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(input[0]) << 'f';
		std::cout << std::endl;
		return ;
	}
	float f;
	std::istringstream iss(input);
	if (iss >> f) {
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}
	else
	std::cout << "impossible" << std::endl;
}

void ScalarConverter::PrintDouble(const std::string& input) {
	if (input.length() == 1 && !isdigit(input[0])) {
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(input[0]);
		std::cout << std::endl;
	}
	else {
		float i;
		std::istringstream iss(input);
		if (iss >> i)
			std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
		else
			std::cout << "impossible" << std::endl;
	}
}
