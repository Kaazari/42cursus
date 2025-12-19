# MODULE CPP02 : Operators & Orthodox Canonical Form

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre l'Orthodox Canonical Form (OCF)
- ✅ Implémenter les 4 fonctions canoniques
- ✅ Surcharger des opérateurs (`+`, `-`, `*`, `/`, `<<`, etc.)
- ✅ Créer une classe Fixed-point number
- ✅ Éviter les pièges de copie shallow vs deep

**Durée estimée : 7-8 heures**

**⚠️ Ce module est le PLUS CHIANT mais le PLUS IMPORTANT ! C'est la base pour CPP03-04 !**

---

## 📖 1. Orthodox Canonical Form (OCF) - LA BASE

### C'est Quoi l'OCF ?

**En C++ (à partir de CPP02), TOUTE classe doit avoir 4 fonctions minimum :**

1. **Constructeur par défaut** : `MyClass()`
2. **Copy constructor** : `MyClass(const MyClass& other)`
3. **Copy assignment operator** : `MyClass& operator=(const MyClass& other)`
4. **Destructeur** : `~MyClass()`

**Si tu ne les codes pas, le compilateur les génère automatiquement (et mal) !**

---

### Exemple Complet OCF

```cpp
class Point {
private:
    int _x;
    int _y;

public:
    // 1. Constructeur par défaut
    Point() : _x(0), _y(0) {
        std::cout << "Default constructor called" << std::endl;
    }

    // 2. Copy constructor
    Point(const Point& other) : _x(other._x), _y(other._y) {
        std::cout << "Copy constructor called" << std::endl;
    }

    // 3. Copy assignment operator
    Point& operator=(const Point& other) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other) {  // Protection contre self-assignment
            _x = other._x;
            _y = other._y;
        }
        return *this;
    }

    // 4. Destructeur
    ~Point() {
        std::cout << "Destructor called" << std::endl;
    }
};
```

---

### Quand Sont-elles Appelées ?

```cpp
Point p1;              // Constructeur par défaut
Point p2(p1);          // Copy constructor
Point p3 = p1;         // Copy constructor aussi !
p3 = p2;               // Copy assignment operator
```

---

### Protection Contre Self-Assignment

**Problème :**
```cpp
Point p;
p = p;  // Self-assignment !
```

**Solution :**
```cpp
Point& operator=(const Point& other) {
    if (this != &other) {  // Vérifie qu'on n'assigne pas à soi-même
        _x = other._x;
        _y = other._y;
    }
    return *this;
}
```

---

## 🔢 2. Fixed-Point Numbers - C'est Quoi ?

### Floating-Point (ce que tu connais)

```cpp
float f = 3.14159;
```

