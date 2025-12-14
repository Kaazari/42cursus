#ifndef PHONE_BOOK_HPP
# define PHONE_BOOK_HPP

# include <string>
# include <iostream>
# include "Contact.hpp"

class PhoneBook {
private:
	Contact _contacts[8];
	int		_count;
	int		_index;

public:
	PhoneBook();
	~PhoneBook();

	void addContact();
	void searchContact();
	void displayContact(int index);
	std::string getInput(std::string prompt);
	std::string formatField(std::string str) const;
};

#endif
