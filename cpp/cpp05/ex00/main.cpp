#include "Bureaucrat.hpp"

int main() {
	std::cout << "=== Test 1: Valid creation ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Too high ===" << std::endl;
	try {
		Bureaucrat god("God", 0);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Too low ===" << std::endl;
	try {
		Bureaucrat noob("Noob", 151);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Increment edge case ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl; // grade 1
		alice.incrementGrade(); // BOOM
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
