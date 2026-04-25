#include "ScalarConverter.hpp"

int main(int ac, char **av) {
	if (av[1] && ac == 2) {
		std::string s = av[1];
		ScalarConverter::Convert(s);
	}
	return (0);
}
