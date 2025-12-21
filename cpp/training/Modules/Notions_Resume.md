# 🎯 Résumé des Notions C++ - Modules 00 à 04

**Par ordre de complexité croissante** 🚀

---

## 📖 Table des Matières

1. [CPP00 - Bases de la POO](#cpp00---bases-de-la-poo)
2. [CPP01 - Mémoire & Pointeurs](#cpp01---mémoire--pointeurs)
3. [CPP02 - Forme Canonique & Opérateurs](#cpp02---forme-canonique--opérateurs)
4. [CPP03 - Héritage](#cpp03---héritage)
5. [CPP04 - Polymorphisme & Classes Abstraites](#cpp04---polymorphisme--classes-abstraites)
6. [Aide-Mémoire Rapide](#aide-mémoire-rapide)

---

# CPP00 - Bases de la POO

## 🎯 Objectifs
Comprendre les bases de la Programmation Orientée Objet en C++

---

## 1️⃣ Classes et Objets

### Définition de Base

```cpp
class MyClass {
private:
    int _attribute;     // Attribut privé (convention: préfixe _)

public:
    MyClass();          // Constructeur
    ~MyClass();         // Destructeur

    void method();      // Méthode publique
    int getValue() const;  // Getter (const = ne modifie pas l'objet)
    void setValue(int val); // Setter
};
```

### Utilisation

```cpp
MyClass obj;           // Déclaration (constructeur appelé)
obj.method();          // Appel de méthode
int x = obj.getValue(); // Getter
obj.setValue(42);      // Setter
// Destructeur appelé automatiquement en fin de scope
```

---

## 2️⃣ Encapsulation

**Principe : Cacher les détails d'implémentation**

```cpp
class BankAccount {
private:
    double _balance;    // ❌ Inaccessible de l'extérieur

public:
    double getBalance() const {  // ✅ Accès contrôlé
        return _balance;
    }

    void deposit(double amount) {
        if (amount > 0)  // ✅ Validation
            _balance += amount;
    }
};
```

**Modificateurs d'accès :**
- `private:` - Accessible uniquement dans la classe
- `public:` - Accessible partout
- `protected:` - Accessible dans la classe et ses dérivées

---

## 3️⃣ Constructeur & Destructeur

### Constructeur

```cpp
class Fixed {
private:
    int _value;

public:
    // Constructeur par défaut
    Fixed() : _value(0) {
        //    ^^^^^^^^^^
        //    Liste d'initialisation (RECOMMANDÉE)
        std::cout << "Constructor called" << std::endl;
    }

    // Constructeur avec paramètres
    Fixed(int n) : _value(n) {
    }
};
```

### Destructeur

```cpp
~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
```

**Appelé automatiquement :**
- Fin de scope
- `delete` (si allocation dynamique)
- Fin du programme

---

## 4️⃣ Const Correctness

```cpp
class MyClass {
private:
    int _value;

public:
    // Méthode const : ne modifie PAS l'objet
    int getValue() const {
        return _value;  // ✅ OK (lecture)
        // _value = 42; // ❌ ERREUR (modification)
    }

    // Méthode non-const : peut modifier
    void setValue(int v) {
        _value = v;  // ✅ OK
    }
};

// Utilisation
const MyClass obj;
obj.getValue();   // ✅ OK (méthode const)
// obj.setValue(10); // ❌ ERREUR (méthode non-const sur objet const)
```

---

## 5️⃣ Static

### Attributs Static

```cpp
class Counter {
private:
    static int _count;  // Partagé par TOUTES les instances

public:
    Counter() { _count++; }
    static int getCount() { return _count; }
};

// Définition OBLIGATOIRE en dehors de la classe
int Counter::_count = 0;

// Utilisation
Counter a, b, c;
std::cout << Counter::getCount();  // 3
```

### Méthodes Static

```cpp
class Math {
public:
    static int max(int a, int b) {
        return (a > b) ? a : b;
    }
};

// Appel sans instance
int result = Math::max(5, 10);  // Pas besoin d'objet
```

---

## ✅ Checklist CPP00

- [x] Comprendre classe/objet
- [x] Maîtriser public/private
- [x] Écrire constructeur/destructeur
- [x] Utiliser const correctement
- [x] Comprendre static

---

# CPP01 - Mémoire & Pointeurs

## 🎯 Objectifs
Gérer la mémoire dynamique et comprendre pointeurs/références

---

## 1️⃣ Stack vs Heap

### Stack (Pile)

```cpp
void function() {
    int x = 42;        // Sur le STACK
    MyClass obj;       // Sur le STACK
}  // ← x et obj détruits automatiquement
```

**Caractéristiques :**
- ✅ Rapide
- ✅ Nettoyage automatique
- ❌ Taille limitée
- ❌ Durée de vie = scope

---

### Heap (Tas)

```cpp
void function() {
    int* ptr = new int(42);     // Sur le HEAP
    MyClass* obj = new MyClass(); // Sur le HEAP

    delete ptr;   // ⚠️ Libération MANUELLE obligatoire
    delete obj;   // ⚠️ Sinon fuite mémoire !
}
```

**Caractéristiques :**
- ✅ Taille flexible
- ✅ Survit au scope
- ❌ Plus lent
- ❌ Gestion manuelle (new/delete)

---

## 2️⃣ Pointeurs

### Déclaration et Utilisation

```cpp
int x = 42;
int* ptr = &x;     // ptr contient l'ADRESSE de x
//  ^      ^^
//  Type   Opérateur "adresse de"

std::cout << ptr;   // Affiche l'adresse (ex: 0x7fff5f...)
std::cout << *ptr;  // Affiche 42 (déréférencement)
//           ^
//           Opérateur de déréférencement

*ptr = 100;  // Modifie x (x devient 100)
```

### Pointeurs et Objets

```cpp
MyClass* obj = new MyClass();

obj->method();   // Appel de méthode via pointeur
//  ^^
//  Opérateur flèche

(*obj).method(); // Équivalent (moins lisible)

delete obj;  // ⚠️ OBLIGATOIRE
```

---

## 3️⃣ Références

### Déclaration

```cpp
int x = 42;
int& ref = x;  // ref est un ALIAS de x
//  ^
//  Type référence

ref = 100;     // Modifie x (x devient 100)
std::cout << x;  // 100
```

### Différences Pointeur vs Référence

| Aspect | Pointeur | Référence |
|--------|----------|-----------|
| **Syntaxe** | `int* ptr = &x;` | `int& ref = x;` |
| **NULL possible** | ✅ Oui | ❌ Non |
| **Réassignable** | ✅ Oui | ❌ Non |
| **Déréférencement** | `*ptr` | Automatique |
| **Utilisation** | `ptr->method()` | `ref.method()` |

---

## 4️⃣ Références en Paramètres

### Passage par Valeur (Copie)

```cpp
void function(MyClass obj) {  // ← Copie l'objet
    obj.modify();  // Modifie la copie
}

MyClass original;
function(original);  // original PAS modifié
```

---

### Passage par Référence (Pas de Copie)

```cpp
void function(MyClass& obj) {  // ← Pas de copie
    obj.modify();  // Modifie l'original
}

MyClass original;
function(original);  // original modifié ✅
```

---

### Passage par Référence Const (Lecture Seule)

```cpp
void function(const MyClass& obj) {  // Pas de copie, lecture seule
    obj.read();      // ✅ OK (méthode const)
    // obj.modify(); // ❌ ERREUR (modification interdite)
}
```

**Règle d'or :**
- Types simples (`int`, `float`) → par valeur
- Objets → par référence const (lecture) ou référence (modification)

---

## 5️⃣ new & delete

### Allocation Simple

```cpp
int* ptr = new int(42);
delete ptr;

MyClass* obj = new MyClass();
delete obj;
```

---

### Allocation Tableau

```cpp
int* array = new int[10];  // Tableau de 10 int
delete[] array;  // ⚠️ delete[] et PAS delete !
//      ^^

MyClass* objects = new MyClass[5];
delete[] objects;  // ⚠️ delete[] obligatoire
```

**⚠️ CRUCIAL :**
- `new` → `delete`
- `new[]` → `delete[]`
- **Jamais mélanger !**

---

## ✅ Checklist CPP01

- [x] Comprendre stack vs heap
- [x] Maîtriser pointeurs (`*`, `&`, `->`)
- [x] Maîtriser références (`&`)
- [x] Utiliser new/delete correctement
- [x] Différencier `delete` et `delete[]`
- [x] Passer par référence en paramètres

---

# CPP02 - Forme Canonique & Opérateurs

## 🎯 Objectifs
Maîtriser la forme canonique orthodoxe et la surcharge d'opérateurs

---

## 1️⃣ Forme Canonique Orthodoxe (OCF)

**4 fonctions OBLIGATOIRES dans chaque classe (à partir de CPP02) :**

```cpp
class Fixed {
private:
    int _value;

public:
    // 1. Constructeur par défaut
    Fixed();

    // 2. Copy constructor
    Fixed(const Fixed& other);

    // 3. Copy assignment operator
    Fixed& operator=(const Fixed& other);

    // 4. Destructeur
    ~Fixed();
};
```

---

## 2️⃣ Copy Constructor

**Appelé lors de la CRÉATION par copie :**

```cpp
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    _value = other._value;  // Copie simple
}

// Quand est-il appelé ?
Fixed a;
Fixed b(a);      // ✅ Copy constructor
Fixed c = a;     // ✅ Copy constructor (PAS assignment !)
```

---

## 3️⃣ Copy Assignment Operator

**Appelé lors de l'ASSIGNATION (objet existe déjà) :**

```cpp
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;

    // Protection auto-assignation
    if (this != &other) {
        _value = other._value;
    }

    return *this;  // ← Permet chaînage (a = b = c)
}

// Quand est-il appelé ?
Fixed a, b;
a = b;  // ✅ Copy assignment (a existe déjà)
```

---

## 4️⃣ Différence Copy Constructor vs Copy Assignment

```cpp
Fixed a;           // Constructeur par défaut

Fixed b(a);        // ← Copy constructor (b n'existe pas encore)
Fixed c = a;       // ← Copy constructor (c n'existe pas encore)

Fixed d;           // Constructeur par défaut
d = a;             // ← Copy assignment (d existe déjà)
```

**Règle simple :**
- Déclaration avec `=` → Copy constructor
- Assignation après déclaration → Copy assignment

---

## 5️⃣ Le Pointeur `this`

**`this` = pointeur vers l'objet courant**

```cpp
class MyClass {
private:
    int _value;

public:
    void setValue(int value) {
        this->_value = value;  // Équivalent à : _value = value;
        //    ^^
        //    Pointeur vers l'objet actuel
    }

    MyClass& getThis() {
        return *this;  // Retourne l'objet lui-même
        //     ^^^^^
        //     Déréférence de this
    }
};
```

**Usages principaux :**
1. Lever l'ambiguïté (rare avec `_`)
2. Retourner `*this` (chaînage)
3. Comparer avec `&other` (auto-assignation)

---

## 6️⃣ Protection Auto-Assignation

**Pourquoi `if (this != &other)` ?**

```cpp
Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other) {  // ← Compare les ADRESSES
    //  ^^^^    ^^^^^^
    //  |       Adresse de other
    //  Adresse de l'objet actuel
        _value = other._value;
    }
    return *this;
}

Fixed a;
a = a;  // Auto-assignation détectée → pas de copie
```

**Crucial pour classes avec pointeurs :**

```cpp
class String {
    char* _data;
public:
    String& operator=(const String& other) {
        if (this != &other) {  // ← OBLIGATOIRE !
            delete[] _data;  // Sans if : crash si this == &other
            _data = new char[strlen(other._data) + 1];
            strcpy(_data, other._data);
        }
        return *this;
    }
};
```

---

## 7️⃣ Surcharge d'Opérateurs

### Opérateurs Arithmétiques

```cpp
class Fixed {
public:
    // Addition
    Fixed operator+(const Fixed& rhs) const {
        return Fixed(_value + rhs._value);
    }

    // Soustraction
    Fixed operator-(const Fixed& rhs) const {
        return Fixed(_value - rhs._value);
    }
};

// Utilisation
Fixed a(10), b(5);
Fixed c = a + b;  // Appelle operator+
```

---

### Opérateurs de Comparaison

```cpp
class Fixed {
public:
    bool operator>(const Fixed& rhs) const {
        return _value > rhs._value;
    }

    bool operator<(const Fixed& rhs) const {
        return _value < rhs._value;
    }

    bool operator==(const Fixed& rhs) const {
        return _value == rhs._value;
    }
};

// Utilisation
if (a > b) { /* ... */ }
if (a == b) { /* ... */ }
```

---

### Opérateurs d'Incrémentation

```cpp
class Fixed {
public:
    // Pré-incrémentation : ++a
    Fixed& operator++() {
        _value++;
        return *this;  // Retourne référence
    }

    // Post-incrémentation : a++
    Fixed operator++(int) {  // int = dummy parameter
        Fixed temp(*this);  // Sauvegarde valeur actuelle
        _value++;
        return temp;  // Retourne ancienne valeur
    }
};

Fixed a(5);
++a;  // a = 6, retourne a
a++;  // a = 7, retourne 6
```

---

### Opérateur d'Insertion (<<)

**⚠️ ATTENTION : Fonction GLOBALE (hors classe) !**

```cpp
// Dans le .hpp (HORS de la classe)
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

// Dans le .cpp
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;  // ← Permet chaînage
}

// Utilisation
Fixed a(42.5f);
std::cout << a;  // Affiche 42.5
std::cout << a << " et " << b;  // Chaînage
```

**Pourquoi `ostream&` et pas `cout` ?**
→ Pour marcher avec `cout`, `cerr`, fichiers, etc.

---

## 8️⃣ Fixed-Point Numbers

**Principe : Stocker un nombre décimal dans un `int`**

```cpp
class Fixed {
private:
    int _rawBits;
    static const int _fractionalBits = 8;  // 2^8 = 256

public:
    // float → fixed
    Fixed(const float f) {
        _rawBits = roundf(f * (1 << _fractionalBits));
        //                     ^^^^^^^^^^^^^^^^^^^^
        //                     2^8 = 256
    }

    // fixed → float
    float toFloat() const {
        return (float)_rawBits / (1 << _fractionalBits);
        //                       ^^^^^^^^^^^^^^^^^^^^
        //                       256
    }
};
```

**Opérateurs de décalage de bits :**
```cpp
x << n  =  x × 2^n  // Décalage à gauche
x >> n  =  x / 2^n  // Décalage à droite

// Exemples :
5 << 1  =  10   // 5 × 2
5 << 2  =  20   // 5 × 4
20 >> 1 =  10   // 20 / 2
20 >> 2 =  5    // 20 / 4
```

---

## ✅ Checklist CPP02

- [x] Implémenter les 4 fonctions OCF
- [x] Comprendre copy constructor vs copy assignment
- [x] Maîtriser `this` et `*this`
- [x] Protéger contre auto-assignation
- [x] Surcharger opérateurs basiques
- [x] Différencier `++a` et `a++`
- [x] Implémenter `operator<<` (fonction globale)
- [x] Comprendre fixed-point et bitshift

---

# CPP03 - Héritage

## 🎯 Objectifs
Comprendre l'héritage et la réutilisation de code

---

## 1️⃣ Héritage de Base

### Syntaxe

```cpp
// Classe de base (parent)
class Animal {
protected:  // ← Accessible dans les classes dérivées
    std::string _name;

public:
    Animal(std::string name);
    void eat();
    void sleep();
};

// Classe dérivée (enfant)
class Dog : public Animal {
//        ^^^^^^^^
//        Héritage public
private:
    std::string _breed;

public:
    Dog(std::string name, std::string breed);
    void bark();  // Méthode spécifique à Dog
};
```

---

### Constructeurs avec Héritage

```cpp
// Constructeur de la classe de base
Animal::Animal(std::string name) : _name(name) {
    std::cout << "Animal constructor" << std::endl;
}

// Constructeur de la classe dérivée
Dog::Dog(std::string name, std::string breed)
    : Animal(name),  // ← Appelle le constructeur parent
      _breed(breed) {
    std::cout << "Dog constructor" << std::endl;
}
```

**Ordre d'exécution :**
1. Constructeur parent (`Animal`)
2. Constructeur enfant (`Dog`)

**Ordre de destruction :**
1. Destructeur enfant (`Dog`)
2. Destructeur parent (`Animal`)

---

## 2️⃣ Modificateurs d'Accès

```cpp
class Base {
private:
    int _private;    // ❌ Accessible UNIQUEMENT dans Base

protected:
    int _protected;  // ✅ Accessible dans Base ET dérivées

public:
    int _public;     // ✅ Accessible partout
};

class Derived : public Base {
public:
    void test() {
        // _private;    ❌ ERREUR (privé)
        _protected;     // ✅ OK (protégé)
        _public;        // ✅ OK (public)
    }
};
```

**Règle simple :**
- `private:` → Classe uniquement
- `protected:` → Classe + dérivées
- `public:` → Partout

---

## 3️⃣ Types d'Héritage

```cpp
class Derived : public Base { };     // ← Le plus courant
class Derived : protected Base { };
class Derived : private Base { };
```

**À 42, on utilise TOUJOURS `public` ! ✅**

---

## 4️⃣ Héritage Multiple (Diamond Problem)

```cpp
class A {
public:
    void method();
};

class B : public A { };
class C : public A { };

class D : public B, public C {
//        ^^^^^^^^^^^^^^^^^^
//        Héritage multiple
public:
    void test() {
        // method();  ❌ ERREUR : ambiguïté (vient de B ou C ?)
        B::method();  // ✅ OK : spécifie B
        C::method();  // ✅ OK : spécifie C
    }
};
```

**Solution : Héritage virtuel**

```cpp
class B : virtual public A { };
class C : virtual public A { };
//        ^^^^^^^

class D : public B, public C {
    // Une seule copie de A maintenant
};
```

---

## ✅ Checklist CPP03

- [x] Comprendre héritage public
- [x] Appeler constructeur parent
- [x] Utiliser `protected`
- [x] Gérer héritage multiple
- [x] Résoudre diamond problem

---

# CPP04 - Polymorphisme & Classes Abstraites

## 🎯 Objectifs
Maîtriser le polymorphisme, les classes abstraites et les interfaces

---

## 1️⃣ Fonctions Virtuelles

### Sans `virtual` (Pas de Polymorphisme)

```cpp
class Animal {
public:
    void makeSound() {  // ← Pas virtual
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() {  // ← Override
        std::cout << "Woof!" << std::endl;
    }
};

// Utilisation
Dog dog;
Animal* ptr = &dog;

ptr->makeSound();  // ❌ Affiche "Animal sound" (pas polymorphique)
```

---

### Avec `virtual` (Polymorphisme ✅)

```cpp
class Animal {
public:
    virtual void makeSound() {  // ← virtual !
        std::cout << "Animal sound" << std::endl;
    }

    virtual ~Animal() { }  // ⚠️ Destructeur virtuel OBLIGATOIRE
};

class Dog : public Animal {
public:
    void makeSound() {  // Override automatique
        std::cout << "Woof!" << std::endl;
    }
};

// Utilisation
Dog dog;
Animal* ptr = &dog;

ptr->makeSound();  // ✅ Affiche "Woof!" (polymorphisme)
```

**Règle d'or : TOUJOURS mettre le destructeur `virtual` dans une classe de base !**

---

## 2️⃣ Classes Abstraites

**Classe avec au moins une méthode virtuelle pure**

```cpp
class Animal {  // ← Classe abstraite
public:
    virtual void makeSound() = 0;  // ← Méthode virtuelle PURE
    //                       ^^^
    //                       = 0 rend la méthode pure

    virtual ~Animal() { }
};

// Animal a;  ❌ ERREUR : Impossible d'instancier une classe abstraite

class Dog : public Animal {
public:
    void makeSound() {  // ← Implémentation OBLIGATOIRE
        std::cout << "Woof!" << std::endl;
    }
};

Dog dog;  // ✅ OK (Dog implémente makeSound)
```

**Usage :**
- Forcer les classes dérivées à implémenter une méthode
- Définir une interface

---

## 3️⃣ Interfaces (Classe 100% Abstraite)

```cpp
class IAnimal {  // ← Interface (convention: préfixe I)
public:
    virtual void makeSound() = 0;
    virtual void move() = 0;
    virtual ~IAnimal() { }

    // ❌ PAS d'attributs
    // ❌ PAS d'implémentation
};

class Dog : public IAnimal {
public:
    void makeSound() {  // ← DOIT implémenter
        std::cout << "Woof!" << std::endl;
    }

    void move() {  // ← DOIT implémenter
        std::cout << "Running" << std::endl;
    }
};
```

**Interface = Contrat que les classes dérivées doivent respecter**

---

## 4️⃣ Destructeur Virtuel (CRUCIAL ⚠️)

### Sans Destructeur Virtuel (Bug)

```cpp
class Base {
public:
    ~Base() {  // ← PAS virtual
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
private:
    int* _data;

public:
    Derived() { _data = new int[100]; }

    ~Derived() {  // ← Pas appelé si via pointeur Base* !
        delete[] _data;
        std::cout << "Derived destructor" << std::endl;
    }
};

// Utilisation
Base* ptr = new Derived();
delete ptr;  // ❌ Appelle SEULEMENT ~Base() !
             // → Fuite mémoire (_data jamais libéré)
```

---

### Avec Destructeur Virtuel (Correct ✅)

```cpp
class Base {
public:
    virtual ~Base() {  // ← virtual !
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
private:
    int* _data;

public:
    Derived() { _data = new int[100]; }

    ~Derived() {
        delete[] _data;
        std::cout << "Derived destructor" << std::endl;
    }
};

// Utilisation
Base* ptr = new Derived();
delete ptr;  // ✅ Appelle ~Derived() PUIS ~Base()
             // → Pas de fuite mémoire
```

**Règle absolue : Si une classe a des méthodes `virtual`, le destructeur DOIT être `virtual` !**

---

## 5️⃣ Tableau de Polymorphisme

```cpp
Animal* animals[3];

animals[0] = new Dog();
animals[1] = new Cat();
animals[2] = new Bird();

// Polymorphisme en action
for (int i = 0; i < 3; i++) {
    animals[i]->makeSound();  // Appelle la bonne méthode !
}

// Nettoyage
for (int i = 0; i < 3; i++) {
    delete animals[i];  // ✅ Appelle le bon destructeur (si virtual)
}
```

---

## 6️⃣ Virtual vs Pure Virtual

| Type | Syntaxe | Implémentation | Classe abstraite ? |
|------|---------|----------------|-------------------|
| **Normale** | `void method();` | Obligatoire | Non |
| **Virtual** | `virtual void method();` | Optionnelle | Non |
| **Pure Virtual** | `virtual void method() = 0;` | Interdite (dans classe abstraite) | Oui |

```cpp
class Example {
public:
    void normal();              // Méthode normale
    virtual void virt();        // Virtuelle (peut être override)
    virtual void pure() = 0;    // Pure (DOIT être override)
};
```

---

## ✅ Checklist CPP04

- [x] Utiliser `virtual` pour polymorphisme
- [x] Créer classes abstraites (méthodes pures)
- [x] Implémenter interfaces
- [x] TOUJOURS mettre destructeur `virtual`
- [x] Comprendre liaison dynamique
- [x] Utiliser tableaux polymorphiques

---

# Aide-Mémoire Rapide

## 🔥 Syntaxe Essentielle

### Pointeurs & Références

```cpp
int x = 42;

int* ptr = &x;     // Pointeur
int& ref = x;      // Référence

*ptr = 100;        // Déréférence
ref = 100;         // Pas de déréférence nécessaire

ptr->method();     // Méthode via pointeur
ref.method();      // Méthode via référence
```

---

### Forme Canonique

```cpp
class MyClass {
public:
    MyClass();                              // 1. Constructeur
    MyClass(const MyClass& other);          // 2. Copy constructor
    MyClass& operator=(const MyClass& other); // 3. Copy assignment
    ~MyClass();                             // 4. Destructeur
};
```

---

### Héritage

```cpp
class Base {
protected:
    int _value;
public:
    virtual void method() = 0;  // Pure virtual
    virtual ~Base() { }         // Destructeur virtuel
};

class Derived : public Base {
public:
    Derived() : Base() { }      // Appel constructeur parent
    void method() { }           // Implémentation obligatoire
};
```

---

## 🎯 Erreurs Classiques à Éviter

### ❌ Oublier `delete`

```cpp
int* ptr = new int(42);
// delete ptr;  ← OUBLIÉ → FUITE MÉMOIRE
```

---

### ❌ `delete` au lieu de `delete[]`

```cpp
int* arr = new int[10];
delete arr;  // ❌ ERREUR ! Devrait être delete[]
```

---

### ❌ Retourner `this` au lieu de `*this`

```cpp
MyClass& operator=(const MyClass& other) {
    // ...
    return this;   // ❌ ERREUR (retourne pointeur)
    return *this;  // ✅ CORRECT (retourne objet)
}
```

---

### ❌ Oublier `virtual` dans le destructeur

```cpp
class Base {
public:
    ~Base() { }  // ❌ Devrait être virtual
};

Base* ptr = new Derived();
delete ptr;  // Fuite mémoire (destructeur Derived pas appelé)
```

---

### ❌ Ne pas protéger contre auto-assignation

```cpp
MyClass& operator=(const MyClass& other) {
    delete _data;  // ❌ Si this == &other → CRASH
    _data = new int(*other._data);

    // ✅ Correct :
    if (this != &other) {
        delete _data;
        _data = new int(*other._data);
    }
}
```

---

## 📊 Tableau Récapitulatif

| Module | Concepts Clés | Difficulté | Temps Estimé |
|--------|---------------|------------|--------------|
| **CPP00** | Classes, encapsulation | ⭐⭐ | 4-6h |
| **CPP01** | Pointeurs, références, new/delete | ⭐⭐⭐ | 5-7h |
| **CPP02** | OCF, opérateurs, fixed-point | ⭐⭐⭐⭐ | 6-8h |
| **CPP03** | Héritage, diamond problem | ⭐⭐⭐ | 4-6h |
| **CPP04** | Polymorphisme, abstraites | ⭐⭐⭐⭐⭐ | 8-12h |

---

## 🚀 Conseils Généraux

### 1. Toujours Initialiser

```cpp
// ✅ BON
MyClass() : _value(0) { }

// ❌ MAUVAIS
MyClass() {
    // _value pas initialisé → valeur random
}
```

---

### 2. const Correctness

```cpp
// Méthode const si elle ne modifie pas l'objet
int getValue() const { return _value; }

// Paramètre const& pour objets
void process(const MyClass& obj);
```

---

### 3. Ordre d'Initialisation

**Liste d'initialisation suit l'ordre de DÉCLARATION, pas l'ordre dans la liste !**

```cpp
class MyClass {
private:
    int _a;
    int _b;

public:
    // ✅ Ordre : _a puis _b (ordre de déclaration)
    MyClass() : _a(0), _b(0) { }

    // ⚠️ _b initialisé avant _a (ordre déclaration) !
    MyClass() : _b(0), _a(_b) { }  // _a = valeur random !
};
```

---

### 4. Return `*this` pour Chaînage

```cpp
MyClass& operator=(const MyClass& other) {
    // ...
    return *this;  // Permet : a = b = c;
}

MyClass& operator++() {
    _value++;
    return *this;  // Permet : ++(++a);
}
```

---

### 5. Destructeur Virtuel Systématique

```cpp
// Dès qu'il y a virtual quelque part :
class Base {
public:
    virtual void method();
    virtual ~Base() { }  // ← OBLIGATOIRE
};
```

---

## 💡 Ressources

- **Normes 42 :** `-Wall -Wextra -Werror`, C++98, Orthodox Canonical Form
- **Compilation :** `c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program`
- **Valgrind :** `valgrind --leak-check=full ./program` (vérifier fuites mémoire)

---

**Bon Courage ! 🔥**

*N'hésite pas à relire ce document régulièrement pour ancrer les concepts !*
