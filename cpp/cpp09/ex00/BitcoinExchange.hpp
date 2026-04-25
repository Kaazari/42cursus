#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

class BitcoinExchange {
private:
	std::map<std::string, float> _database;

	std::string trim(std::string const& str);
	float getPrice(std::string const& date);

public:
	BitcoinExchange();
	~BitcoinExchange();

	void loadDatabase(std::string const& filename);
	void processInput(std::string const& filename);
};

#endif
