#include "Zombie.hpp"

// external use
Zombie* newZombie(std::string name) {
	Zombie *z = new Zombie(name);
	return z;
}
