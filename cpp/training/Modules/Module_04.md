# MODULE CPP04 : Polymorphism & Abstract Classes

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre le polymorphisme
- ✅ Utiliser `virtual` correctement
- ✅ Créer des classes abstraites
- ✅ Implémenter des interfaces (pure abstract classes)
- ✅ Gérer le deep copy avec pointeurs

**Durée estimée : 9-10 heures**

**⚠️ C'est le MODULE LE PLUS LONG et LE PLUS COMPLEXE ! Mais c'est le BOSS FINAL ! 🔥**

---

## 📖 1. Le Polymorphisme - C'est Quoi ?

### Problème Sans Polymorphisme

```cpp
class Animal {
public:
    void makeSound() {
        std::cout << "Some generic animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() {
        std::cout << "Woof!" << std::endl;
    }
};

// Utilisation
Dog dog;
Animal *ptr = &dog;  // Pointeur Animal vers un Dog

ptr->makeSound();  // ❌ Affiche "Some generic animal sound"
                   // Au lieu de "Woof!"
```

**Problème :** Le compilateur appelle la méthode de `Animal`, pas celle de `Dog` !

---

### Solution : `virtual`

```cpp
class Animal {
public:
    virtual void makeSound() {  // ← virtual !
        std::cout << "Some generic animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() {  // Override automatique
        std::cout << "Woof!" << std::endl;
    }
};

// Utilisation
Dog dog;
Animal *ptr = &dog;

ptr->makeSound();  // ✅ Affiche "Woof!"
```

**`virtual` permet au programme de choisir la bonne méthode à l'exécution !**

---

### Destructeur Virtual (CRITIQUE)

**❌ Sans virtual :**
```cpp
class Animal {
public:
    ~Animal() { std::cout << "Animal destroyed" << std::endl; }
};

class Dog : public Animal {
private:
    int *data;
public:
    Dog() { data = new int[100]; }
    ~Dog() {
        delete[] data;
        std::cout << "Dog destroyed" << std::endl;
    }
};

// Problème
Animal *ptr = new Dog();
delete ptr;  // ❌ Appelle SEULEMENT ~Animal() → LEAK !
```

**✅ Avec virtual :**
```cpp
class Animal {
public:
    virtual ~Animal() { std::cout << "Animal destroyed" << std::endl; }
};

// Maintenant
delete ptr;  // ✅ Appelle ~Dog() puis ~Animal()
```

**RÈGLE D'OR : Si une classe a des méthodes virtual, le destructeur DOIT être virtual !**

---

## 🎭 2. Classes Abstraites & Interfaces

### Classe Abstraite

**Une classe avec au moins une méthode `pure virtual` (= 0) :**

```cpp
class Animal {
public:
    virtual void makeSound() = 0;  // ← Pure virtual
    //                       ^^^
    //                       = 0 signifie "pas d'implémentation"
};
```

**Conséquence : Tu NE PEUX PAS instancier Animal !**

```cpp
Animal animal;  // ❌ ERREUR : Animal est abstraite
Dog dog;        // ✅ OK si Dog implémente makeSound()
```

---

### Interface (Pure Abstract Class)

**Une classe avec TOUTES les méthodes pure virtual :**

```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**C'est l'équivalent des `interface` en Java/C# !**

---

## 📝 3. Les Exercices du Sujet - Guides Complets

### Ex00 : Polymorphism (Animal/Dog/Cat)

#### 📋 Consignes du Sujet

Créer une hiérarchie de classes pour comprendre le polymorphisme.

**Classe Animal (classe de base) :**

**Attribut protégé :**
- `std::string _type`

**Méthodes publiques :**
- `Animal()` - Constructeur par défaut
- `Animal(const Animal& other)` - Copy constructor
- `Animal& operator=(const Animal& other)` - Copy assignment
- `virtual ~Animal()` - Destructeur virtuel **OBLIGATOIRE**
- `virtual void makeSound() const` - Méthode virtuelle
- `std::string getType() const` - Retourne le type

**Classes dérivées à créer :**
- `Dog` (hérite de Animal, _type = "Dog", makeSound = "Woof!")
- `Cat` (hérite de Animal, _type = "Cat", makeSound = "Meow!")

**Classes supplémentaires (pour tester le non-polymorphisme) :**
- `WrongAnimal` (sans virtual)
- `WrongCat` (hérite de WrongAnimal)

**Test obligatoire :**
```cpp
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

