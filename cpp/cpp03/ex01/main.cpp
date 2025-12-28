#include "ScavTrap.hpp"

int main() {
	ScavTrap scav("ST-00");

	scav.attack("Lilith");
	scav.takeDamage(90);
	scav.beRepaired(10);
	scav.guardGate();
	scav.takeDamage(90);
	scav.guardGate();
	return (0);
}
