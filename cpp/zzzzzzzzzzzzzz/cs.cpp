// ============================================
// 🔥 CPP CHEATSHEET COMPLET - 42
// ============================================

// ============================================
// 📋 FORME CANONIQUE (TOUJOURS)
// ============================================

class MyClass {
private:
    int* _data;

public:
    // 1. Constructeur par défaut
    MyClass();

    // 2. Copy constructor (DEEP COPY si pointeurs!)
    MyClass(MyClass const& src);

    // 3. Assignment operator
    MyClass& operator=(MyClass const& rhs);

    // 4. Destructeur (virtual si héritage!)
    ~MyClass();
};

// Implémentation
MyClass::MyClass() : _data(NULL) {}

MyClass::MyClass(MyClass const& src) {
    _data = new int(*src._data);  // Deep copy
}

MyClass& MyClass::operator=(MyClass const& rhs) {
    if (this != &rhs) {  // Self-assignment check
        delete _data;
        _data = new int(*rhs._data);
    }
    return *this;
}

MyClass::~MyClass() {
    delete _data;
}


// ============================================
// 🎯 HÉRITAGE & POLYMORPHISME
// ============================================

// Classe de base
class Animal {
protected:  // Accessible aux classes dérivées
    std::string _type;

public:
    Animal();
    virtual ~Animal();  // TOUJOURS virtual si héritage!

    virtual void makeSound() const;  // Peut être overridée
    virtual void eat() const = 0;    // Pure virtual (= abstract)
};

// Classe dérivée
class Dog : public Animal {
public:
    Dog();
    virtual ~Dog();

    virtual void makeSound() const;  // Override
    virtual void eat() const;        // Override obligatoire
};

// Implémentation
Dog::Dog() : Animal() {}  // Appelle constructeur parent

// Usage polymorphique
Animal* animal = new Dog();
animal->makeSound();  // Appelle Dog::makeSound() (virtual)
delete animal;        // Appelle Dog::~Dog() puis Animal::~Animal()


// ============================================
// 🔥 OPERATOR OVERLOADING
// ============================================

class Fixed {
private:
    int _value;

public:
    // Arithmetic
    Fixed operator+(Fixed const& rhs) const;
    Fixed operator-(Fixed const& rhs) const;
    Fixed operator*(Fixed const& rhs) const;
    Fixed operator/(Fixed const& rhs) const;

    // Comparison
    bool operator>(Fixed const& rhs) const;
    bool operator<(Fixed const& rhs) const;
    bool operator==(Fixed const& rhs) const;

    // Increment/Decrement
    Fixed& operator++();      // Prefix: ++a
    Fixed operator++(int);    // Postfix: a++

    // Assignment
    Fixed& operator=(Fixed const& rhs);

    // Subscript (pour containers)
    int& operator[](int index);
};

// Implémentation
Fixed Fixed::operator+(Fixed const& rhs) const {
    Fixed result;
    result._value = this->_value + rhs._value;
    return result;
}

// Stream operator (OUTSIDE class)
std::ostream& operator<<(std::ostream& out, Fixed const& f) {
    out << f.getValue();
    return out;
}


// ============================================
// ⚠️ EXCEPTIONS
// ============================================

// Créer exception custom
class MyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "My error message";
    }
};

// Usage
try {
    if (error)
        throw MyException();
    // ou
    throw std::runtime_error("Error message");
}
catch (MyException& e) {
    std::cerr << e.what() << std::endl;
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}

// Exceptions standards
throw std::runtime_error("msg");
throw std::logic_error("msg");
throw std::out_of_range("msg");


// ============================================
// 🎨 TEMPLATES
// ============================================

// Template fonction
template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// Usage
int x = 1, y = 2;
swap(x, y);  // Type déduit automatiquement

// Template classe
template <typename T>
class Array {
private:
    T* _data;
    unsigned int _size;

public:
    Array();
    Array(unsigned int n);
    ~Array();

    T& operator[](unsigned int i);
    unsigned int size() const;
};

// Implémentation (TOUT dans .hpp!)
template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}

// Usage
Array<int> arr(5);
arr[0] = 42;


// ============================================
// 📦 CONTAINERS STL
// ============================================

#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>

// VECTOR (array dynamique)
std::vector<int> vec;
vec.push_back(42);        // Ajoute
vec[0] = 10;              // Accès
vec.size();               // Taille
vec.clear();              // Vide

// LIST (linked list)
std::list<int> lst;
lst.push_back(42);
lst.push_front(10);

// MAP (dictionnaire clé-valeur)
std::map<std::string, int> m;
m["key"] = 42;            // Insert/update
m.find("key");            // Cherche
m.lower_bound("key");     // Premier >= key

// SET (valeurs uniques)
std::set<int> s;
s.insert(42);
s.find(42);

// STACK (LIFO)
std::stack<int> stack;
stack.push(42);
stack.pop();
stack.top();              // Dernier élément

// QUEUE (FIFO)
std::queue<int> q;
q.push(42);
q.pop();
q.front();                // Premier élément


// ============================================
// 🔄 ITERATORS
// ============================================

std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);

// Iterator
std::vector<int>::iterator it;
for (it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << std::endl;  // Dereference
}

// Const iterator
std::vector<int>::const_iterator cit;
for (cit = vec.begin(); cit != vec.end(); ++cit) {
    std::cout << *cit << std::endl;
}

// Reverse iterator
std::vector<int>::reverse_iterator rit;
for (rit = vec.rbegin(); rit != vec.rend(); ++rit) {
    std::cout << *rit << std::endl;
}


// ============================================
// 📝 STRING MANIPULATION
// ============================================

#include <string>
#include <sstream>
#include <cstdlib>

std::string str = "Hello World";

