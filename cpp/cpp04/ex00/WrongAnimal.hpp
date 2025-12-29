#ifndef WRONG_ANIMAL_HPP
# define WRONG_ANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal {
protected:
	std::string _type;

public:
	WrongAnimal();
	WrongAnimal(std::string _type);
	WrongAnimal(const WrongAnimal& other);
	WrongAnimal& operator=(const WrongAnimal& other);
	~WrongAnimal();

	void makeSound() const;
	std::string getType() const;
};

#endif
