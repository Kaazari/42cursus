#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << "=== TEST 1: Create valid Form ===" << std::endl;
	try {
		Form contract("Contract", 50, 25);
		std::cout << contract << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: Form grade too high ===" << std::endl;
	try {
		Form invalid("Invalid", 0, 50);  // Grade 0 = too high
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Form grade too low ===" << std::endl;
	try {
		Form invalid("Invalid", 50, 151);  // Grade 151 = too low
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Bureaucrat signs Form (success) ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 30);
		Form contract("Contract", 50, 25);

		std::cout << alice << std::endl;
		std::cout << contract << std::endl;

		alice.signForm(contract);

		std::cout << contract << std::endl;  // Should show signed: yes
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Bureaucrat signs Form (grade too low) ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 100);
		Form topSecret("TopSecret", 10, 5);

		std::cout << bob << std::endl;
		std::cout << topSecret << std::endl;

		bob.signForm(topSecret);  // Should fail

		std::cout << topSecret << std::endl;  // Should show signed: no
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6: Sign already signed Form ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		Form memo("Memo", 100, 50);

		boss.signForm(memo);  // First signature - OK
		std::cout << memo << std::endl;

		boss.signForm(memo);  // Try to sign again - should work but inform
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
