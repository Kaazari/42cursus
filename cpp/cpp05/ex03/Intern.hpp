#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
	public:
		Intern();
		Intern(Intern const& other);
		Intern& operator=(Intern const& other);
		~Intern();

		AForm* makeForm(std::string name, std::string target);

	private:
		static AForm* makeShrubbery(std::string target);
		static AForm* makeRobotomy(std::string target);
		static AForm* makePresidential(std::string target);
};

#endif
