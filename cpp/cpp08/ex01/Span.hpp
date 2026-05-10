#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

class Span {
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

	Span();

public:
	Span(unsigned int N);
	Span(const Span& other);
	Span& operator=(const Span& rhs);
	~Span();

	void addNumber(int number);

	template <typename Iterator>
	void addNumber(Iterator begin, Iterator end) {
		while (begin != end) {
			if (_numbers.size() >= _maxSize)
				throw std::length_error("Span is full");
			_numbers.push_back(*begin);
			++begin;
		}
	}

	int shortestSpan() const;
	int longestSpan() const;

	class SpanFullException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Span is already full";
		}
	};

	class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Not enough numbers to calculate span";
		}
	};
};

#endif
