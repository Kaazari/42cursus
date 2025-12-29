#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
	std::cout << "=== TEST DU SUJET ===" << std::endl;
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		delete j;
		delete i;
	}

	std::cout << "\n=== TEST ARRAY ===" << std::endl;
	{
		const int size = 4;
		Animal* animals[size];

		for (int i = 0; i < size / 2; i++)
			animals[i] = new Dog();

		for (int i = size / 2; i < size; i++)
			animals[i] = new Cat();

		for (int i = 0; i < size; i++)
			delete animals[i];
	}

	std::cout << "\n=== TEST DEEP COPY (Dog) ===" << std::endl;
	{
		Dog dog1;
		dog1.setBrainIdea(0, "I love bones 🦴");
		dog1.setBrainIdea(1, "Chase that cat 🐈");

		std::cout << "\nCopying dog1 to dog2..." << std::endl;
		Dog dog2(dog1);

		std::cout << "\nOriginal ideas:" << std::endl;
		std::cout << "dog1[0]: " << dog1.getBrainIdea(0) << std::endl;
		std::cout << "dog2[0]: " << dog2.getBrainIdea(0) << std::endl;

		std::cout << "\nModifying dog1..." << std::endl;
		dog1.setBrainIdea(0, "I want to sleep 💤");

		std::cout << "\nAfter modification:" << std::endl;
		std::cout << "dog1[0]: " << dog1.getBrainIdea(0) << std::endl;
		std::cout << "dog2[0]: " << dog2.getBrainIdea(0) << std::endl;
		std::cout << "(Should be DIFFERENT - deep copy!)" << std::endl;
	}

	std::cout << "\n=== TEST DEEP COPY (Cat) ===" << std::endl;
	{
		Cat cat1;
		cat1.setBrainIdea(0, "Catch mice 🐭");

		Cat cat2;
		cat2 = cat1;

		std::cout << "cat1[0]: " << cat1.getBrainIdea(0) << std::endl;
		std::cout << "cat2[0]: " << cat2.getBrainIdea(0) << std::endl;

		cat1.setBrainIdea(0, "Sleep on keyboard ⌨️");

		std::cout << "\nAfter modification:" << std::endl;
		std::cout << "cat1[0]: " << cat1.getBrainIdea(0) << std::endl;
		std::cout << "cat2[0]: " << cat2.getBrainIdea(0) << std::endl;
		std::cout << "(Should be DIFFERENT)" << std::endl;
	}

	std::cout << "\n=== TEST ASSIGNMENT ===" << std::endl;
	{
		Dog* dog1 = new Dog();
		Dog* dog2 = new Dog();

		dog1->setBrainIdea(0, "Idea 1 💡");
		dog2->setBrainIdea(0, "Idea 2 💡");

		std::cout << "Before: dog2[0] = " << dog2->getBrainIdea(0) << std::endl;

		*dog2 = *dog1;

		std::cout << "After:  dog2[0] = " << dog2->getBrainIdea(0) << std::endl;

		delete dog1;
		delete dog2;
	}

	return 0;
}
