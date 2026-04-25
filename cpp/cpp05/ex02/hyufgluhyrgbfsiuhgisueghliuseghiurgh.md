# 🔥 CPP00-04 - RAPPEL RAPIDE

## 📋 Vue d'ensemble

| Module | Concept principal |
|--------|------------------|
| **CPP00** | Basics C++, classes, namespace, stdio streams |
| **CPP01** | Memory allocation, pointers vs references |
| **CPP02** | Operator overloading, Orthodox Canonical Form |
| **CPP03** | Inheritance |
| **CPP04** | Polymorphism, abstract classes, interfaces |

---

## 🎯 CPP00-01: BASES

### Namespace & class basics
```cpp
// Namespace
namespace Awesome {
    void func() { std::cout << "Hello" << std::endl; }
}

// Usage
Awesome::func();
```

### Class de base
```cpp
class Student {
private:
    std::string _name;  // Convention: underscore pour private
    int _grade;

public:
    // Constructor
    Student(std::string name, int grade);

    // Destructor
    ~Student();

    // Getters (const!)
    std::string getName() const { return _name; }
    int getGrade() const { return _grade; }

    // Setters
    void setGrade(int grade) { _grade = grade; }
};

// Implementation
Student::Student(std::string name, int grade) : _name(name), _grade(grade) {
    std::cout << "Constructor called" << std::endl;
}

Student::~Student() {
    std::cout << "Destructor called" << std::endl;
}
```

### Pointers vs References
```cpp
// POINTER (peut être NULL)
int* ptr = &x;
*ptr = 42;  // Dereference
ptr = NULL; // OK

// REFERENCE (ne peut PAS être NULL, alias permanent)
int& ref = x;
ref = 42;   // Direct access, no dereference
// ref = y; // IMPOSSIBLE, ref is bound to x forever
```

### new/delete
```cpp
// Single object
Student* student = new Student("Alice", 42);
delete student;

// Array
int* array = new int[10];
delete[] array;  // IMPORTANT: [] pour array!
```

---

## 🎯 CPP02: ORTHODOX CANONICAL FORM

### La forme canonique (TOUJOURS)
```cpp
class Fixed {
private:
    int _value;
    static const int _fractionalBits = 8;

public:
    // 1. Default constructor
    Fixed();

    // 2. Copy constructor
    Fixed(const Fixed& other);

    // 3. Copy assignment operator
    Fixed& operator=(const Fixed& other);

    // 4. Destructor
    ~Fixed();

    // Autres...
};
```

### Implementation
```cpp
// 1. Default constructor
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

// 2. Copy constructor
Fixed::Fixed(const Fixed& other) : _value(other._value) {
    std::cout << "Copy constructor called" << std::endl;
}

// 3. Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {  // Self-assignment check
        _value = other._value;
    }
    return *this;
}

// 4. Destructor
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
```

### Operator overloading - syntaxe
```cpp
class Fixed {
public:
    // Arithmetic operators
    Fixed operator+(const Fixed& other) const;
    Fixed operator-(const Fixed& other) const;
    Fixed operator*(const Fixed& other) const;
    Fixed operator/(const Fixed& other) const;

    // Comparison operators
    bool operator>(const Fixed& other) const;
    bool operator<(const Fixed& other) const;
    bool operator>=(const Fixed& other) const;
    bool operator<=(const Fixed& other) const;
    bool operator==(const Fixed& other) const;
    bool operator!=(const Fixed& other) const;

    // Increment/Decrement
    Fixed& operator++();      // Prefix: ++a
    Fixed operator++(int);    // Postfix: a++
    Fixed& operator--();      // Prefix: --a
    Fixed operator--(int);    // Postfix: a--
};

// Implementation examples
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result._value = this->_value + other._value;
    return result;
}

bool Fixed::operator>(const Fixed& other) const {
    return this->_value > other._value;
}

// Prefix increment
Fixed& Fixed::operator++() {
    _value++;
    return *this;
}

// Postfix increment (int est un dummy parameter)
Fixed Fixed::operator++(int) {
    Fixed temp(*this);  // Save current state
    _value++;
    return temp;        // Return old value
}
```

### Stream operators (outside class)
```cpp
// Dans le .hpp (outside class)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

// Dans le .cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}

// Usage
Fixed a(42.42f);
std::cout << a << std::endl;
```

