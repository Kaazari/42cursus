#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		_ideas[i] = other._ideas[i];  // Deep copy
}

Brain& Brain::operator=(const Brain& other) {
	std::cout << "Brain assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < 100; i++)
			_ideas[i] = other._ideas[i];  // Deep copy
	}
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, std::string idea) {
	if (index >= 0 && index < 100)
		_ideas[index] = idea;
}

std::string Brain::getIdea(int index) const {
	if (index >= 0 && index < 100)
		return _ideas[index];
	return "";
}
