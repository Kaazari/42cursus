# MODULE CPP00 : Classes & Objets

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre la différence entre `struct` et `class`
- ✅ Créer des classes avec constructeurs et destructeurs
- ✅ Utiliser public/private/protected correctement
- ✅ Implémenter des member functions (méthodes)
- ✅ Comprendre le pointeur `this`
- ✅ Valider tes compétences avec 5 exercices + Ex00 et Ex01 du sujet

**Durée estimée : 6-8 heures**

---

## 📖 1. De struct à class : La Transition

### Ce que tu connais : les structures en C

**En C, une structure c'est :**
```c
typedef struct s_player {
    char    *name;
    int     health;
    int     mana;
} t_player;

// Création
t_player *create_player(char *name) {
    t_player *p = malloc(sizeof(t_player));
    p->name = strdup(name);
    p->health = 100;
    p->mana = 50;
    return p;
}

// Modification
void player_take_damage(t_player *p, int damage) {
    p->health -= damage;
}

// Destruction
void destroy_player(t_player *p) {
    free(p->name);
    free(p);
}

// Utilisation
int main(void) {
    t_player *hero = create_player("Aragorn");
    player_take_damage(hero, 20);
    printf("Health: %d\n", hero->health);
    destroy_player(hero);
    return 0;
}
```

