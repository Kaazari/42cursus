#include "BankAccount.hpp"
#include <iostream>

int main() {

	BankAccount b("Mr.Wayne");

	b.deposit(19000);
	std::cout << "Withdraw possible: " << b.withdraw(20000) << std::endl;
	std::cout << "Owner: " << b.getOwner() << "\nBalance: " << b.getBalance() << std::endl;
	std::cout << "Withdraw possible: " << b.withdraw(5000) << std::endl;
	std::cout << "Owner: " << b.getOwner() << "\nBalance: " << b.getBalance() << std::endl;

	return 0;
}
