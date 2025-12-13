#include "IntArray.hpp"
#include <iostream>

IntArray::IntArray(int size) {
	_size = size;
	_array = new int[size];
	std::cout << "Initiated!" << std::endl;
}

IntArray::~IntArray() {
	delete[] _array;
	std::cout << "Anihilation." << std::endl;
}

void IntArray::set(int index, int value) {
	if (index <= _size)
		_array[index] = value;
	else
		std::cout << "err" << std::endl;
}

int IntArray::get(int index) const {
	if (index <= _size)
		return (_array[index]);
	else
		std::cout << "err" << std::endl;
	return (1);
}

int IntArray::getSize() const {
	return (_size);
}
