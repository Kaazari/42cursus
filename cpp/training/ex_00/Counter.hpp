#ifndef COUNTER_HPP
# define COUNTER_HPP

class Counter {
private:
	int _value;

public:
	Counter();				// Constructeur par défaut
	~Counter();				// Destructeur

	void increment();		// Augmente de 1
	void decrement();		// Diminue de 1
	int  getValue() const;	// Retourne la valeur
};

#endif
