#ifndef TRAIN_HPP
# define TRAIN_HPP

# include <iostream>

class Contact {
private:

const std::string _firstName;
const std::string _lastName;
const int 			_age;

public:
// Default constructor
Contact();

Contact(std::string firstName, std::string lastName, int age);

// Copy constructor
Contact(const Contact& og);
// Copy assignment operator
Contact& operator=(const Contact& og);
// Destructor
~Contact();

// Getters
std::string getFirstName();
std::string getLastName();
int getAge();

// Info Printer
void displayInfo();

};

#endif
