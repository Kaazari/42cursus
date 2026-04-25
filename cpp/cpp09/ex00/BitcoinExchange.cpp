#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::~BitcoinExchange() {};

std::string BitcoinExchange::trim(std::string const& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, (last - first + 1));
}

void BitcoinExchange::loadDatabase(std::string const& filename) {
	std::ifstream file(filename.c_str());
	std::string line;

	std::getline(file, line);

	while (std::getline(file, line)) {
		size_t comma = line.find(',');

		std::string date = line.substr(0, comma);
		std::string priceStr = line.substr(comma + 1);

		float price = atof(priceStr.c_str());

		_database[date] = price;
	}

	file.close();
}

void BitcoinExchange::processInput(std::string const& filename) {
	std::ifstream file(filename.c_str());
	std::string line;

	std::getline(file, line);

	while (std::getline(file, line)) {
		size_t pipe = line.find('|');

		if (pipe == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipe));
		std::string valueStr = trim(line.substr(pipe + 1));

		float quantity = atof(valueStr.c_str());

		if (quantity < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}

		if (quantity > 1000) {
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		try {
			float price = getPrice(date);
			float result = quantity * price;
			std::cout << date << " => " << quantity << " = " << result << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Error: bad input => " << date << std::endl;
		}
	}

	file.close();
}

float BitcoinExchange::getPrice(std::string const& date) {
	std::map<std::string, float>::iterator it = _database.find(date);

	if (it != _database.end()) {
		return it->second;
	}

	it = _database.lower_bound(date);

	if (it == _database.begin()) {
		throw std::runtime_error("Error: date too early");
	}
	--it;
	return it->second;
}
