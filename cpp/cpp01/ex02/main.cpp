#include <iostream>
#include <string>

int main() {
	std::string str = "HI THIS IS BRAIN";

	std::string *stringPTR = &str;
	std::string& stringREF = str;

	std::cout << "Address of str:	" << &str << std::endl;
	std::cout << "Address in PTR:	" << stringPTR << std::endl;
	std::cout << "Address of REF:	" << &stringREF << std::endl;

	std::cout << std::endl;

	std::cout << "Value of str:	  " << str << std::endl;
	std::cout << "Value via PTR:	 " << *stringPTR << std::endl;
	std::cout << "Value via REF:	 " << stringREF << std::endl;

	return 0;
}
