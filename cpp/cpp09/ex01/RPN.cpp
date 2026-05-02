#include "RPN.hpp"

RPN::RPN() {
}

RPN::RPN(RPN const& src) {
	*this = src;
}

RPN& RPN::operator=(RPN const& rhs) {
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(std::string const& token) {
	return (token == "*" || token  == "+" ||
			token == "-" || token == "/");
}

bool RPN::isNumber(std::string const& token) {
	if (token.empty())
		return false;
	if (token.length() == 1 && isdigit(token[0]))
		return true;
	return false;
}

int RPN::calculate(int a, int b, char op) {
	switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("error: division by zero");
			return a / b;
		default:
			throw std::runtime_error("error: unknown operator");
	}
}

int RPN::evaluate(std::string const& expression) {
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token) {
		if (isNumber(token)) {
			int num = atoi(token.c_str());
			_stack.push(num);
		}
		else if (isOperator(token)) {
			if (_stack.size() < 2)
				throw std::runtime_error("error: insufficent operands");

			int b = _stack.top();
			_stack.pop();

			int a = _stack.top();
			_stack.pop();

			_stack.push(calculate(a, b, token[0]));
		}
		else {
			throw std::runtime_error("error: invalid token") ;
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("error: invalid syntax");
	return _stack.top();
}
