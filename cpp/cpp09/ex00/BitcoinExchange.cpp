#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& other) {
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(std::string const& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValidDate(std::string const& date) {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.size(); ++i) {
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (year < 0)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	return true;
}

bool BitcoinExchange::parseValue(std::string const& str, float& out) {
	if (str.empty())
		return false;

	char* end = 0;
	double value = std::strtod(str.c_str(), &end);

	if (*end != '\0')
		return false;
	if (value != value)
		return false;

	out = static_cast<float>(value);
	return true;
}

void BitcoinExchange::loadDatabase(std::string const& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = line.substr(0, comma);
		std::string priceStr = line.substr(comma + 1);

		float price = static_cast<float>(std::atof(priceStr.c_str()));
		_database[date] = price;
	}

	file.close();
}

void BitcoinExchange::processInput(std::string const& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

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

		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		float quantity;
		if (!parseValue(valueStr, quantity)) {
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}

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
	std::map<std::string, float>::iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
		return it->second;

	if (it == _database.begin())
		throw std::runtime_error("Error: date too early");

	--it;
	return it->second;
}
