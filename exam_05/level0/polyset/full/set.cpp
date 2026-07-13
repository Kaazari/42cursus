#include "set.hpp"

set::set(searchable_bag& bag) : _bag(bag) {}

set::~set() {}

bool set::has(int value) const {
	return _bag.has(value);
}

void set::insert(int value) {
	if (!_bag.has(value))
		_bag.insert(value);
}

void set::insert(int *items, int count) {
	for (int i = 0; i < count; i++) {
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

const searchable_bag& set::get_bag() const {
	return _bag;
}
