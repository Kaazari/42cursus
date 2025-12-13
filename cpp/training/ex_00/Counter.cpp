#include "Counter.hpp"
#include <iostream>

// using namespace std; unauthorized
// *printf, *alloc, free unauthorized
// STL, Algorithms, Containers unauthorized

Counter::Counter() {
	_value = 0;
	std::cout << "Initiated!" << std::endl;
}

Counter::~Counter() {
	std::cout << "Anihilation..." << std::endl;
}

void Counter::increment() {
	_value += 1;
}

void Counter::decrement() {
	_value -= 1;
}

int Counter::getValue() const {
	return _value;
}
