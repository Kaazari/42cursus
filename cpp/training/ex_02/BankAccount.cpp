#include "BankAccount.hpp"
#include <iostream>

BankAccount::BankAccount(std::string owner) {
	_owner = owner;
	_balance = 0;
	std::cout << "Account created!" << std::endl;
}

BankAccount::~BankAccount() {
	std::cout << "Account destroyed." << std::endl;
}

void BankAccount::deposit(int amount) {
	if (amount > 0)
		_balance += amount;
}

bool BankAccount::withdraw(int amount) {
	if (_balance >= amount)
	{
		_balance -= amount;
		return (true);
	}
	return (false);
}

int BankAccount::getBalance() const {
	return (_balance);
}

std::string BankAccount::getOwner() const {
	return (_owner);
}
