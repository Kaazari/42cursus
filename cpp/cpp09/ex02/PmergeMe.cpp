#include "PmergeMe.hpp"
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <climits>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg.empty())
			throw InvalidArgumentException();
		for (size_t j = 0; j < arg.length(); ++j) {
			if (!std::isdigit(static_cast<unsigned char>(arg[j])))
				throw InvalidArgumentException();
		}
		errno = 0;
		char* end = 0;
		long val = std::strtol(arg.c_str(), &end, 10);
		if (*end != '\0' || errno == ERANGE || val > INT_MAX || val < 0)
			throw InvalidArgumentException();
		_input.push_back(static_cast<int>(val));
	}
}

PmergeMe::PmergeMe(const PmergeMe& other) : _input(other._input) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs) {
	if (this != &rhs)
		_input = rhs._input;
	return *this;
}

PmergeMe::~PmergeMe() {}

// Time

double getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

// Jacobsthal insertion order
// Pend has pendSize elements b_1..b_p 1-based (1, 2, 3, 4, 5...)
// b_1 is inserted at the front separately.
// This returns the 0-based (0, 1, 2, 3, 4...) indices
// of b_2..b_p in the order dictated by the Jacobsthal numbers (1,3,5,11,21,...).
// J(n) = J(n-1) + 2*J(n-2)
std::vector<size_t> PmergeMe::jacobOrder(size_t p) {
	std::vector<size_t> order;
	if (p <= 1)
		return order;
	std::vector<size_t> jac;
	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < p) {
		size_t n = jac.size();
		jac.push_back(jac[n - 1] + 2 * jac[n - 2]);
	}
	for (size_t c = 1; c < jac.size(); ++c) {
		size_t hi = jac[c];
		size_t lo = jac[c - 1] + 1;
		if (hi > p) hi = p;
		if (lo > p) break;
		for (size_t j = hi; j >= lo; --j) {
			order.push_back(j - 1);
			if (j == lo) break;
		}
	}
	return order;
}

// Vector implementation

// Sort a vector of (big, small) pairs ascending by .first, using
// merge-insertion. Pairs stay together so each big keeps its small.
void PmergeMe::sortPairsByFirstVec(std::vector<std::pair<int, int> >& p) {
	size_t m = p.size();
// Recursion cond is when there is only 1 pair left
	if (m < 2)
		return;

	bool odd = (m % 2 == 1);
	std::pair<int, int> straggler;
	if (odd)
		straggler = p[m - 1];

// Send the biggest .first in bigs and the smallest .first in smalls
// by comparing the 2 given pairs (i += 2)
// Recursion compares the bigs so its sorted and we end with only
// the biggest pair (according to .first)
	std::vector<std::pair<int, int> > bigs, smalls;
	for (size_t i = 0; i + 1 < m; i += 2) {
		std::pair<int, int> a = p[i], b = p[i + 1];
		if (a.first < b.first)
			std::swap(a, b);
		bigs.push_back(a);
		smalls.push_back(b);
	}

// Recursion of the bigs
	sortPairsByFirstVec(bigs);

// Add along the recursion the smalls to the final result which start
// with bigs. Binary search (mid / lo + hi) is used for efficiency.
// Pairs are added 1 by 1 thanks to recursion.
	std::vector<std::pair<int, int> > res = bigs;
	for (size_t i = 0; i < smalls.size(); ++i) {
		int lo = 0, hi = static_cast<int>(res.size());
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (res[mid].first < smalls[i].first) lo = mid + 1;
			else hi = mid;
		}
		res.insert(res.begin() + lo, smalls[i]);
	}
// Straggler cond
	if (odd) {
		int lo = 0, hi = static_cast<int>(res.size());
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (res[mid].first < straggler.first) lo = mid + 1;
			else hi = mid;
		}
		res.insert(res.begin() + lo, straggler);
	}
	p = res;
}

// Binary insertion of the pend[jacobOrder] value
void PmergeMe::binaryInsertVec(std::vector<int>& chain, int value) {
	int lo = 0, hi = static_cast<int>(chain.size());
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (chain[mid] < value) lo = mid + 1;
		else hi = mid;
	}
	chain.insert(chain.begin() + lo, value);
}

