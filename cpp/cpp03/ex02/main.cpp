#include "FragTrap.hpp"

#include "FragTrap.hpp"

int main( void ) {
	std::cout << "=== Creating FragTrap ===" << std::endl;
	FragTrap frag("FT-00");

	std::cout << "\n=== Testing attacks ===" << std::endl;
	frag.attack("HandsomeJack");
	frag.takeDamage(50);
	frag.beRepaired(30);

	std::cout << "\n=== Special ability ===" << std::endl;
	frag.highFivesGuys();

	std::cout << "\n=== End of program ===" << std::endl;
	return 0;
}
