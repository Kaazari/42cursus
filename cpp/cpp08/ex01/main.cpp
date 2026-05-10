#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main() {
	std::cout << "=== Test 1: Subject example ===" << std::endl;
	try {
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Exception when full ===" << std::endl;
	try {
		Span sp = Span(3);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		sp.addNumber(4); // Should throw
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Exception with 0 or 1 element ===" << std::endl;
	try {
		Span sp = Span(5);
		sp.addNumber(42);
		std::cout << sp.shortestSpan() << std::endl; // Should throw
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Range of iterators ===" << std::endl;
	try {
		Span sp = Span(10);
		std::vector<int> v;
		v.push_back(5);
		v.push_back(10);
		v.push_back(15);
		v.push_back(20);

		sp.addNumber(v.begin(), v.end());
		sp.addNumber(25);

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: 10,000 numbers ===" << std::endl;
	try {
		Span sp = Span(10000);
		std::vector<int> numbers;

		std::srand(std::time(NULL));
		for (int i = 0; i < 10000; i++) {
			numbers.push_back(std::rand());
		}

		sp.addNumber(numbers.begin(), numbers.end());

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Negative numbers ===" << std::endl;
	try {
		Span sp = Span(5);
		sp.addNumber(-10);
		sp.addNumber(-5);
		sp.addNumber(0);
		sp.addNumber(5);
		sp.addNumber(10);

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
