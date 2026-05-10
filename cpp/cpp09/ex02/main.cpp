#include "PmergeMe.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error: No arguments provided" << std::endl;
		return 1;
	}

	try {
		PmergeMe sorter(argc, argv);
		sorter.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