j->makeSound(); // Doit afficher "Woof!"
i->makeSound(); // Doit afficher "Meow!"
meta->makeSound(); // Affiche le son de Animal

delete j;
delete i;
delete meta;
```

**⚠️ Sans `virtual`, le polymorphisme ne marche pas !**

#### 📁 Fichiers à Créer

```
ex00/
├── Animal.hpp
├── Animal.cpp
├── Dog.hpp
├── Dog.cpp
├── Cat.hpp
├── Cat.cpp
├── WrongAnimal.hpp
├── WrongAnimal.cpp
├── WrongCat.hpp
├── WrongCat.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Destructeur Animal est virtuel
- [ ] makeSound() est virtuel
- [ ] Dog/Cat redéfinissent makeSound()
- [ ] Polymorphisme fonctionne (appelle la bonne version)
- [ ] WrongAnimal démontre le problème sans virtual
- [ ] Pas de leaks mémoire

**Objectif :** Comprendre `virtual` et polymorphisme de base.

---

#### Animal.hpp

```cpp
#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal {
protected:
    std::string _type;

public:
    Animal();
    Animal(std::string type);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();  // ← virtual IMPORTANT !

    virtual void makeSound() const;  // ← virtual
    std::string getType() const;
};

#endif
```

---

#### Animal.cpp

```cpp
#include "Animal.hpp"
#include <iostream>

Animal::Animal() : _type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type) : _type(type) {
    std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal& other) : _type(other._type) {
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other)
        _type = other._type;
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Some generic animal sound" << std::endl;
}

std::string Animal::getType() const {
    return _type;
}
```

---

#### Dog.hpp

```cpp
#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal {
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();

    void makeSound() const;  // Override
};

#endif
```

---

#### Dog.cpp

```cpp
#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other)
        Animal::operator=(other);
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}
```

---

#### Cat.hpp & Cat.cpp

**Exactement pareil que Dog, mais avec "Meow!" au lieu de "Woof!" !**

---

#### WrongAnimal & WrongCat (Partie 2 de Ex00)

**Le sujet demande de créer WrongAnimal/WrongCat SANS `virtual` pour montrer la différence !**

**WrongAnimal.hpp :**
```cpp
class WrongAnimal {
protected:
    std::string _type;

public:
    WrongAnimal();
    ~WrongAnimal();

    void makeSound() const;  // ← PAS virtual !
    std::string getType() const;
};
```

**Test pour montrer la différence :**
```cpp
const Animal* dog = new Dog();
const WrongAnimal* wrongCat = new WrongCat();

dog->makeSound();       // ✅ "Woof!" (polymorphisme)
wrongCat->makeSound();  // ❌ "WrongAnimal sound" (pas de polymorphisme)
```

---

### Ex01 : I don't want to set the world on fire (Brain)

#### 📋 Consignes du Sujet

Ajouter un attribut privé alloué dynamiquement aux classes Dog et Cat.

**Créer une classe Brain :**

**Attributs :**
- `std::string _ideas[100]` - Tableau de 100 idées

**Méthodes :**
- `Brain()` - Constructeur
- `Brain(const Brain& other)` - Copy constructor (copie profonde !)
- `Brain& operator=(const Brain& other)` - Copy assignment (copie profonde !)
- `~Brain()` - Destructeur

**Modifier Dog et Cat :**

**Ajouter attribut privé :**
- `Brain* _brain` - Alloué dynamiquement dans le constructeur

