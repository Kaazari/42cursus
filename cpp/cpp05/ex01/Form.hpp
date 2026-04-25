#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
private:
	const std::string _name;
	bool _is_signed;
	const int _gradeToSign;
	const int _gradeToExecute;

public:
	// Constructor
	Form(const std::string& name, int gradeToSign, int gradeToExecute);

	// Canonical
	Form(const Form& other);
	Form& operator=(const Form& other);
	~Form();

	// Getters
	const std::string& getName() const { return _name; }
	int getGradeToSign() const { return _gradeToSign; }
	int getGradeToExecute() const { return _gradeToExecute; }
	bool isSigned() const { return _is_signed; }

	// Actions
	void beSigned(const Bureaucrat& other);

	// Nested Exception Classes
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Grade is too high!";
		}
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Grade is too low!";
		}
	};
};

std::ostream& operator<<(std::ostream& out, const Form& b);


#endif
