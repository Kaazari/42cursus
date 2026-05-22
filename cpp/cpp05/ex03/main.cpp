#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
	std::cout << "\n=== TEST 1: Intern creates Robotomy ===" << std::endl;
	try {
		Intern someRandomIntern;
		AForm* rrf;

		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf) {
			Bureaucrat boss("Boss", 1);
			boss.signForm(*rrf);
			boss.executeForm(*rrf);
			delete rrf;
		}
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: Intern creates Shrubbery ===" << std::endl;
	try {
		Intern someRandomIntern;
		AForm* form;

		form = someRandomIntern.makeForm("shrubbery creation", "garden");
		if (form) {
			Bureaucrat bob("Bob", 137);
			bob.signForm(*form);
			bob.executeForm(*form);
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Intern creates Presidential ===" << std::endl;
	try {
		Intern someRandomIntern;
		AForm* form;

		form = someRandomIntern.makeForm("presidential pardon", "Marvin");
		if (form) {
			Bureaucrat president("President", 1);
			president.signForm(*form);
			president.executeForm(*form);
			delete form;
		}
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Intern creates unknown form ===" << std::endl;
	try {
		Intern someRandomIntern;
		AForm* form;

		form = someRandomIntern.makeForm("coffee request", "Boss");
		if (form)
			delete form;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
