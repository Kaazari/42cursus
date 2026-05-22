#include "Intern.hpp"
#include <iostream>

Intern::Intern() {}
Intern::Intern(Intern const& other) { (void)other; }
Intern& Intern::operator=(Intern const& other) { (void)other; return *this; }
Intern::~Intern() {}

AForm* Intern::makeShrubbery(std::string target) { return new ShrubberyCreationForm(target); }
AForm* Intern::makeRobotomy(std::string target)  { return new RobotomyRequestForm(target); }
AForm* Intern::makePresidential(std::string target) { return new PresidentialPardonForm(target); }

AForm* Intern::makeForm(std::string name, std::string target) {
	std::string names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm* (*creators[3])(std::string) = {
		&Intern::makeShrubbery,
		&Intern::makeRobotomy,
		&Intern::makePresidential
	};

	for (int i = 0; i < 3; i++) {
		if (names[i] == name) {
			std::cout << "Intern creates " << name << std::endl;
			return creators[i](target);
		}
	}
	std::cerr << "Error: form '" << name << "' does not exist" << std::endl;
	return NULL;
}
