#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
	std::cout << "=== TEST DU SUJET ===" << std::endl;
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;

		i->makeSound();
		j->makeSound();
		meta->makeSound();

		delete i;
		delete j;
		delete meta;
	}

	std::cout << "\n=== TEST POLYMORPHISME ===" << std::endl;
	{
		Animal* animals[3];
		animals[0] = new Animal();
		animals[1] = new Dog();
		animals[2] = new Cat();

		for (int i = 0; i < 3; i++) {
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}

		for (int i = 0; i < 3; i++)
			delete animals[i];
	}

	std::cout << "\n=== TEST WRONGANIMAL (sans virtual) ===" << std::endl;
	{
		const WrongAnimal* wrong = new WrongAnimal();
		const WrongAnimal* wrongCat = new WrongCat();

		std::cout << "WrongAnimal: ";
		wrong->makeSound();

		std::cout << "WrongCat (via WrongAnimal*): ";
		wrongCat->makeSound();

		delete wrong;
		delete wrongCat;
	}

	return 0;
}
