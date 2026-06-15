#include "Train.hpp"

int main() {
	Contact bro;

	{
		std::cout << bro.getFirstName() << bro.getLastName() << bro.getAge() << std::endl;
	}

	Contact you("kaa", "zari", 22);

	{
		std::cout << you.getFirstName() << you.getLastName() << you.getAge() << std::endl;
	}
}
