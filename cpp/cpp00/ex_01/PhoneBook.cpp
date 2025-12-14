#include "PhoneBook.hpp"

PhoneBook::PhoneBook() {
	_count = 0;
	_index = 0;
}

PhoneBook::~PhoneBook() {
	std::cout << "PhoneBook has been deleted." << std::endl;
}

std::string PhoneBook::getInput(std::string prompt) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (input.empty())
			std::cout << "Error: Field cannot be empty." << std::endl;
	} while (input.empty());

	return (input);
}

std::string PhoneBook::formatField(std::string str) const {
	if (str.length() > 10) {
		str = str.substr(0, 9);
		str += ".";
	}

	while (str.length() < 10)
		str = " " + str;
	return (str);
}

void PhoneBook::addContact() {
	_contacts[_index].setFirstName(getInput("First Name: "));
	_contacts[_index].setLastName(getInput("Last Name: "));
	_contacts[_index].setNickname(getInput("Nickname: "));
	_contacts[_index].setPhoneNumber(getInput("Phone Number: "));
	_contacts[_index].setDarkestSecret(getInput("Darkest Secret: "));

	_index = (_index + 1) % 8;
	if (_count < 8)
		_count++;

	std::cout << "Contact has been succesfully added!" << std::endl;
}

void PhoneBook::searchContact() {
	if (_count == 0) {
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	std::cout << formatField("Index") << "|";
	std::cout << formatField("First Name") << "|";
	std::cout << formatField("Last Name") << "|";
	std::cout << formatField("Nickname") << std::endl;

	for (int i = 0; i < _count; i++) {
		std::cout << formatField(std::to_string(i)) << "|";
		std::cout << formatField(_contacts[i].getFirstName()) << "|";
		std::cout << formatField(_contacts[i].getLastName()) << "|";
		std::cout << formatField(_contacts[i].getNickname()) << std::endl;
	}

	std::cout << "Enter index: ";
	int index;
	std::cin >> index;
	std::cin.ignore();

	if (index >= 0 && index < _count) {
		displayContact(index);
	}
	else {
		std::cout << "Invalid index" << std::endl;
	}
}

void PhoneBook::displayContact(int index) {
	std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
}