**Méthodes Dog/Cat à adapter :**
- Constructeur : `_brain = new Brain()`
- Copy constructor : `_brain = new Brain(*other._brain)` (copie profonde !)
- Copy assignment : gérer la copie profonde
- Destructeur : `delete _brain`

**Test obligatoire :**
```cpp
Dog basic;
{
    Dog tmp = basic; // Copy constructor
}
// tmp détruit ici, mais basic doit rester valide !
```

**Problème à résoudre : Copie superficielle vs copie profonde**

#### 📁 Fichiers à Créer

```
ex01/
├── Animal.hpp
├── Animal.cpp
├── Dog.hpp
├── Dog.cpp
├── Cat.hpp
├── Cat.cpp
├── Brain.hpp
├── Brain.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Classe Brain avec tableau de 100 strings
- [ ] Dog et Cat ont un Brain* en privé
- [ ] Allocation dynamique dans constructeur (new)
- [ ] Libération dans destructeur (delete)
- [ ] Copy constructor fait une copie profonde
- [ ] Copy assignment fait une copie profonde
- [ ] Pas de double free
- [ ] Pas de leaks mémoire

**Objectif :** Comprendre copie profonde vs superficielle.

---**Objectif :** Deep copy avec pointeurs.

**⚠️ C'est l'exercice LE PLUS IMPORTANT du module pour comprendre la mémoire !**

---

#### Brain.hpp

```cpp
#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

class Brain {
private:
    std::string _ideas[100];

public:
    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();

    void setIdea(int index, std::string idea);
    std::string getIdea(int index) const;
};

#endif
```

---

#### Brain.cpp

```cpp
#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
    std::cout << "Brain copy constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        _ideas[i] = other._ideas[i];  // Deep copy
}

Brain& Brain::operator=(const Brain& other) {
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < 100; i++)
            _ideas[i] = other._ideas[i];  // Deep copy
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, std::string idea) {
    if (index >= 0 && index < 100)
        _ideas[index] = idea;
}

std::string Brain::getIdea(int index) const {
    if (index >= 0 && index < 100)
        return _ideas[index];
    return "";
}
```

---

#### Dog Modifié (avec Brain)

**Dog.hpp :**
```cpp
#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {
private:
    Brain* _brain;  // ← Pointeur vers Brain

public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();

    void makeSound() const;
    Brain* getBrain() const;
};

#endif
```

---

#### Dog.cpp (Deep Copy)

```cpp
#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
    std::cout << "Dog constructor called" << std::endl;
    _brain = new Brain();  // ← Alloue Brain
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    _brain = new Brain(*other._brain);  // ← DEEP COPY !
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;                    // ← Libère l'ancien Brain
        _brain = new Brain(*other._brain); // ← DEEP COPY !
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete _brain;  // ← Libère Brain
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain() const {
    return _brain;
}
```

---

#### Shallow vs Deep Copy

**❌ Shallow Copy (MAUVAIS) :**
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    _brain = other._brain;  // ❌ Copie juste le pointeur !
}
// Maintenant les 2 Dogs pointent vers le MÊME Brain !
// → Double free au delete !
```

