#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
private:

public:
	MutantStack() : std::stack<T>() {};

	MutantStack(const MutantStack& src) : std::stack<T>() {};

	MutantStack& operator=(const MutantStack& rhs) {
		if (this != &rhs)
			std::stack<T>::operator=(rhs);
		return *this;
	};

	~MutantStack() {};

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); };
	iterator end() { return this->c.end(); };

};

#endif
