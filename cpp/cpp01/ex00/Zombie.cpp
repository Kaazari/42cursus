#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : _name(name) {
	std::cout << _name << " created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << _name << " destroyed" << std::endl;
}

void Zombie::announce() const {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
