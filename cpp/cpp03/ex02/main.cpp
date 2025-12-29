#include "FragTrap.hpp"

#include "FragTrap.hpp"

int main( void ) {
	FragTrap frag("FT-00");

	frag.attack("HandsomeJack");
	frag.takeDamage(50);
	frag.beRepaired(30);

	frag.highFivesGuys();

	return 0;
}