**Problèmes :**
- Imprécis (erreurs d'arrondi)
- Lent sur certains processeurs (pas de FPU)

---

### Fixed-Point (ce que tu vas coder)

**Principe :** Représenter un nombre décimal avec un entier.

**Exemple :** 8 bits pour la partie fractionnaire

```
Nombre réel : 42.5
Représentation : 42.5 × 2^8 = 42.5 × 256 = 10880

Stocké en mémoire : 10880 (entier)
```

**Pour retrouver la valeur :**
```
10880 / 256 = 42.5
```

---

### Formules de Conversion

**Float → Fixed :**
```cpp
int fixed = (int)roundf(float_value * (1 << fractional_bits));
//                                    ^^^^^^^^^^^^^^^^^^^^^
//                                    2^8 = 256
```

**Fixed → Float :**
```cpp
float value = (float)fixed_value / (1 << fractional_bits);
```

**Fixed → Int :**
```cpp
int value = fixed_value >> fractional_bits;
//                       ^^
//                       Diviser par 2^8
```

---

## 📝 3. Les Exercices du Sujet - Guides Complets

### Ex00 : My First Class in Orthodox Canonical Form

#### 📋 Consignes du Sujet

Créer une classe `Fixed` qui représente un nombre à virgule fixe.

**Attributs privés :**
- `int _rawBits` : valeur brute du nombre fixed-point
- `static const int _fractionalBits = 8` : nombre de bits fractionnaires (constante)

**Méthodes publiques OCF (Orthodox Canonical Form) :**
1. `Fixed()` - Constructeur par défaut (initialise à 0)
2. `Fixed(const Fixed& other)` - Copy constructor
3. `Fixed& operator=(const Fixed& other)` - Copy assignment operator
4. `~Fixed()` - Destructeur

**Méthodes supplémentaires :**
- `int getRawBits() const` - Retourne la valeur brute
- `void setRawBits(int const raw)` - Définit la valeur brute

**Affichage obligatoire :**
- Chaque constructeur/destructeur/opérateur doit afficher un message

**Objectif :** Comprendre la différence entre copy constructor et copy assignment.

#### 📁 Fichiers à Créer

```
ex00/
├── Fixed.hpp
├── Fixed.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Classe Fixed avec attributs privés
- [ ] 4 fonctions OCF implémentées
- [ ] Messages affichés à chaque appel
- [ ] getRawBits() et setRawBits() fonctionnels
- [ ] Compile sans warnings
- [ ] Comprendre : `Fixed b(a)` vs `Fixed b = a`

---

#### Fixed.hpp

```cpp
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed {
private:
    int                 _value;           // Valeur fixed-point
    static const int    _fractionalBits = 8;  // Nombre de bits fractionnaires

public:
    // OCF
    Fixed();                              // Constructeur par défaut
    Fixed(const Fixed& other);            // Copy constructor
    Fixed& operator=(const Fixed& other); // Copy assignment operator
    ~Fixed();                             // Destructeur

    // Getters/Setters
    int getRawBits() const;
    void setRawBits(int const raw);
};

#endif
```

---

#### Fixed.cpp

```cpp
#include "Fixed.hpp"

// Constructeur par défaut
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;  // Utilise l'operator=
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        _value = other.getRawBits();
    }
    return *this;
}

// Destructeur
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

// Getter
int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called" << std::endl;
    return _value;
}

// Setter
void Fixed::setRawBits(int const raw) {
    _value = raw;
}
```

---

#### Test (donné dans le sujet)

```cpp
#include "Fixed.hpp"

int main() {
    Fixed a;
    Fixed b(a);
    Fixed c;

    c = b;

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    return 0;
}
```

**Output attendu :**
```
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
```

---

### Ex01 : Towards a more useful fixed-point number class

#### 📋 Consignes du Sujet

Améliorer la classe `Fixed` pour la rendre utilisable avec des nombres réels.

**Nouveaux constructeurs à ajouter :**
- `Fixed(const int n)` - Convertit un entier en fixed-point
- `Fixed(const float f)` - Convertit un float en fixed-point

**Nouvelles méthodes de conversion :**
- `float toFloat() const` - Convertit fixed-point vers float
- `int toInt() const` - Convertit fixed-point vers int

**Surcharge d'opérateur obligatoire :**
- `std::ostream& operator<<(std::ostream& os, const Fixed& fixed)` - Affichage

**Formules à utiliser :**
- int → fixed : `value << _fractionalBits`
- float → fixed : `roundf(value * (1 << _fractionalBits))`
- fixed → float : `(float)_rawBits / (1 << _fractionalBits)`
- fixed → int : `_rawBits >> _fractionalBits`

**Ne plus afficher les messages constructeur/destructeur dans cet exercice !**

#### 📁 Fichiers à Créer

```
ex01/
├── Fixed.hpp
├── Fixed.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Constructeur `Fixed(int)` fonctionne
- [ ] Constructeur `Fixed(float)` fonctionne
- [ ] Conversions `toFloat()` et `toInt()` correctes
- [ ] `operator<<` affiche la valeur en float
- [ ] Pas de messages debug (sauf si demandé dans le main)
- [ ] Précision correcte (8 bits fractionnaires)

---

#### Nouveaux Constructeurs

**Fixed.hpp :**
```cpp
class Fixed {
    // ...
public:
    Fixed();
    Fixed(const int value);        // ← NOUVEAU
    Fixed(const float value);      // ← NOUVEAU
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    float toFloat() const;         // ← NOUVEAU
    int   toInt() const;           // ← NOUVEAU

    int getRawBits() const;
    void setRawBits(int const raw);
};

// ← NOUVEAU : Surcharge de <<
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);
```

