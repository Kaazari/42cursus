#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>

class BitcoinExchange {
private:
	std::map<std::string, float> _database;

	std::string trim(std::string const& str);
	bool		isValidDate(std::string const& date);
	bool		parseValue(std::string const& str, float& out);
	float		getPrice(std::string const& date);

public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const& other);
	BitcoinExchange& operator=(BitcoinExchange const& other);
	~BitcoinExchange();

	void loadDatabase(std::string const& filename);
	void processInput(std::string const& filename);
};

#endif
