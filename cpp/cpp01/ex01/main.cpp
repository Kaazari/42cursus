#include "Zombie.hpp"

int main( void ) {
	// Test 1 : Small horde
	std::cout << "=== Test 1 : Small horde (3 zombies) ===" << std::endl;
	Zombie* smallHorde = zombieHorde(3, "Walker");
	for (int i = 0; i < 3; i++) {
		smallHorde[i].announce();
	}
	delete[] smallHorde;

	std::cout << std::endl;

	// Test 2 : Large Horde
	std::cout << "=== Test 2 : Large horde (10 zombies) ===" << std::endl;
	Zombie* largeHorde = zombieHorde(10, "Runner");
	std::cout << "Making all 10 zombies announce:" << std::endl;
	for (int i = 0; i < 10; i++) {
		largeHorde[i].announce();
	}
	delete[] largeHorde;

	std::cout << std::endl;

	// Test 3 : Single
	std::cout << "=== Test 3 : Single zombie horde ===" << std::endl;
	Zombie* single = zombieHorde(1, "Alone");
	single[0].announce();
	delete[] single;

	std::cout << std::endl;
	std::cout << "=== End of program ===" << std::endl;

	return 0;
}
