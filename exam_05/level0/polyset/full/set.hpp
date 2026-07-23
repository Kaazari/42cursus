#ifndef SET__HPP
# define SET__HPP

#include "searchable_bag.hpp"

class set {
private:
	searchable_bag& _bag;

	set();
	set(const set& src);
	set& operator=(const set& src);

public:
	set(searchable_bag& src);
	~set();

	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();
	bool has(int) const;
	const searchable_bag& get_bag() const;
};

#endif
