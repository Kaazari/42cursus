#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog constructor called" << std::endl;
	_brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog copy constructor called" << std::endl;
	_brain = new Brain(*other._brain);
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		delete _brain;
		_brain = new Brain(*other._brain);
	}
	return *this;
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
	delete _brain;
}

void Dog::makeSound() const {
	std::cout << "🐶: Woof! Woof!" << std::endl;
}

void Dog::setBrainIdea(int index, std::string idea) {
	_brain->setIdea(index, idea);
}

std::string Dog::getBrainIdea(int index) const {
	return _brain->getIdea(index);
}
