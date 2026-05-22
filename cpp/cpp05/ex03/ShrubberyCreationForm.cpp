#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	// Check si signé
	if (!isSigned())
		throw FormNotSignedException();

	// Check grade executor
	if (executor.getGrade() > getGradeToExecute())
		throw GradeTooLowException();

	// Action: créer fichier avec arbre ASCII
	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Could not create file");

	file << "       ###\n";
	file << "      #o###\n";
	file << "    #####o###\n";
	file << "   #o#\\#|#/###\n";
	file << "    ###\\|/#o#\n";
	file << "     # }|{  #\n";
	file << "       }|{\n";

	file.close();
}