**Problèmes avec cette approche :**
- Les données et les fonctions sont **séparées**
- Tu dois passer le pointeur à chaque fonction
- Rien n'empêche d'accéder directement à `hero->health` (pas d'encapsulation)
- Tu peux oublier d'appeler `destroy_player()` → leak

---

### En C++ : La classe regroupe tout

```cpp
#include <string>
#include <iostream>

class Player {
private:                        // Privé = invisible de l'extérieur
    std::string _name;
    int         _health;
    int         _mana;

public:                         // Public = accessible de partout
    // Constructeur (remplace create_player)
    Player(std::string name) {
        _name = name;
        _health = 100;
        _mana = 50;
        std::cout << "Player " << _name << " created" << std::endl;
    }

    // Destructeur (remplace destroy_player)
    ~Player() {
        std::cout << "Player " << _name << " destroyed" << std::endl;
        // string se libère automatiquement
    }

    // Méthode (remplace player_take_damage)
    void takeDamage(int damage) {
        _health -= damage;
    }

    // Getter pour lire health
    int getHealth() const {
        return _health;
    }
};

// Utilisation
int main() {
    Player hero("Aragorn");         // Constructeur appelé automatiquement
    hero.takeDamage(20);            // Appel de méthode
    std::cout << "Health: " << hero.getHealth() << std::endl;

    return 0;
}   // Destructeur appelé automatiquement ici
```

**Avantages :**
- ✅ Données + fonctions **regroupées** dans la classe
- ✅ **Encapsulation** : on ne peut pas modifier `_health` directement
- ✅ **Constructeur/Destructeur automatiques** : pas de risque d'oubli
- ✅ Code plus **lisible** : `hero.takeDamage(20)` au lieu de `player_take_damage(&hero, 20)`

---

## 🔐 2. Public, Private, Protected

### Les Niveaux de Visibilité

```cpp
class Player {
private:
    int _secret;        // Accessible uniquement DANS la classe

protected:
    int _internal;      // Accessible dans la classe ET les classes dérivées

public:
    int visible;        // Accessible PARTOUT
};
```

**Tableau récapitulatif :**

| Niveau | Classe elle-même | Classes dérivées | Extérieur |
|--------|------------------|------------------|-----------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

**Note importante :** Par défaut dans une `class`, tout est `private`. Dans une `struct`, tout est `public`.

---

### Exemple Concret

```cpp
class BankAccount {
private:
    int _balance;           // Privé : personne ne peut modifier directement

public:
    BankAccount() {
        _balance = 0;
    }

    void deposit(int amount) {
        if (amount > 0)
            _balance += amount;
    }

    bool withdraw(int amount) {
        if (amount > 0 && _balance >= amount) {
            _balance -= amount;
            return true;
        }
        return false;
    }

    int getBalance() const {
        return _balance;
    }
};

int main() {
    BankAccount account;

    account.deposit(100);
    // account._balance = 1000000;  // ❌ ERREUR : _balance est privé

    std::cout << "Balance: " << account.getBalance() << std::endl;

    return 0;
}
```

**Pourquoi c'est important ?**
- On **contrôle** comment `_balance` est modifié
- Impossible de mettre une valeur négative ou invalide
- C'est ça, l'**encapsulation**

---

## 🏗️ 3. Constructeurs & Destructeurs

### Le Constructeur : Initialisation Automatique

**En C :**
```c
t_player *p = malloc(sizeof(t_player));
p->health = 100;
p->mana = 50;
p->name = strdup("Bob");
```

**En C++ :**
```cpp
Player p("Bob");  // Tout est initialisé automatiquement
```

**Syntaxes de constructeur :**

```cpp
class Player {
private:
    std::string _name;
    int         _health;
    int         _mana;

public:
    // 1. Constructeur par défaut (sans paramètres)
    Player() {
        _name = "Unknown";
        _health = 100;
        _mana = 50;
    }

    // 2. Constructeur avec paramètres
    Player(std::string name) {
        _name = name;
        _health = 100;
        _mana = 50;
    }

    // 3. Constructeur avec liste d'initialisation (RECOMMANDÉ)
    Player(std::string name, int hp, int mp) : _name(name), _health(hp), _mana(mp) {
        // Le corps peut être vide si tout est initialisé dans la liste
    }
};
```

**Pourquoi la liste d'initialisation est meilleure ?**
```cpp
// ❌ Moins efficace (initialisation puis assignation)
Player(std::string name) {
    _name = name;           // 1. string créé vide, 2. puis assigné
}

// ✅ Plus efficace (initialisation directe)
Player(std::string name) : _name(name) {
    // string créé directement avec la bonne valeur
}
```

---

### Le Destructeur : Nettoyage Automatique

**En C :**
```c
void destroy_player(t_player *p) {
    free(p->weapon);
    free(p->inventory);
    free(p);
}
// Il faut PENSER à l'appeler !
```

**En C++ :**
```cpp
class Player {
private:
    int *_inventory;

public:
    Player() {
        _inventory = new int[10];  // Allocation dynamique
    }

    ~Player() {
        delete[] _inventory;       // Libération automatique
        std::cout << "Player destroyed" << std::endl;
    }
};

// Utilisation
{
    Player p;
    // ...
}   // Destructeur appelé AUTOMATIQUEMENT ici
```

**Règle d'or :** Si tu fais `new` dans le constructeur, tu fais `delete` dans le destructeur.

---

### Quand sont appelés constructeur et destructeur ?

```cpp
void function() {
    Player p1;              // Constructeur appelé

    if (true) {
        Player p2;          // Constructeur appelé
        // ...
    }                       // Destructeur de p2 appelé (fin de scope)

    Player *p3 = new Player();  // Constructeur appelé
    delete p3;                  // Destructeur appelé MANUELLEMENT

}                           // Destructeur de p1 appelé (fin de fonction)
```

**Stack vs Heap :**
- **Stack** (`Player p;`) : destructeur automatique
- **Heap** (`Player *p = new Player();`) : tu dois faire `delete p;`

---

## 📝 4. Member Functions (Méthodes)

### Syntaxe de Base

**Dans le .hpp (déclaration) :**
```cpp
class Player {
private:
    int _health;

public:
    Player();
    void takeDamage(int damage);    // Déclaration
    int  getHealth() const;         // const = ne modifie pas l'objet
};
```

**Dans le .cpp (définition) :**
```cpp
#include "Player.hpp"

Player::Player() : _health(100) {
    // Constructeur
}

void Player::takeDamage(int damage) {
    _health -= damage;
}

int Player::getHealth() const {
    return _health;
}
```

**Syntaxe importante :** `Player::takeDamage` signifie "la méthode `takeDamage` de la classe `Player`"

---

### Le mot-clé `const`

```cpp
class Player {
private:
    int _health;

public:
    // Cette méthode ne modifie PAS l'objet
    int getHealth() const {
        return _health;
    }

    // Cette méthode MODIFIE l'objet
    void takeDamage(int damage) {
        _health -= damage;
    }

    // ❌ Erreur : const et modification incompatibles
    void badMethod() const {
        _health = 0;  // ❌ Interdit car méthode const
    }
};
```

**Règle :** Si une méthode ne modifie pas l'objet, mets `const`. C'est une bonne pratique.

---

## 👉 5. Le Pointeur `this`

### C'est Quoi `this` ?

**En C, tu faisais :**
```c
void player_heal(t_player *self, int amount) {
    self->health += amount;
}
```

**En C++, `this` est ce pointeur automatique :**
```cpp
class Player {
private:
    int _health;

public:
    void heal(int amount) {
        // 'this' pointe vers l'objet actuel
        this->_health += amount;

        // Équivalent (plus court) :
        _health += amount;
    }

    // Retourner *this permet le chaînage
    Player& addHealth(int amount) {
        _health += amount;
        return *this;
    }
};

// Utilisation
Player p;
p.addHealth(10).addHealth(20);  // Chaînage possible grâce à 'return *this'
```

**`this` est un pointeur vers l'objet courant.**

---

### Quand utiliser `this` explicitement ?

**1. Conflit de nom :**
```cpp
class Player {
private:
    int health;

public:
    void setHealth(int health) {
        this->health = health;  // Distingue paramètre et attribut
    }
};
```

**2. Retourner l'objet lui-même :**
```cpp
Player& setName(std::string name) {
    _name = name;
    return *this;
}
```

**3. Passer l'objet à une fonction :**
```cpp
void attack(Enemy& target) {
    target.takeDamage(this->getDamage());
}
```

---

## 📝 6. Exercices Progressifs

### Exercice 00 : Première Classe Simple

**Objectif :** Créer une classe `Counter` qui compte.

**Fichier Counter.hpp :**
```cpp
#ifndef COUNTER_HPP
# define COUNTER_HPP

class Counter {
private:
    int _value;

public:
    Counter();              // Constructeur par défaut
    ~Counter();             // Destructeur

    void increment();       // Augmente de 1
    void decrement();       // Diminue de 1
    int  getValue() const;  // Retourne la valeur
};

#endif
```

**Fichier Counter.cpp :**
```cpp
#include "Counter.hpp"
#include <iostream>

// À TOI DE COMPLÉTER

Counter::Counter() {
    // Initialise _value à 0
    // Affiche un message de création
}

Counter::~Counter() {
    // Affiche un message de destruction
}

void Counter::increment() {
    // Augmente _value de 1
}

void Counter::decrement() {
    // Diminue _value de 1
}

int Counter::getValue() const {
    // Retourne _value
}
```

**Fichier main.cpp :**
```cpp
#include "Counter.hpp"
#include <iostream>

int main() {
    Counter c;

    c.increment();
    c.increment();
    c.increment();

    std::cout << "Value: " << c.getValue() << std::endl;  // Doit afficher 3

    c.decrement();

    std::cout << "Value: " << c.getValue() << std::endl;  // Doit afficher 2

    return 0;
}
```

**Compilation :**
```bash
c++ -Wall -Wextra -Werror -std=c++98 main.cpp Counter.cpp -o counter
./counter
```

**Output attendu :**
```
Counter created
Value: 3
Value: 2
Counter destroyed
```

---

### Exercice 01 : Classe avec Paramètres

**Objectif :** Créer une classe `Rectangle` avec longueur et largeur.

**Fichier Rectangle.hpp :**
```cpp
#ifndef RECTANGLE_HPP
# define RECTANGLE_HPP

class Rectangle {
private:
    int _width;
    int _height;

public:
    Rectangle();                        // Constructeur par défaut (1x1)
    Rectangle(int w, int h);            // Constructeur avec paramètres
    ~Rectangle();

    int  getArea() const;               // Retourne width * height
    int  getPerimeter() const;          // Retourne 2 * (width + height)
    void setWidth(int w);
    void setHeight(int h);
};

#endif
```

**À toi de compléter Rectangle.cpp et main.cpp pour tester !**

**Tests attendus :**
```cpp
Rectangle r1;               // 1x1
Rectangle r2(5, 3);         // 5x3

std::cout << r1.getArea() << std::endl;       // 1
std::cout << r2.getArea() << std::endl;       // 15
std::cout << r2.getPerimeter() << std::endl;  // 16
```

---

### Exercice 02 : Encapsulation

**Objectif :** Créer une classe `BankAccount` avec protection.

**Fichier BankAccount.hpp :**
```cpp
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
```

**Règles :**
- Le solde ne peut jamais être négatif
- `deposit()` ne doit accepter que des montants > 0
- `withdraw()` retourne `false` si le solde est insuffisant

**À toi de compléter et tester !**

---

### Exercice 03 : Liste d'Initialisation

**Objectif :** Créer une classe `Point` (x, y) avec liste d'initialisation.

**Fichier Point.hpp :**
```cpp
#ifndef POINT_HPP
# define POINT_HPP

class Point {
private:
    const int _x;  // Constante = doit être initialisée dans la liste
    const int _y;

public:
    Point(int x, int y);
    ~Point();

    int getX() const;
    int getY() const;
    double distanceTo(const Point& other) const;  // Distance euclidienne
};

#endif
```

**Note importante :** Les attributs `const` DOIVENT être initialisés dans la liste d'initialisation.

**Exemple :**
```cpp
Point::Point(int x, int y) : _x(x), _y(y) {
    // _x et _y déjà initialisés
}
```

**Formule distance euclidienne :**
```
d = sqrt((x2-x1)² + (y2-y1)²)
```

Utilise `#include <cmath>` et `sqrt()`

---

### Exercice 04 : Classe avec Tableaux Dynamiques

**Objectif :** Créer une classe `IntArray` qui gère un tableau dynamique.

**Fichier IntArray.hpp :**
```cpp
#ifndef INTARRAY_HPP
# define INTARRAY_HPP

class IntArray {
private:
    int *_array;
    int  _size;

public:
    IntArray(int size);
    ~IntArray();

    void set(int index, int value);
    int  get(int index) const;
    int  getSize() const;
};

#endif
```

**Règles :**
- Le constructeur alloue `_size` entiers avec `new int[size]`
- Le destructeur libère avec `delete[] _array`
- `set()` et `get()` vérifient que l'index est valide

**Exemple d'utilisation :**
```cpp
IntArray arr(5);

arr.set(0, 10);
arr.set(1, 20);
arr.set(2, 30);

std::cout << arr.get(1) << std::endl;  // 20
```

---

### Exercice 05 : Chaînage avec `this`

**Objectif :** Créer une classe `StringBuilder` avec chaînage de méthodes.

**Fichier StringBuilder.hpp :**
```cpp
#ifndef STRINGBUILDER_HPP
# define STRINGBUILDER_HPP

# include <string>

class StringBuilder {
private:
    std::string _str;

public:
    StringBuilder();
    ~StringBuilder();

    StringBuilder& append(std::string text);
    StringBuilder& appendInt(int num);
    StringBuilder& clear();
    std::string    toString() const;
};

#endif
```

**L'idée :** Retourner `*this` permet le chaînage.

**Exemple d'utilisation :**
```cpp
StringBuilder sb;

sb.append("Hello")
  .append(" ")
  .append("World")
  .appendInt(42);

std::cout << sb.toString() << std::endl;  // "Hello World42"
```

**À toi de compléter !**

---

## 📚 7. Passer aux Exercices du Sujet

Maintenant que tu as fait ces 5 exercices, tu es prêt pour les exercices officiels :

### Ex00 : Megaphone

**Ce qu'il faut faire :**
- Prendre les arguments en ligne de commande
- Les convertir en majuscules
- Les afficher

**Hints :**
- `argc` et `argv` fonctionnent pareil qu'en C
- Pour convertir en majuscule : `toupper()` de `<cctype>`
- Si aucun argument : afficher "* LOUD AND UNBEARABLE FEEDBACK NOISE *"

---

### Ex01 : PhoneBook

**Ce qu'il faut faire :**
- Créer 2 classes : `PhoneBook` et `Contact`
- `PhoneBook` stocke 8 contacts max (tableau statique)
- Commandes : ADD, SEARCH, EXIT

**Structure recommandée :**

**Contact.hpp :**
```cpp
class Contact {
private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phoneNumber;
    std::string _darkestSecret;

public:
    Contact();
    ~Contact();

    void setFirstName(std::string fn);
    // ... autres setters

    std::string getFirstName() const;
    // ... autres getters
};
```

**PhoneBook.hpp :**
```cpp
class PhoneBook {
private:
    Contact _contacts[8];
    int     _count;
    int     _index;

public:
    PhoneBook();
    ~PhoneBook();

    void addContact();
    void searchContact();
    void displayContacts();
};
```

**Règles importantes :**
- Utilise `std::string`, pas `char *`
- Les champs ne peuvent pas être vides
- Pour l'affichage : colonnes de 10 caractères, alignées à droite
- Si texte > 10 chars : tronquer et mettre un point

---

## ✅ 8. Validation du Module CPP00

**Pour valider ce module, tu dois :**

1. ✅ Avoir complété les 5 exercices progressifs
2. ✅ Comprendre public/private/protected
3. ✅ Savoir créer constructeur et destructeur
4. ✅ Comprendre le pointeur `this`
5. ✅ Avoir terminé Ex00 et Ex01 du sujet

---

## 🎯 Checklist Finale

- [ ] Je sais créer une classe avec attributs privés
- [ ] Je sais faire un constructeur avec liste d'initialisation
- [ ] Je comprends pourquoi le destructeur est important
- [ ] Je sais faire des getters/setters
- [ ] Je comprends `const` sur les méthodes
- [ ] Je sais utiliser `this` quand nécessaire
- [ ] J'ai terminé Ex00 Megaphone
- [ ] J'ai terminé Ex01 PhoneBook

---

## 🔜 Prochaine Étape

**Module CPP01 : Mémoire & Références**
- Stack vs Heap en détail
- `new` / `delete` vs `malloc` / `free`
- Références vs Pointeurs
- Pointeurs sur membres de classe

**Prêt à continuer ? Passe au fichier CPP01.md ! 🚀**

---

*Module créé spécialement pour un étudiant 42 qui connaît le C.*
*Focus sur la compréhension progressive. Let's go! 💪*