---

#### Fixed.cpp - Conversions

```cpp
#include <cmath>

// Constructeur int
Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    _value = value << _fractionalBits;  // Multiplie par 256
}

// Constructeur float
Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    _value = roundf(value * (1 << _fractionalBits));
}

// Conversion vers float
float Fixed::toFloat() const {
    return (float)_value / (1 << _fractionalBits);
}

// Conversion vers int
int Fixed::toInt() const {
    return _value >> _fractionalBits;  // Divise par 256
}

// Surcharge de <<
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}
```

---

#### Test

```cpp
int main() {
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b);

    a = Fixed(1234.4321f);

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
}
```

**Output attendu :**
```
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
```

---

### Ex02 : Now we're talking (Operators Overload)

#### 📋 Consignes du Sujet

Surcharger tous les opérateurs pour rendre la classe `Fixed` complètement fonctionnelle.

**Opérateurs de comparaison (6) :**
- `bool operator>(const Fixed& rhs) const`
- `bool operator<(const Fixed& rhs) const`
- `bool operator>=(const Fixed& rhs) const`
- `bool operator<=(const Fixed& rhs) const`
- `bool operator==(const Fixed& rhs) const`
- `bool operator!=(const Fixed& rhs) const`

**Opérateurs arithmétiques (4) :**
- `Fixed operator+(const Fixed& rhs) const`
- `Fixed operator-(const Fixed& rhs) const`
- `Fixed operator*(const Fixed& rhs) const`
- `Fixed operator/(const Fixed& rhs) const`

**Opérateurs d'incrémentation/décrémentation (4) :**
- `Fixed& operator++()` - Pré-incrémentation (++a)
- `Fixed operator++(int)` - Post-incrémentation (a++)
- `Fixed& operator--()` - Pré-décrémentation (--a)
- `Fixed operator--(int)` - Post-décrémentation (a--)

**Fonctions statiques min/max (4 surcharges) :**
- `static Fixed& min(Fixed& a, Fixed& b)`
- `static const Fixed& min(const Fixed& a, const Fixed& b)`
- `static Fixed& max(Fixed& a, Fixed& b)`
- `static const Fixed& max(const Fixed& a, const Fixed& b)`

**Total : 18 fonctions à implémenter !**

#### 📁 Fichiers à Créer

