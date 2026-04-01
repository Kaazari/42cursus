#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm {
private:
	const std::string _name;
	bool _is_signed;
	const int _gradeToSign;
	const int _gradeToExecute;

public:
	// Constructor
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);

	// Canonical
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm();  // Virtual destructor!

	// Getters
	const std::string& getName() const { return _name; }
	bool isSigned() const { return _is_signed; }
	int getGradeToSign() const { return _gradeToSign; }
	int getGradeToExecute() const { return _gradeToExecute; }

	// Actions
	void beSigned(const Bureaucrat& bureaucrat);

	// Pure virtual execute (= classe abstraite)
	virtual void execute(const Bureaucrat& executor) const = 0;

	// Exceptions
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

	class FormNotSignedException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Form is not signed!";
		}
	};
};

std::ostream& operator<<(std::ostream& out, const AForm& f);

#endif