---

## 🎯 CPP03: INHERITANCE

### Syntaxe de base
```cpp
// Base class
class Animal {
protected:  // Accessible par classes dérivées
    std::string _type;

public:
    Animal();
    Animal(std::string type);
    ~Animal();

    std::string getType() const { return _type; }
};

// Derived class
class Dog : public Animal {  // public inheritance
private:
    std::string _name;

public:
    Dog();
    Dog(std::string name);
    ~Dog();

    void bark() const { std::cout << "Woof!" << std::endl; }
};
```

### Constructors/Destructors order
```cpp
Dog::Dog(std::string name) : Animal("Dog"), _name(name) {
    //                        ^^^^^^^^^^ Appel constructeur parent AVANT
    std::cout << "Dog constructor" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog destructor" << std::endl;
    // Destructeur parent appelé APRÈS automatiquement
}
```

**Ordre d'exécution:**
```
Construction:
1. Animal constructor
2. Dog constructor

Destruction:
1. Dog destructor
2. Animal destructor  (automatique)
```

### Public vs Protected vs Private
```cpp
class Base {
public:
    int pub;      // Accessible partout
protected:
    int prot;     // Accessible: Base + classes dérivées
private:
    int priv;     // Accessible: Base seulement
};

class Derived : public Base {
    void func() {
        pub = 1;   // ✅ OK
        prot = 2;  // ✅ OK
        priv = 3;  // ❌ ERROR
    }
};
```

---

## 🎯 CPP04: POLYMORPHISM (le plus important)

### Virtual functions - SYNTAXE COMPLÈTE

```cpp
// ====== CLASSE DE BASE ======
class Animal {
protected:
    std::string _type;

public:
    // Constructor
    Animal();
    Animal(std::string type);

    // Destructor DOIT être virtual si polymorphisme!
    virtual ~Animal();

    // Virtual function (peut être overridée)
    virtual void makeSound() const;

    // Non-virtual (ne peut PAS être overridée correctement)
    void sleep() const;

    // Pure virtual = abstract (DOIT être overridée)
    virtual void eat() const = 0;

    // Getter
    std::string getType() const { return _type; }
};

// ====== CLASSE DÉRIVÉE ======
class Dog : public Animal {
public:
    Dog();
    virtual ~Dog();  // virtual optionnel mais recommandé

    // Override virtual function
    virtual void makeSound() const;  // virtual optionnel en dérivée

    // Override pure virtual (obligation)
    virtual void eat() const;
};
```

### Implementation
```cpp
// Animal.cpp
Animal::Animal() : _type("Animal") {
    std::cout << "Animal constructor" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destructor" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Some generic sound" << std::endl;
}

void Animal::sleep() const {
    std::cout << "Zzz..." << std::endl;
}

// Dog.cpp
Dog::Dog() : Animal("Dog") {
    std::cout << "Dog constructor" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog destructor" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}

void Dog::eat() const {
    std::cout << "Dog eats kibble" << std::endl;
}
```

### Usage polymorphique
```cpp
int main() {
    // Polymorphisme via pointeurs
    Animal* animal = new Dog();

    animal->makeSound();  // "Woof! Woof!" (virtual, appelle Dog::makeSound)
    animal->sleep();      // "Zzz..." (non-virtual, appelle Animal::sleep)
    animal->eat();        // "Dog eats kibble" (pure virtual overridée)

    delete animal;        // Appelle Dog::~Dog() puis Animal::~Animal()
                          // (grâce à virtual ~Animal())

    return 0;
}
```

### Abstract class (interface)
```cpp
// Classe abstraite = au moins 1 fonction pure virtual
class AAnimal {  // Convention: A prefix pour abstract
public:
    virtual ~AAnimal() {}

    // Pure virtual functions
    virtual void makeSound() const = 0;
    virtual void eat() const = 0;

    // On ne peut PAS faire:
    // AAnimal animal;  // ERROR: cannot instantiate abstract class
};

// Classe concrète
class Cat : public AAnimal {
public:
    // DOIT override toutes les pure virtual
    virtual void makeSound() const { std::cout << "Meow!" << std::endl; }
    virtual void eat() const { std::cout << "Cat eats fish" << std::endl; }
};
```

---

