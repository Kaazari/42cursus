#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: Shrubbery ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 137);
		ShrubberyCreationForm shrubbery("home");

		bob.signForm(shrubbery);
		bob.executeForm(shrubbery);  // Crée fichier home_shrubbery
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: Robotomy ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 45);
		RobotomyRequestForm robotomy("Bender");

		alice.signForm(robotomy);
		alice.executeForm(robotomy);  // 50% chance
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Presidential ===" << std::endl;
	try {
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");

		president.signForm(pardon);
		president.executeForm(pardon);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Execute without signing ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon2("Ford");

		boss.executeForm(pardon2);  // Pas signé → fail
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Execute with low grade ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon3("Zaphod");

		Bureaucrat boss("Boss", 1);
		boss.signForm(pardon3);  // Boss signe

		intern.executeForm(pardon3);  // Intern execute → fail (grade trop bas)
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
