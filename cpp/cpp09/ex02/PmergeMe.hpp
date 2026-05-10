#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <sys/time.h>

class PmergeMe {
private:
	std::vector<int> _vec;
	std::deque<int>  _deq;

	PmergeMe();

	// Ford-Johnson for vector
	void mergeInsertSortVec(std::vector<int>& arr, int left, int right);
	void insertionSortVec(std::vector<int>& arr, int left, int right);
	void mergeVec(std::vector<int>& arr, int left, int mid, int right);

	// Ford-Johnson for deque
	void mergeInsertSortDeq(std::deque<int>& arr, int left, int right);
	void insertionSortDeq(std::deque<int>& arr, int left, int right);
	void mergeDeq(std::deque<int>& arr, int left, int mid, int right);

public:
	PmergeMe(int argc, char** argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();

	void run();

	class InvalidArgumentException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Error: Invalid argument";
		}
	};
};

double getTime();

#endif
