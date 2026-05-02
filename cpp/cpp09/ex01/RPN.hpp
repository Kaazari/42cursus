// RPN.hpp
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class RPN {
private:
	std::stack<int> _stack;

	bool isOperator(std::string const& token);
	bool isNumber(std::string const& token);
	int calculate(int a, int b, char op);

public:
	RPN();
	RPN(RPN const& src);
	~RPN();
	RPN& operator=(RPN const& rhs);

	int evaluate(std::string const& expression);
};

#endif
