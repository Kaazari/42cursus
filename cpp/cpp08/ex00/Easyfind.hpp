#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>
#include <iostream>
#include <vector>
#include <list>

template <typename T>
typename T::iterator easyfind(T& container, int value) {
	typename T::iterator it;

	for (it = container.begin(); it != container.end(); it++) {
		if (*it == value)
			return it;
	}

	throw std::exception();
}

#endif