**✅ Deep Copy (BON) :**
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    _brain = new Brain(*other._brain);  // ✅ Crée un NOUVEAU Brain
}
// Chaque Dog a son propre Brain
```

---

#### Test de Deep Copy

```cpp
int main() {
    Dog dog1;
    dog1.getBrain()->setIdea(0, "I love bones");

    Dog dog2(dog1);  // Copy constructor

    std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;

    // Modifier dog2
    dog2.getBrain()->setIdea(0, "I love cats");

    std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;

    // ✅ Les ideas sont différentes = deep copy réussi !

    return 0;
}
```

---

#### Array de Animals

**Le sujet demande de créer un array d'Animals (moitié Dog, moitié Cat) :**

```cpp
int main() {
    const Animal* animals[10];

    // Moitié Dogs
    for (int i = 0; i < 5; i++)
        animals[i] = new Dog();

    // Moitié Cats
    for (int i = 5; i < 10; i++)
        animals[i] = new Cat();

    // Utiliser les animals
    for (int i = 0; i < 10; i++)
        animals[i]->makeSound();

    // ⚠️ IMPORTANT : Delete en tant qu'Animal
    for (int i = 0; i < 10; i++)
        delete animals[i];  // Destructeur virtual ESSENTIEL !

    return 0;
}
```

**⚠️ Si le destructeur de Animal n'est PAS virtual → LEAK des Brain !**

---

### Ex02 : Abstract class

#### 📋 Consignes du Sujet

Rendre la classe Animal non-instanciable en la transformant en classe abstraite.

**Modifier la classe Animal :**

**Renommer en AAnimal (optionnel mais recommandé) :**
```cpp
class AAnimal {
    // ...
public:
    virtual void makeSound() const = 0;  // ← Méthode pure virtuelle
    //                               ^^^
};
```

**Effet : Animal/AAnimal ne peut plus être instancié !**
```cpp
Animal a;  // ❌ Erreur : classe abstraite
Dog d;     // ✅ OK : classe concrète
```

**Dog et Cat doivent implémenter makeSound() !**

**Ce qui change :**
- Animal devient AAnimal (ou garde le nom Animal)
- `makeSound()` devient pure virtuelle (`= 0`)
- Impossible de faire `new Animal()`
- Dog et Cat DOIVENT implémenter makeSound()

**Test à faire :**
```cpp
// const Animal* a = new Animal();  // ❌ Ne compile pas !
const Animal* d = new Dog();        // ✅ OK
const Animal* c = new Cat();        // ✅ OK
```

#### 📁 Fichiers à Créer

```
ex02/
├── AAnimal.hpp (ou Animal.hpp)
├── AAnimal.cpp (ou Animal.cpp)
├── Dog.hpp
├── Dog.cpp
├── Cat.hpp
├── Cat.cpp
├── Brain.hpp
├── Brain.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Animal est une classe abstraite (méthode pure virtuelle)
- [ ] Impossible d'instancier Animal directement
- [ ] Dog et Cat restent instanciables
- [ ] makeSound() implémentée dans Dog et Cat
- [ ] Polymorphisme fonctionne toujours
- [ ] Brain toujours présent et fonctionnel

**Objectif :** Comprendre les classes abstraites et méthodes pures virtuelles.

**C'est TRÈS SIMPLE : rendre une méthode pure virtual !**

---

#### AAnimal.hpp (ou Animal.hpp modifié)

```cpp
class AAnimal {  // A pour Abstract (optionnel)
protected:
    std::string _type;

public:
    AAnimal();
    AAnimal(std::string type);
    virtual ~AAnimal();

    virtual void makeSound() const = 0;  // ← = 0 !
    //                               ^^^
    std::string getType() const;
};
```

**Maintenant :**
```cpp
AAnimal animal;  // ❌ ERREUR : cannot instantiate abstract class
Dog dog;         // ✅ OK car Dog implémente makeSound()
```

**C'est tout ! Ex02 terminé ! 😄**

---

### Ex03 : Interface & recap (Materia)

#### 📋 Consignes du Sujet

Créer un système complexe avec interfaces et gestion mémoire avancée.

**Classes à créer :**

**1. AMateria (classe abstraite) :**
- Attribut : `std::string _type`
- Méthodes : `clone()` (pure virtuelle), `use(ICharacter& target)`

**2. Ice et Cure (héritent de AMateria) :**
- Implémentent `clone()` et `use()`
- Ice affiche : "* shoots an ice bolt at <target> *"
- Cure affiche : "* heals <target>'s wounds *"

**3. ICharacter (interface pure) :**
- Toutes les méthodes sont pures virtuelles
- `getName()`, `equip(AMateria*)`, `unequip(int)`, `use(int, ICharacter&)`

**4. Character (implémente ICharacter) :**
- Inventaire de 4 Materias max
- Gère l'équipement/déséquipement
- Ne doit PAS delete les Materias unequip !

