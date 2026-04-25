#include "Form.hpp"
#include "Bureaucrat.hpp"

// Constructor
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _is_signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

// Copy constructor
Form::Form(const Form& other)
	: _name(other._name), _is_signed(other._is_signed),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

// Assignment operator
Form& Form::operator=(const Form& other) {
	if (this != &other) {
		// _name, _gradeToSign, _gradeToExecute sont const, on peut pas les reassigner
		_is_signed = other._is_signed;  // Seul _is_signed peut changer
	}
	return *this;
}

// Destructor
Form::~Form() {}

// beSigned
void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_is_signed = true;
}

// operator<< overload
std::ostream& operator<<(std::ostream& out, const Form& f) {
	out << "Form " << f.getName()
		<< ", signed: " << (f.isSigned() ? "yes" : "no")
		<< ", grade to sign: " << f.getGradeToSign()
		<< ", grade to execute: " << f.getGradeToExecute();
	return out;
}
