#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <iostream>
#include <string>

class AForm;  // ✅ Forward declaration AForm (pas Form)

class Bureaucrat {
private:
	const std::string _name;
	int _grade;

public:
	// Constructeur
	Bureaucrat(const std::string& name, int grade);

	// Canonical form
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();

	// Getters
	const std::string& getName() const { return _name; }
	int getGrade() const { return _grade; }

	// Actions
	void incrementGrade();
	void decrementGrade();
	void signForm(AForm& form);  // ✅ AForm (pas Form)
	void executeForm(const AForm& form) const;  // ✅ AForm

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

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b);

#endif
