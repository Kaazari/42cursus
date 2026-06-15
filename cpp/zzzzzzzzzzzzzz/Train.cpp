#include "Train.hpp"

Contact::Contact() :
_firstName("xxxxx"), _lastName("xxxxx"), _age(0) {}

Contact::Contact(std::string firstName, std::string lastName, int age) :
_firstName(firstName), _lastName(lastName), _age(age) {}

Contact::Contact(const Contact& og) : _firstName(og._firstName), _lastName(og._lastName), _age(og._age) {}

Contact& Contact::operator=(const Contact& og) {
	if (this != &og) {
		*this = og;
	}
	return (*this);
}

Contact::~Contact() {}

std::string Contact::getFirstName() { return (_firstName); }

std::string Contact::getLastName() { return (_lastName); }

int Contact::getAge() { return (_age); }

void Contact::displayInfo() {
	std::cout << _firstName << _lastName << _age << std::endl;
}

