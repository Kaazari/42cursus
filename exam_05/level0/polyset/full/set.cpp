#include "set.hpp"

set::set(searchable_bag& src) : _bag(src) {}

set::~set() {}

void set::insert(int value) {
	if (!_bag.has(value))
		_bag.insert(value);
}

void set::insert(int *items, int value) {
	for (int i = 0; i < value; i++) {
		if (!_bag.has(items[i]))
			_bag.insert(items[i]);
	}
}

void set::print() const {
	_bag.print();
}

void set::clear() {
	_bag.clear();
}

bool set::has(int value) const{
	return _bag.has(value);
}

const searchable_bag& set::get_bag() const {
	return _bag;
}