**5. IMateriaSource (interface pure) :**
- `learnMateria(AMateria*)`, `createMateria(std::string const&)`

**6. MateriaSource (implémente IMateriaSource) :**
- Peut apprendre 4 Materias
- Crée des copies des Materias apprises

**Règles importantes :**
- unequip() ne doit PAS delete la Materia
- Le code appelant doit gérer la mémoire des Materias unequip
- Toutes les Materias doivent être delete avant la fin du programme

**⚠️ Gestion mémoire CRITIQUE : leaks interdits !**

#### 📁 Fichiers à Créer

```
ex03/
├── AMateria.hpp
├── AMateria.cpp
├── Ice.hpp
├── Ice.cpp
├── Cure.hpp
├── Cure.cpp
├── ICharacter.hpp
├── Character.hpp
├── Character.cpp
├── IMateriaSource.hpp
├── MateriaSource.hpp
├── MateriaSource.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] AMateria est abstraite
- [ ] Ice et Cure fonctionnent
- [ ] ICharacter est une interface pure
- [ ] Character gère 4 Materias max
- [ ] unequip() ne delete PAS
- [ ] IMateriaSource est une interface pure
- [ ] MateriaSource apprend et clone les Materias
- [ ] AUCUN leak mémoire
- [ ] Tests du sujet passent

**⚠️ C'est l'exercice LE PLUS GROS du module (et de tous les CPP) !**

---

#### Vue d'Ensemble

**Classes à créer :**
1. `AMateria` (abstract)
2. `Ice` (dérivée de AMateria)
3. `Cure` (dérivée de AMateria)
4. `ICharacter` (interface)
5. `Character` (implémente ICharacter)
6. `IMateriaSource` (interface)
7. `MateriaSource` (implémente IMateriaSource)

---

#### AMateria.hpp

```cpp
#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>

class ICharacter;  // Forward declaration

class AMateria {
protected:
    std::string _type;

public:
    AMateria(std::string const& type);
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    virtual ~AMateria();

    std::string const& getType() const;

    virtual AMateria* clone() const = 0;  // Pure virtual
    virtual void use(ICharacter& target);
};

#endif
```

---

#### AMateria.cpp

```cpp
#include "AMateria.hpp"

AMateria::AMateria(std::string const& type) : _type(type) {}

AMateria::AMateria(const AMateria& other) : _type(other._type) {}

AMateria& AMateria::operator=(const AMateria& other) {
    // ⚠️ Le sujet dit : "copying the type doesn't make sense"
    // Donc on ne copie PAS le type !
    (void)other;
    return *this;
}

AMateria::~AMateria() {}

std::string const& AMateria::getType() const {
    return _type;
}

void AMateria::use(ICharacter& target) {
    (void)target;
    // Implémentation par défaut (vide)
}
```

---

#### Ice.hpp

```cpp
#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"

class Ice : public AMateria {
public:
    Ice();
    Ice(const Ice& other);
    Ice& operator=(const Ice& other);
    ~Ice();

    AMateria* clone() const;
    void use(ICharacter& target);
};

#endif
```

---

#### Ice.cpp

```cpp
#include "Ice.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& other) : AMateria(other) {}

Ice& Ice::operator=(const Ice& other) {
    AMateria::operator=(other);
    return *this;
}

Ice::~Ice() {}

AMateria* Ice::clone() const {
    return new Ice(*this);  // Retourne une COPIE
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *"
              << std::endl;
}
```

---

#### Cure.hpp & Cure.cpp

**Exactement pareil que Ice, mais :**
- Type : `"cure"`
- Message : `"* heals <name>'s wounds *"`

---

#### ICharacter.hpp (Interface)

```cpp
#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>

class AMateria;  // Forward declaration

class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};

#endif
```

---

#### Character.hpp

```cpp
#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character : public ICharacter {
private:
    std::string _name;
    AMateria*   _inventory[4];  // Max 4 Materias

public:
    Character(std::string const& name);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();

    std::string const& getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};

#endif
```

---

#### Character.cpp

```cpp
#include "Character.hpp"
#include <iostream>

