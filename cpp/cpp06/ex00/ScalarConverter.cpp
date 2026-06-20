#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::Convert(const std::string& input) {
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') {
		char c = input[1];
		std::cout << "char: '" << c << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
		return;
	}
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
	if (!(iss >> n) || !iss.eof()) {
		std::cout << "char: impossible" << std::endl;
		return;
	}
	unsigned char c = static_cast<unsigned char>(n);
	if (c >= 32 && c <= 127) {
		std::cout << "char: " << "'" << c << "'" << std::endl;
	}
	else if (n < 0 || n > 127)
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
		if (!(iss >> i) || !iss.eof()) {
		std::cout << "int: impossible" << std::endl;
		return;
	}
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
	if (!(iss >> f) || !iss.eof()) {
		std::cout << "float: impossible" << std::endl;
		return;
	}
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
		if (!(iss >> i) || !iss.eof()) {
			std::cout << "double: impossible" << std::endl;
			return;
		}
		if (iss >> i)
			std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
		else
			std::cout << "impossible" << std::endl;
	}
}
