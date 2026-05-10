#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		// Check negative or non-numeric
		for (size_t j = 0; j < arg.length(); j++) {
			if (!isdigit(arg[j]))
				throw InvalidArgumentException();
		}

		std::istringstream iss(arg);
		int num;
		iss >> num;

		if (num < 0)
			throw InvalidArgumentException();

		_vec.push_back(num);
		_deq.push_back(num);
	}
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs) {
	if (this != &rhs) {
		_vec = rhs._vec;
		_deq = rhs._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

double getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

// VECTOR IMPLEMENTATION

void PmergeMe::insertionSortVec(std::vector<int>& arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void PmergeMe::mergeVec(std::vector<int>& arr, int left, int mid, int right) {
	std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
	std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

	size_t i = 0, j = 0;
	int k = left;

	while (i < leftArr.size() && j < rightArr.size()) {
		if (leftArr[i] <= rightArr[j])
			arr[k++] = leftArr[i++];
		else
			arr[k++] = rightArr[j++];
	}

	while (i < leftArr.size())
		arr[k++] = leftArr[i++];
	while (j < rightArr.size())
		arr[k++] = rightArr[j++];
}

void PmergeMe::mergeInsertSortVec(std::vector<int>& arr, int left, int right) {
	if (right - left <= 10) {
		insertionSortVec(arr, left, right);
		return;
	}

	int mid = left + (right - left) / 2;
	mergeInsertSortVec(arr, left, mid);
	mergeInsertSortVec(arr, mid + 1, right);
	mergeVec(arr, left, mid, right);
}

// DEQUE IMPLEMENTATION

void PmergeMe::insertionSortDeq(std::deque<int>& arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void PmergeMe::mergeDeq(std::deque<int>& arr, int left, int mid, int right) {
	std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
	std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

	size_t i = 0, j = 0;
	int k = left;

	while (i < leftArr.size() && j < rightArr.size()) {
		if (leftArr[i] <= rightArr[j])
			arr[k++] = leftArr[i++];
		else
			arr[k++] = rightArr[j++];
	}

	while (i < leftArr.size())
		arr[k++] = leftArr[i++];
	while (j < rightArr.size())
		arr[k++] = rightArr[j++];
}

void PmergeMe::mergeInsertSortDeq(std::deque<int>& arr, int left, int right) {
	if (right - left <= 10) {
		insertionSortDeq(arr, left, right);
		return;
	}

	int mid = left + (right - left) / 2;
	mergeInsertSortDeq(arr, left, mid);
	mergeInsertSortDeq(arr, mid + 1, right);
	mergeDeq(arr, left, mid, right);
}

// RUN

void PmergeMe::run() {
	// Print before
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size() && i < 5; i++)
		std::cout << _vec[i] << " ";
	if (_vec.size() > 5)
		std::cout << "[...]";
	std::cout << std::endl;

	// Sort with vector
	double startVec = getTime();
	mergeInsertSortVec(_vec, 0, _vec.size() - 1);
	double endVec = getTime();
	double timeVec = endVec - startVec;

	// Sort with deque
	double startDeq = getTime();
	mergeInsertSortDeq(_deq, 0, _deq.size() - 1);
	double endDeq = getTime();
	double timeDeq = endDeq - startDeq;

	// Print after
	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size() && i < 5; i++)
		std::cout << _vec[i] << " ";
	if (_vec.size() > 5)
		std::cout << "[...]";
	std::cout << std::endl;

	// Print times
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