Character::Character(std::string const& name) : _name(name) {
    for (int i = 0; i < 4; i++)
        _inventory[i] = NULL;
}

Character::Character(const Character& other) : _name(other._name) {
    for (int i = 0; i < 4; i++) {
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();  // Deep copy
        else
            _inventory[i] = NULL;
    }
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        _name = other._name;

        // Delete old inventory
        for (int i = 0; i < 4; i++) {
            if (_inventory[i])
                delete _inventory[i];
        }

        // Deep copy new inventory
        for (int i = 0; i < 4; i++) {
            if (other._inventory[i])
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = NULL;
        }
    }
    return *this;
}

Character::~Character() {
    for (int i = 0; i < 4; i++) {
        if (_inventory[i])
            delete _inventory[i];
    }
}

std::string const& Character::getName() const {
    return _name;
}

void Character::equip(AMateria* m) {
    if (!m)
        return;

    for (int i = 0; i < 4; i++) {
        if (!_inventory[i]) {
            _inventory[i] = m;
            return;
        }
    }
    // Inventaire plein : ne fait rien
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4 && _inventory[idx]) {
        _inventory[idx] = NULL;  // ⚠️ Ne delete PAS !
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && _inventory[idx]) {
        _inventory[idx]->use(target);
    }
}
```

**⚠️ `unequip()` ne delete PAS la Materia ! C'est au programmeur de la gérer !**

---

#### IMateriaSource.hpp & MateriaSource

**Pareil que Character mais pour stocker des "templates" de Materias !**

---

#### Test du Sujet

```cpp
int main() {
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    return 0;
}
```

**Output attendu :**
```
* shoots an ice bolt at bob *
* heals bob's wounds *
```

---

## ✅ 4. Validation du Module CPP04

**Pour valider ce module, tu dois :**

1. ✅ Ex00 : Polymorphisme avec Animal/Dog/Cat
2. ✅ Ex01 : Deep copy avec Brain
3. ✅ Ex02 : Classe abstraite
4. ⭕ Ex03 : Interface & Materia (optionnel mais ÉNORME XP)

---

## 🎯 Checklist Finale

- [ ] Ex00 : virtual fonctionne (Dog fait Woof, Cat fait Meow)
- [ ] Ex00 : WrongAnimal montre la différence sans virtual
- [ ] Ex01 : Deep copy fonctionne (Brain copié, pas partagé)
- [ ] Ex01 : Destructeur virtual (pas de leak)
- [ ] Ex02 : Animal non-instanciable (pure virtual)
- [ ] Ex03 : Toutes les classes compilent et fonctionnent
- [ ] Pas de memory leaks (valgrind)

---

## ⚠️ Pièges Classiques

**1. Oublier virtual sur le destructeur :**
```cpp
class Animal {
public:
    virtual ~Animal() {}  // ← ESSENTIEL !
};
```

**2. Shallow copy au lieu de deep copy :**
```cpp
// ❌ Shallow
_brain = other._brain;

// ✅ Deep
_brain = new Brain(*other._brain);
```

**3. unequip() qui delete :**
```cpp
void unequip(int idx) {
    _inventory[idx] = NULL;  // ✅ Juste mettre à NULL
    // delete _inventory[idx];  ❌ NE PAS DELETE !
}
```

---

## 🎉 FÉLICITATIONS !

**Si tu as fini CPP04, tu as terminé les 5 modules de base !**

**Tu maîtrises maintenant :**
- ✅ Classes et objets (CPP00)
- ✅ Gestion mémoire (CPP01)
- ✅ Opérateurs et OCF (CPP02)
- ✅ Héritage (CPP03)
- ✅ Polymorphisme et interfaces (CPP04)

**Tu es prêt pour les modules avancés (CPP05-09) ou pour l'exam ! 🚀**

---

*Module optimisé projet-only pour un étudiant 42 pressé par le temps.*
*CPP04 est long mais c'est le BOSS FINAL. GG ! 🏆*