// Longueur
str.length();
str.size();

// Accès
str[0];                    // 'H'
str.at(1);                 // 'e' (avec bounds check)

// Chercher
str.find("World");         // Position ou npos
str.find_first_of("aeiou");
str.find_last_of("aeiou");

// Extraire
str.substr(0, 5);          // "Hello" (pos, length)
str.substr(6);             // "World" (pos jusqu'à la fin)

// Conversion
str.c_str();               // → const char*

// Comparaison
str == "Hello";
str.compare("Hello");

// Modification
str += " !";               // Concaténation
str.append(" !");
str.erase(5, 6);           // Efface (pos, length)


// ============================================
// 🔄 STRING CONVERSION
// ============================================

#include <cstdlib>
#include <sstream>

// String → int/float
int i = atoi("42");               // C-style
float f = atof("42.5");

// String → int (C++ style)
std::stringstream ss("42");
int num;
ss >> num;

// Int → string
std::stringstream ss;
ss << 42;
std::string str = ss.str();

// Float → string avec precision
std::stringstream ss;
ss << std::fixed << std::setprecision(2) << 42.567;
std::string str = ss.str();  // "42.57"


// ============================================
// 📂 FICHIERS
// ============================================

#include <fstream>

// Lecture
std::ifstream file("input.txt");
if (!file.is_open()) {
    // Erreur
}

std::string line;
while (std::getline(file, line)) {
    // Process line
}
file.close();

// Écriture
std::ofstream file("output.txt");
file << "Hello" << std::endl;
file.close();


// ============================================
// 🎲 PARSING
// ============================================

// Split sur délimiteur
std::string line = "2011-01-03,0.3";
size_t comma = line.find(',');

std::string date = line.substr(0, comma);
std::string price = line.substr(comma + 1);

// Trim whitespace
std::string trim(std::string const& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}


// ============================================
// 🔢 CASTING C++
// ============================================

// static_cast (conversions normales)
float f = 42.9f;
int i = static_cast<int>(f);  // 42

// dynamic_cast (downcast polymorphique)
Animal* animal = new Dog();
Dog* dog = dynamic_cast<Dog*>(animal);
if (dog != NULL) {
    dog->bark();
}

// const_cast (enlever const - RARE)
const int* ptr = &x;
int* mutable_ptr = const_cast<int*>(ptr);

// reinterpret_cast (cast brutal - DANGEREUX)
int* p = reinterpret_cast<int*>(&f);


// ============================================
// 💾 MÉMOIRE
// ============================================

// Allocation
int* ptr = new int;
int* arr = new int[10];

// Initialisation
int* ptr = new int(42);        // *ptr = 42
int* arr = new int[10]();      // Tous à 0

// Libération
delete ptr;
delete[] arr;  // IMPORTANT: [] pour array!

// Deep copy
int* copy = new int[size];
for (int i = 0; i < size; i++)
    copy[i] = original[i];


// ============================================
// 🔍 POINTEURS vs RÉFÉRENCES
// ============================================

// Pointeur (peut être NULL)
int* ptr = &x;
*ptr = 42;
ptr = NULL;

// Référence (ne peut PAS être NULL)
int& ref = x;
ref = 42;  // Modifie x directement


// ============================================
// 🎯 CONST
// ============================================

// Fonction const (ne modifie pas l'objet)
int getValue() const { return _value; }

// Paramètre const (ne sera pas modifié)
void func(int const& param);

// Return const (valeur constante)
const int& getRef() const;

// Pointeur const
const int* ptr;      // Pointeur vers int constant
int* const ptr;      // Pointeur constant
const int* const p;  // Les deux


// ============================================
// 📊 TYPEDEF
// ============================================

typedef std::vector<int>::iterator iter;
iter it = vec.begin();

// Dans templates
template <typename T>
class MyClass {
    typedef typename T::iterator iterator;
};


// ============================================
// ⚡ TIPS PRATIQUES
// ============================================

// Self-assignment check
if (this != &rhs) { /* ... */ }

// Initializer list (TOUJOURS utiliser)
MyClass::MyClass() : _data(NULL), _size(0) {}

// Virtual destructor si héritage
virtual ~MyClass() {}

// Protected pour héritage
protected:
    int _protectedVar;  // Accessible aux classes dérivées

// Static (partagé entre instances)
static int count;

// Const member function
int size() const { return _size; }


// ============================================
// 🚨 ERREURS COURANTES
// ============================================

// ❌ Shallow copy avec pointeurs
MyClass(MyClass const& src) : _data(src._data) {}  // BAD

// ✅ Deep copy
MyClass(MyClass const& src) {
    _data = new int(*src._data);  // GOOD
}

// ❌ Oublier virtual destructor
class Base {
    ~Base() {}  // BAD si héritage
};

// ✅ Virtual destructor
class Base {
    virtual ~Base() {}  // GOOD
};

// ❌ Pas de delete[]
int* arr = new int[10];
delete arr;  // BAD (leak!)

// ✅ delete[] pour arrays
delete[] arr;  // GOOD


// ============================================
// 🎓 ORDRE COMPILATION
// ============================================

Construction:
1. Classe parente constructor
2. Membres (dans l'ordre de déclaration)
3. Classe dérivée constructor

Destruction (INVERSE):
1. Classe dérivée destructor
2. Membres
3. Classe parente destructor


// ============================================
// 🔧 MAKEFILE STANDARD
// ============================================

NAME = program

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp MyClass.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


// ============================================
// 📚 RESSOURCES ESSENTIELLES
// ============================================

// Documentation
https://en.cppreference.com/      // Référence complète
http://cplusplus.com/              // Exemples simples

// Google patterns
"c++ [concept] example"
"c++ how to [action]"
"c++ [error message]"