## 🔥 ORDRE DES NOTATIONS - SYNTAXE FONCTION

### Dans la classe (.hpp)
```cpp
class MyClass {
public:
    // Ordre: virtual | type | nom | (params) | const
    virtual void myFunction(int param) const;

    // Pure virtual
    virtual void pureVirtual() const = 0;

    // Non-virtual const
    int getValue() const;

    // Non-virtual non-const
    void setValue(int val);

    // Static
    static void staticFunc();
};
```

### Dans l'implémentation (.cpp)
```cpp
// PAS de virtual dans .cpp!
// Ordre: type | MyClass:: | nom | (params) | const

void MyClass::myFunction(int param) const {
    // Implementation
}

int MyClass::getValue() const {
    return _value;
}

void MyClass::setValue(int val) {
    _value = val;
}

void MyClass::staticFunc() {
    // Static implementation
}
```

---

## 📊 TABLEAU RÉCAP: const & virtual

### Placement de const
```cpp
// Dans la classe
void myFunc() const;           // ✅ Fonction const
void myFunc(const int& param); // ✅ Paramètre const
const int& getVal() const;     // ✅ Return const + fonction const

// Dans l'implémentation
void MyClass::myFunc() const { }           // ✅ const à la fin
const int& MyClass::getVal() const { }     // ✅ const au début ET fin
```

### Placement de virtual
```cpp
// Dans la classe SEULEMENT
class Base {
    virtual void func();        // ✅ Virtual normal
    virtual void func() = 0;    // ✅ Pure virtual
};

// Dans l'implémentation - PAS de virtual
void Base::func() { }  // ✅ Pas de "virtual" ici!
```

---

## 🔥 PIÈGES COURANTS

### 1. Oublier virtual destructor
```cpp
// ❌ MAUVAIS
class Base {
public:
    ~Base() { }  // Non-virtual!
};

class Derived : public Base {
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() { delete[] data; }
};

Base* ptr = new Derived();
delete ptr;  // LEAK! Appelle seulement ~Base(), pas ~Derived()

// ✅ BON
class Base {
public:
    virtual ~Base() { }  // Virtual!
};
```

### 2. Shallow copy avec pointeurs
```cpp
class Array {
    int* _data;
public:
    Array(int size) { _data = new int[size]; }
    ~Array() { delete[] _data; }

    // ❌ MAUVAIS (shallow copy par défaut)
    // Array(const Array& other) : _data(other._data) { }

    // ✅ BON (deep copy)
    Array(const Array& other) {
        _data = new int[other._size];
        for (int i = 0; i < other._size; i++)
            _data[i] = other._data[i];
    }
};
```

### 3. Self-assignment
```cpp
// ❌ MAUVAIS
Array& Array::operator=(const Array& other) {
    delete[] _data;  // Si other == *this, on delete notre propre data!
    _data = new int[other._size];
    // ...
}

// ✅ BON
Array& Array::operator=(const Array& other) {
    if (this != &other) {  // Check self-assignment
        delete[] _data;
        _data = new int[other._size];
        // ...
    }
    return *this;
}
```

### 4. Protected vs Private dans inheritance
```cpp
class Base {
private:
    int _priv;    // Inaccessible aux dérivées
protected:
    int _prot;    // ✅ Accessible aux dérivées
public:
    int _pub;     // Accessible partout
};

class Derived : public Base {
    void func() {
        _prot = 1;  // ✅ OK
        _priv = 2;  // ❌ ERROR
    }
};
```

---

## 💡 CHECKLIST AVANT CPP05

- [x] Je connais Orthodox Canonical Form (4 fonctions)
- [x] Je sais faire deep copy vs shallow copy
- [x] Je comprends public/protected/private
- [x] Je sais quand utiliser `virtual`
- [x] Je sais que destructor DOIT être virtual si polymorphisme
- [x] Je connais pure virtual `= 0` pour abstract class
- [x] Je sais l'ordre: `virtual type name(params) const`
- [x] Je sais que `virtual` n'apparaît PAS dans .cpp

---

## 🚀 TRANSITION CPP05

**CPP05 ajoute:** Exceptions (try/catch/throw)

**Ce qui reste pareil:**
- Orthodox Canonical Form
- Virtual functions
- Tout ce que tu as appris

**Ready? Let's go!** 🔥
