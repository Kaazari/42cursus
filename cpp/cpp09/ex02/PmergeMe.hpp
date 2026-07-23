#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <sys/time.h>

class PmergeMe {
private:
	std::vector<int> _input;

	PmergeMe();

	// Jacobsthal insertion order (pure index math, shared by both containers)
	std::vector<size_t> jacobOrder(size_t pendSize);

	// Ford-Johnson for std::vector
	void sortPairsByFirstVec(std::vector<std::pair<int, int> >& p);
	void binaryInsertVec(std::vector<int>& chain, int value);
	void fordJohnsonVec(std::vector<int>& v);

	// Ford-Johnson for std::deque
	void sortPairsByFirstDeq(std::deque<std::pair<int, int> >& p);
	void binaryInsertDeq(std::deque<int>& chain, int value);
	void fordJohnsonDeq(std::deque<int>& v);

public:
	PmergeMe(int argc, char** argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();

	void run();

	class InvalidArgumentException : public std::exception {
	public:
		virtual const char* what() const throw() { return "Error: Invalid argument"; }
	};
};

double getTime();

#endif
