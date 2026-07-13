#include "searchable_tree_bag.hpp"
#include <cstdlib>

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
	if (this != &src)
		tree_bag::operator=(src);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::search(node *n, int value) const {
	if (n == NULL)
		return false;
	if (n->value == value)
		return true;
	if (value < n->value)
		return search(n->l, value);
	return search(n->r, value);
}

bool searchable_tree_bag::has(int value) const {
	return search(this->tree, value);
}
