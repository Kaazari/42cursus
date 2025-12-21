#include "Zombie.hpp"

int main( void ) {
	std::cout << "=== Creating heap zombie ===" << std::endl;
	Zombie* zombie1 = newZombie("Heap");

	std::cout << "\n=== Heap zombie announces ===" << std::endl;
	zombie1->announce();

	std::cout << "\n=== Creating stack zombie ===" << std::endl;
	randomChump("Stack");
	std::cout << "(Stack zombie was destroyed automatically)" << std::endl;

	std::cout << "\n=== Creating another heap zombie ===" << std::endl;
	Zombie* zombie2 = newZombie("Heaaaaaaaap");
	zombie2->announce();

	std::cout << "\n=== Deleting heap zombies ===" << std::endl;
	delete zombie1;
	delete zombie2;

	std::cout << "\n=== Multiple stack zombies ===" << std::endl;
	randomChump("Z");
	randomChump("Zz");
	randomChump("Zzz");

	std::cout << "\n=== End of program ===" << std::endl;

	return 0;
}
