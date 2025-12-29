#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal {
protected:
	std::string _type;

public:
	AAnimal();
	AAnimal(std::string _type);
	AAnimal(const AAnimal& other);
	AAnimal& operator=(const AAnimal& other);
	virtual ~AAnimal();

	virtual void makeSound() const = 0; // Pure virtual function
	std::string getType() const;
};

#endif
