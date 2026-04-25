#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
	T*				_data;
	unsigned int	_size;

public:
	// Constructors
	Array();
	Array(unsigned int n);
	Array(Array const& src);
	~Array();

	// Assignements
	Array& operator=(Array const& rhs);

	// Index
	T& operator[](unsigned int i);
	const T& operator[](unsigned int i) const;

	unsigned int size() const;
};

template <typename T>
Array<T>::Array(): _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n): _data(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(Array const& src): _data(new T[src._size]()), _size(src._size) {
	for (unsigned int i = 0; i < _size; i++)
		_data[i] = src._data[i];
}

template <typename T>
Array<T>::~Array() {
	delete[] _data;
}
template <typename T>
Array<T>& Array<T>::operator=(Array const& rhs) {
	if (this != &rhs) {
		delete[] _data;

		_size = rhs._size;
		_data = new T[_size]();
		for (unsigned int i = 0; i < _size; i++)
			_data[i] = rhs._data[i];
	}
	return *this;
}

template <typename T>
const T& Array<T>::operator[](unsigned int i) const {
	if (i >= _size)
		throw std::out_of_range("Index out of bounds");
	return _data[i];
}

template <typename T>
 T& Array<T>::operator[](unsigned int i) {
	if (i >= _size)
		throw std::out_of_range("Index out of bounds");
	return _data[i];
}

template <typename T>
unsigned int Array<T>::size() const {
	return _size;
}

#endif
