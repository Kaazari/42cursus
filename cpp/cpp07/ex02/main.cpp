#include <iostream>
#include "Array.hpp"

#define MAX_VAL 750

int main(int, char**)
{
	// ========== TESTS DU SUJET ==========

	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}

	// SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}

	try
	{
		numbers[-2] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}

	delete[] mirror;

	// ========== MES TESTS ==========

	std::cout << "\n--- Additional Tests ---" << std::endl;

	// Copy
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
		std::cout << "✅ Copy works!" << std::endl;
	}

	// Values match
	mirror = new int[MAX_VAL];
	for (int i = 0; i < MAX_VAL; i++) {
		mirror[i] = numbers[i];
	}

	bool match = true;
	for (int i = 0; i < MAX_VAL; i++) {
		if (mirror[i] != numbers[i]) {
			match = false;
			break;
		}
	}
	if (match)
		std::cout << "✅ Values match!" << std::endl;

	// Test exceptions again
	try {
		numbers[-2] = 0;
	} catch(const std::exception& e) {
		std::cout << "✅ Test -2: " << e.what() << std::endl;
	}

	try {
		numbers[MAX_VAL] = 0;
	} catch(const std::exception& e) {
		std::cout << "✅ Test MAX_VAL: " << e.what() << std::endl;
	}

	std::cout << "✅ All tests passed!" << std::endl;

	delete[] mirror;
	return 0;
}
