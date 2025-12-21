#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

class Harl {
private:
	void debug();
	void info();
	void warning();
	void error();

public:
	typedef void (Harl::*Functions)();
	void complain(std::string level);
};

#endif
