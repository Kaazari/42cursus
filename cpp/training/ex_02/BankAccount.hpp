#ifndef BANKACCOUNT_HPP
# define BANKACCOUNT_HPP

# include <string>

class BankAccount {
private:
    std::string _owner;
    int         _balance;

public:
    BankAccount(std::string owner);
    ~BankAccount();

    void deposit(int amount);           // Ajoute de l'argent
    bool withdraw(int amount);          // Retire si possible (retourne true/false)
    int  getBalance() const;
    std::string getOwner() const;
};

#endif