```
ex02/
├── Fixed.hpp
├── Fixed.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] 6 opérateurs de comparaison fonctionnent
- [ ] 4 opérateurs arithmétiques corrects (attention à * et /)
- [ ] Pré/post incrémentation différents (++a retourne ref, a++ retourne copie)
- [ ] 4 versions de min/max (const et non-const)
- [ ] Epsilon le plus petit possible (incrémenter de 1 en rawBits)
- [ ] Tests complets dans le main

**⚠️ C'est l'exercice le PLUS LONG du module !**

---

#### Opérateurs à Surcharger

**1. Comparaison (6 opérateurs) :**
- `>`, `<`, `>=`, `<=`, `==`, `!=`

**2. Arithmétiques (4 opérateurs) :**
- `+`, `-`, `*`, `/`

**3. Incrémentation/Décrémentation (4 opérateurs) :**
- `++a` (pré-incrémentation)
- `a++` (post-incrémentation)
- `--a` (pré-décrémentation)
- `a--` (post-décrémentation)

**4. Fonctions statiques (4 fonctions) :**
- `min(Fixed& a, Fixed& b)`
- `min(const Fixed& a, const Fixed& b)`
- `max(Fixed& a, Fixed& b)`
- `max(const Fixed& a, const Fixed& b)`

---

#### Fixed.hpp Complet

```cpp
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed {
private:
    int                 _value;
    static const int    _fractionalBits = 8;

public:
    // OCF
    Fixed();
    Fixed(const int value);
    Fixed(const float value);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    // Conversions
    float toFloat() const;
    int   toInt() const;
    int   getRawBits() const;
    void  setRawBits(int const raw);

    // Opérateurs de comparaison
    bool operator>(const Fixed& other) const;
    bool operator<(const Fixed& other) const;
    bool operator>=(const Fixed& other) const;
    bool operator<=(const Fixed& other) const;
    bool operator==(const Fixed& other) const;
    bool operator!=(const Fixed& other) const;

    // Opérateurs arithmétiques
    Fixed operator+(const Fixed& other) const;
    Fixed operator-(const Fixed& other) const;
    Fixed operator*(const Fixed& other) const;
    Fixed operator/(const Fixed& other) const;

    // Incrémentation/Décrémentation
    Fixed& operator++();      // Pré-incrémentation
    Fixed  operator++(int);   // Post-incrémentation
    Fixed& operator--();      // Pré-décrémentation
    Fixed  operator--(int);   // Post-décrémentation

    // Fonctions statiques min/max
    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
```

---

#### Opérateurs de Comparaison

```cpp
bool Fixed::operator>(const Fixed& other) const {
    return _value > other._value;
}

bool Fixed::operator<(const Fixed& other) const {
    return _value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const {
    return _value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const {
    return _value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const {
    return _value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const {
    return _value != other._value;
}
```

---

#### Opérateurs Arithmétiques

```cpp
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(_value + other._value);
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed result;
    result.setRawBits(_value - other._value);
    return result;
}

Fixed Fixed::operator*(const Fixed& other) const {
    Fixed result;
    // Multiplication en fixed-point
    result.setRawBits((_value * other._value) >> _fractionalBits);
    return result;
}

Fixed Fixed::operator/(const Fixed& other) const {
    Fixed result;
    // Division en fixed-point
    result.setRawBits((_value << _fractionalBits) / other._value);
    return result;
}
```

---

#### Incrémentation/Décrémentation

```cpp
// Pré-incrémentation : ++a
Fixed& Fixed::operator++() {
    _value++;  // Incrémente de la plus petite valeur (1/256)
    return *this;
}

// Post-incrémentation : a++
Fixed Fixed::operator++(int) {
    Fixed temp(*this);  // Copie l'ancienne valeur
    ++(*this);          // Incrémente
    return temp;        // Retourne l'ancienne valeur
}

// Pré-décrémentation : --a
Fixed& Fixed::operator--() {
    _value--;
    return *this;
}

// Post-décrémentation : a--
Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    --(*this);
    return temp;
}
```

**Différence pré/post :**
```cpp
Fixed a(5.0f);

++a;  // a = 5 + epsilon, retourne 5 + epsilon
a++;  // a = 5 + epsilon, retourne 5 (l'ancienne valeur)
```

---

#### Fonctions Statiques min/max

```cpp
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}
```

**Utilisation :**
```cpp
Fixed a(10.5f);
Fixed b(20.3f);

Fixed min = Fixed::min(a, b);  // min = 10.5
Fixed max = Fixed::max(a, b);  // max = 20.3
```

---

#### Test du Sujet

```cpp
int main() {
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;

    std::cout << b << std::endl;

    std::cout << Fixed::max(a, b) << std::endl;

    return 0;
}
```

**Output attendu :**
```
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```

---

### Ex03 : BSP (Binary Space Partitioning)

#### 📋 Consignes du Sujet

Implémenter un algorithme géométrique pour déterminer si un point est à l'intérieur d'un triangle.

**Créer une classe `Point` :**

**Attributs privés (const !) :**
- `const Fixed _x`
- `const Fixed _y`

**Méthodes publiques :**
- `Point()` - Constructeur par défaut (0, 0)
- `Point(const float x, const float y)` - Constructeur avec coordonnées
- `Point(const Point& other)` - Copy constructor
- `Point& operator=(const Point& other)` - Copy assignment
- `~Point()` - Destructeur
- Getters : `getX()` et `getY()`

**Fonction à implémenter :**
```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```
- Retourne `true` si `point` est strictement à l'intérieur du triangle ABC
- Retourne `false` si le point est sur un bord ou à l'extérieur

**Algorithme suggéré :**
Utiliser les aires de triangles ou le produit vectoriel pour déterminer la position du point.

**⚠️ Attention : Les attributs `_x` et `_y` sont CONST !**

#### 📁 Fichiers à Créer

```
ex03/
├── Fixed.hpp
├── Fixed.cpp
├── Point.hpp
├── Point.cpp
├── bsp.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Classe Point avec attributs const
- [ ] Copy assignment gère le cas des const (fait rien)
- [ ] Fonction bsp() correcte
- [ ] Point sur le bord = false
- [ ] Point à l'intérieur = true
- [ ] Tests avec plusieurs triangles

**⚠️ Ex03 n'est PAS obligatoire mais recommandé !**

---

#### Point.hpp

```cpp
#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point {
private:
    const Fixed _x;
    const Fixed _y;

public:
    Point();
    Point(const float x, const float y);
    Point(const Point& other);
    Point& operator=(const Point& other);
    ~Point();

    Fixed getX() const;
    Fixed getY() const;
};

#endif
```

**⚠️ `_x` et `_y` sont `const` → DOIVENT être initialisés dans la liste d'initialisation !**

---

#### Point.cpp

```cpp
Point::Point() : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {}

Point& Point::operator=(const Point& other) {
    // ⚠️ On ne peut PAS assigner des const !
    // Mais on doit quand même implémenter l'operator=
    (void)other;  // Évite le warning unused
    return *this;
}

Point::~Point() {}

Fixed Point::getX() const { return _x; }
Fixed Point::getY() const { return _y; }
```

---

#### bsp.cpp - Algorithme

**Méthode : Coordonnées barycentriques**

```cpp
#include "Point.hpp"

static Fixed abs(Fixed x) {
    return (x < 0) ? x * Fixed(-1) : x;
}

static Fixed area(Point const a, Point const b, Point const c) {
    // Aire du triangle ABC
    Fixed area = ((b.getX() - a.getX()) * (c.getY() - a.getY()) -
                  (c.getX() - a.getX()) * (b.getY() - a.getY())) / Fixed(2);
    return abs(area);
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed ABC = area(a, b, c);
    Fixed PAB = area(point, a, b);
    Fixed PBC = area(point, b, c);
    Fixed PCA = area(point, c, a);

    // Le point est dans le triangle si :
    // PAB + PBC + PCA == ABC
    // ET aucune des aires n'est nulle (pas sur un bord)

    if (PAB == 0 || PBC == 0 || PCA == 0)
        return false;  // Sur un bord ou un sommet

    return (PAB + PBC + PCA == ABC);
}
```

**⚠️ Si le point est sur un bord ou un sommet, retourne `false` !**

---

## ✅ 4. Validation du Module CPP02

**Pour valider ce module, tu dois :**

1. ✅ Implémenter l'OCF correctement (Ex00)
2. ✅ Gérer les conversions int/float ↔ fixed-point (Ex01)
3. ✅ Surcharger tous les opérateurs (Ex02)
4. ⭕ Ex03 optionnel mais recommandé

---

## 🎯 Checklist Finale

- [ ] Ex00 : OCF complet (constructeur, copy, assignment, destructeur)
- [ ] Ex01 : Conversions fonctionnent (int, float, toInt, toFloat)
- [ ] Ex02 : Tous les opérateurs surchargés (14 opérateurs + 4 fonctions static)
- [ ] Protection self-assignment dans operator=
- [ ] Pas de memory leaks
- [ ] Tests avec valeurs négatives

---

## ⚠️ Pièges Classiques

**1. Oublier `if (this != &other)` dans operator= :**
```cpp
Fixed& operator=(const Fixed& other) {
    if (this != &other)  // ← IMPORTANT !
        _value = other._value;
    return *this;
}
```

**2. Pré vs Post incrémentation :**
```cpp
Fixed& operator++();      // Pré : retourne référence
Fixed  operator++(int);   // Post : retourne copie
```

**3. Attributs `const` dans Point :**
```cpp
const Fixed _x;  // Doit être initialisé dans la liste !
```

**4. Division par zéro :**
- Le sujet dit que c'est acceptable que le programme crash

---

## 🔜 Prochaine Étape

**Module CPP03 : Inheritance**
- Héritage simple
- Chaînes de construction/destruction
- Protected members
- ClapTrap family

**Passe au fichier CPP03.md ! 🚀**

---

*Module optimisé projet-only pour un étudiant 42 pressé par le temps.*
*CPP02 est chiant mais ESSENTIEL pour la suite. Courage ! 💪*
