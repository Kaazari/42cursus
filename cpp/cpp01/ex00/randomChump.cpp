#include "Zombie.hpp"

// internal / ephemeral use
void randomChump(std::string name) {
	Zombie z(name);
	z.announce();
}
