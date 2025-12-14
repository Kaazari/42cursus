#include "PhoneBook.hpp"
#include <iostream>

int main() {
	PhoneBook phonebook;
	std::string command;

	std::cout << "Welcome to PhoneBook!" << std::endl;
	std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, command);

		if (command == "ADD") {
			phonebook.addContact();
		}
		else if (command == "SEARCH") {
			phonebook.searchContact();
		}
		else if (command == "EXIT") {
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else {
			std::cout << "Invalid command. Use ADD, SEARCH, or EXIT" << std::endl;
		}
	}

	return 0;
}
