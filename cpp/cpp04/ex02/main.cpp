#include <iostream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
	std::cout << "=== TEST CLASSE ABSTRAITE ===" << std::endl;

	// Ne compile pas
	// AAnimal Aanimal;
	// const AAnimal* test = new AAnimal();

	std::cout << "\n=== TEST CREATION ===" << std::endl;
	const AAnimal* dog = new Dog();
	const AAnimal* cat = new Cat();

	std::cout << "\n=== TEST MAKESOUND ===" << std::endl;
	dog->makeSound();
	cat->makeSound();

	std::cout << "\n=== TEST TABLEAU ===" << std::endl;
	{
		const AAnimal* Aanimals[4];

		std::cout << "Creating 2 Dogs and 2 Cats..." << std::endl;
		for (int i = 0; i < 2; i++)
			Aanimals[i] = new Dog();

		for (int i = 2; i < 4; i++)
			Aanimals[i] = new Cat();

		std::cout << "\nMaking sounds..." << std::endl;
		for (int i = 0; i < 4; i++)
			Aanimals[i]->makeSound();

		std::cout << "\nDeleting all..." << std::endl;
		for (int i = 0; i < 4; i++)
			delete Aanimals[i];
	}

	return 0;
}
