#include "Harl.hpp"
#include <iostream>

int getLevelIndex(std::string level) {
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++) {
		if (level == levels[i])
			return i;
	}
	return -1;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./harlFilter <level>" << std::endl;
		return 1;
	}

	Harl harl;
	int level = getLevelIndex(argv[1]);

	switch (level) {
		case 0:
			harl.complain("DEBUG");
		case 1:
			harl.complain("INFO");
		case 2:
			harl.complain("WARNING");
		case 3:
			harl.complain("ERROR");
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}

	return 0;
}
