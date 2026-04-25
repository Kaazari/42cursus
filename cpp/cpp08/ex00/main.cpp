#include "Easyfind.hpp"

int main() {
	// Test 1: Vector - trouvé
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	try {
		std::vector<int>::iterator it = easyfind(vec, 2);
		std::cout << "✅ Found in vector: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << "❌ Not found in vector" << std::endl;
	}

	// Test 2: Vector - pas trouvé
	try {
		std::vector<int>::iterator it = easyfind(vec, 99);
		std::cout << "❌ Found in vector: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << "✅ Not found in vector (expected)" << std::endl;
	}

	// Test 3: List - trouvé
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);

	try {
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "✅ Found in list: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << "❌ Not found in list" << std::endl;
	}

	// Test 4: List - pas trouvé
	try {
		std::list<int>::iterator it = easyfind(lst, 50);
		std::cout << "❌ Found in list: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << "✅ Not found in list (expected)" << std::endl;
	}

	return 0;
}
