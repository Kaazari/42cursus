#include  "ClapTrap.hpp"

int  main() {
	ClapTrap clap("CT-00");
	clap.attack("Roland");
	clap.takeDamage(5);
	clap.beRepaired(3);

	return (0);
}
