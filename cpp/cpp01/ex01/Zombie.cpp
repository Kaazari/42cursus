#include "Zombie.hpp"

Zombie::Zombie() : _name("") {
	std::cout << "Zombie has been created" << std::endl;
}

Zombie::Zombie(std::string name) : _name(name) {
	std::cout << _name << " created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << _name << " destroyed" << std::endl;
}

void Zombie::announce() const {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
		_name = name;
}