void PmergeMe::fordJohnsonVec(std::vector<int>& v) {
	size_t n = v.size();
	if (n < 2)
		return;

	bool odd = (n % 2 == 1);
	int straggler = 0;
	if (odd)
		straggler = v[n - 1];

// Creation of pairs, if a < b we swap in order to always have (big, small)
// with pairs.first and pairs.second. (a = bigs, b == smalls)
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2) {
		int a = v[i], b = v[i + 1];
		if (a < b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

// Sorting of pairs by recursion and binary search.
	sortPairsByFirstVec(pairs);

// Split the pairs into main(bigs) and pend(smalls)
	std::vector<int> main, pend;
	for (size_t i = 0; i < pairs.size(); ++i) {
		main.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}


// Creation of the sorted vector (chain) with pend[0] at first because
// by construction pend[0] < main[0]
	std::vector<int> chain;
	chain.push_back(pend[0]);
	for (size_t i = 0; i < main.size(); ++i)
		chain.push_back(main[i]);


// Definition of the Jacobsthal order depending on the size of the
// numbers to insert (pend vector)
// Insertion of the pendings binary in the Jacobsthal order to
// avoid excessive comparisons.
	std::vector<size_t> order = jacobOrder(pend.size());
	for (size_t o = 0; o < order.size(); ++o)
		binaryInsertVec(chain, pend[order[o]]);
	if (odd)
		binaryInsertVec(chain, straggler);

	v = chain;
}

// Deque implementation (exact same as vector)

void PmergeMe::sortPairsByFirstDeq(std::deque<std::pair<int, int> >& p) {
	size_t m = p.size();
	if (m < 2)
		return;

	bool odd = (m % 2 == 1);
	std::pair<int, int> straggler;
	if (odd)
		straggler = p[m - 1];

	std::deque<std::pair<int, int> > bigs, smalls;
	for (size_t i = 0; i + 1 < m; i += 2) {
		std::pair<int, int> a = p[i], b = p[i + 1];
		if (a.first < b.first)
			std::swap(a, b);
		bigs.push_back(a);
		smalls.push_back(b);
	}

	sortPairsByFirstDeq(bigs);

	std::deque<std::pair<int, int> > res = bigs;
	for (size_t i = 0; i < smalls.size(); ++i) {
		int lo = 0, hi = static_cast<int>(res.size());
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (res[mid].first < smalls[i].first) lo = mid + 1;
			else hi = mid;
		}
		res.insert(res.begin() + lo, smalls[i]);
	}
	if (odd) {
		int lo = 0, hi = static_cast<int>(res.size());
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (res[mid].first < straggler.first) lo = mid + 1;
			else hi = mid;
		}
		res.insert(res.begin() + lo, straggler);
	}
	p = res;
}

void PmergeMe::binaryInsertDeq(std::deque<int>& chain, int value) {
	int lo = 0, hi = static_cast<int>(chain.size());
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (chain[mid] < value) lo = mid + 1;
		else hi = mid;
	}
	chain.insert(chain.begin() + lo, value);
}

void PmergeMe::fordJohnsonDeq(std::deque<int>& v) {
	size_t n = v.size();
	if (n < 2)
		return;

	bool odd = (n % 2 == 1);
	int straggler = 0;
	if (odd)
		straggler = v[n - 1];

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2) {
		int a = v[i], b = v[i + 1];
		if (a < b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	sortPairsByFirstDeq(pairs);

	std::deque<int> main, pend;
	for (size_t i = 0; i < pairs.size(); ++i) {
		main.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	std::deque<int> chain;
	chain.push_back(pend[0]);
	for (size_t i = 0; i < main.size(); ++i)
		chain.push_back(main[i]);

	std::vector<size_t> order = jacobOrder(pend.size());
	for (size_t o = 0; o < order.size(); ++o)
		binaryInsertDeq(chain, pend[order[o]]);
	if (odd)
		binaryInsertDeq(chain, straggler);

	v = chain;
}

// run

void PmergeMe::run() {
	std::cout << "Before:";
	for (size_t i = 0; i < _input.size(); ++i)
		std::cout << " " << _input[i];
	std::cout << std::endl;

	// vector : time data management (fill) + sort
	double t0 = getTime();
	std::vector<int> vec(_input.begin(), _input.end());
	fordJohnsonVec(vec);
	double timeVec = getTime() - t0;

	// deque : time data management (fill) + sort
	t0 = getTime();
	std::deque<int> deq(_input.begin(), _input.end());
	fordJohnsonDeq(deq);
	double timeDeq = getTime() - t0;

	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << " " << vec[i];
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _input.size()
			  << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _input.size()
			  << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
