# MODULE CPP01 : Mémoire & Références

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre la différence entre Stack et Heap
- ✅ Utiliser `new` et `delete` correctement
- ✅ Maîtriser les références vs pointeurs
- ✅ Comprendre quand allouer sur le stack ou le heap
- ✅ Gérer la mémoire sans leaks
- ✅ Utiliser les pointeurs sur fonctions membres

**Durée estimée : 6-8 heures**

---

## 📖 1. Stack vs Heap : La Différence Fondamentale

### En C (ce que tu connais)

**Stack (automatique) :**
```c
void function() {
    int x = 42;           // Sur le stack
    char str[100];        // Sur le stack
    t_player player;      // Sur le stack

    // À la fin de la fonction, tout est détruit automatiquement
}
```

**Heap (dynamique) :**
```c
void function() {
    int *x = malloc(sizeof(int));          // Sur le heap
    char *str = malloc(100);               // Sur le heap
    t_player *player = malloc(sizeof(t_player));  // Sur le heap

    // Il FAUT free manuellement
    free(x);
    free(str);
    free(player);
}
```

---

### En C++ : Pareil mais avec `new` / `delete`

**Stack (automatique) :**
```cpp
void function() {
    int x = 42;           // Sur le stack
    std::string str;      // Sur le stack
    Player player;        // Sur le stack (constructeur appelé)

    // À la fin de la fonction, destructeurs appelés automatiquement
}
```

**Heap (dynamique) :**
```cpp
void function() {
    int *x = new int;              // Sur le heap
    std::string *str = new std::string;  // Sur le heap
    Player *player = new Player(); // Sur le heap (constructeur appelé)

    // Il FAUT delete manuellement
    delete x;
    delete str;
    delete player;  // Destructeur appelé
}
```

---

### Tableau Récapitulatif

| Aspect | Stack | Heap |
|--------|-------|------|
| **Allocation** | Automatique | Manuelle (`new`) |
| **Libération** | Automatique | Manuelle (`delete`) |
| **Taille** | Limitée (~8MB) | Grande (RAM disponible) |
| **Vitesse** | Rapide | Plus lent |
| **Durée de vie** | Jusqu'à la fin du scope | Jusqu'au `delete` |
| **Risque** | Stack overflow | Memory leak |

---

## 🆕 2. `new` et `delete` : Les Nouveaux malloc/free

### Différences Clés

**En C :**
```c
// Allocation
t_player *p = malloc(sizeof(t_player));

// Initialisation manuelle
p->health = 100;
p->name = strdup("Bob");

// Libération manuelle
free(p->name);
free(p);
```

**En C++ :**
```cpp
// Allocation + Constructeur appelé automatiquement
Player *p = new Player("Bob");

// Les attributs sont déjà initialisés par le constructeur

// Libération + Destructeur appelé automatiquement
delete p;
```

---

### Syntaxe de `new` et `delete`

**Un seul objet :**
```cpp
int *n = new int;           // Alloue 1 entier
int *x = new int(42);       // Alloue 1 entier initialisé à 42
Player *p = new Player();   // Alloue 1 Player (constructeur appelé)

delete n;
delete x;
delete p;  // Destructeur appelé
```

**Tableau d'objets :**
```cpp
int *arr = new int[10];         // Alloue 10 entiers
Player *players = new Player[5]; // Alloue 5 Players (constructeur appelé pour chacun)

delete[] arr;      // ⚠️ IMPORTANT : delete[] pour les tableaux
delete[] players;  // Destructeurs appelés pour chacun
```

---

### ⚠️ Erreur Classique : `delete` vs `delete[]`

**❌ MAUVAIS :**
```cpp
int *arr = new int[10];
delete arr;  // ❌ ERREUR : devrait être delete[]
```

**✅ BON :**
```cpp
int *arr = new int[10];
delete[] arr;  // ✅ Correct
```

**Règle simple :**
- `new` → `delete`
- `new[]` → `delete[]`

---

## 🔗 3. Références : Une Alternative aux Pointeurs

### C'est Quoi une Référence ?

**En C, tu utilises des pointeurs :**
```c
void modify(int *n) {
    *n = 42;  // Déréférencement avec *
}

int main() {
    int x = 10;
    modify(&x);  // Passer l'adresse avec &
    printf("%d\n", x);  // 42
}
```

**En C++, tu peux utiliser des références :**
```cpp
void modify(int& n) {
    n = 42;  // Pas besoin de *, la référence fait ça automatiquement
}

int main() {
    int x = 10;
    modify(x);  // Pas besoin de &, la référence le fait automatiquement
    std::cout << x << std::endl;  // 42
}
```

---

### Références vs Pointeurs

| Aspect | Pointeur | Référence |
|--------|----------|-----------|
| **Déclaration** | `int *ptr` | `int& ref` |
| **Initialisation** | Peut être NULL | DOIT être initialisée |
| **Modification** | Peut pointer ailleurs | Pointe toujours au même endroit |
| **Déréférencement** | `*ptr` | Automatique |
| **Syntaxe** | `ptr->member` | `ref.member` |

---

### Exemple Comparatif

**Avec Pointeur :**
```cpp
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int x = 5, y = 10;
    swap(&x, &y);  // Passer les adresses
    std::cout << x << " " << y << std::endl;  // 10 5
}
```

**Avec Référence (plus simple) :**
```cpp
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main() {
    int x = 5, y = 10;
    swap(x, y);  // Pas besoin de &
    std::cout << x << " " << y << std::endl;  // 10 5
}
```

---

### Quand Utiliser Références vs Pointeurs ?

**Utilise une RÉFÉRENCE quand :**
- ✅ La variable existe toujours (jamais NULL)
- ✅ Tu ne veux pas changer ce vers quoi ça pointe
- ✅ Syntaxe plus simple

**Utilise un POINTEUR quand :**
- ✅ La variable peut être NULL
- ✅ Tu veux pouvoir pointer vers différents objets
- ✅ Tu fais de l'allocation dynamique (`new`)

---

## 📝 4. Exercices Progressifs

### Exercice 00 : Stack vs Heap Simple

**Objectif :** Créer une classe et l'instancier sur stack et heap.

**Fichier Animal.hpp :**
```cpp
#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal {
private:
    std::string _name;
    std::string _type;

public:
    Animal(std::string name, std::string type);
    ~Animal();

    void makeSound() const;
    std::string getName() const;
};

#endif
```

**Fichier Animal.cpp :**
```cpp
#include "Animal.hpp"
#include <iostream>

Animal::Animal(std::string name, std::string type) : _name(name), _type(type) {
    std::cout << _type << " " << _name << " created" << std::endl;
}

Animal::~Animal() {
    std::cout << _type << " " << _name << " destroyed" << std::endl;
}

void Animal::makeSound() const {
    std::cout << _name << " makes a sound!" << std::endl;
}

std::string Animal::getName() const {
    return _name;
}
```

**Fichier main.cpp :**
```cpp
#include "Animal.hpp"
#include <iostream>

int main() {
    // Stack allocation
    {
        Animal dog("Rex", "Dog");
        dog.makeSound();
    }  // Destructeur appelé automatiquement ici

    std::cout << "---" << std::endl;

    // Heap allocation
    Animal *cat = new Animal("Whiskers", "Cat");
    cat->makeSound();
    delete cat;  // Destructeur appelé manuellement

    return 0;
}
```

**Output attendu :**
```
Dog Rex created
Rex makes a sound!
Dog Rex destroyed
---
Cat Whiskers created
Whiskers makes a sound!
Cat Whiskers destroyed
```

---

### Exercice 01 : Références

**Objectif :** Créer des fonctions utilisant références vs pointeurs.

**Fichier main.cpp :**
```cpp
#include <iostream>
#include <string>

// Fonction avec pointeur
void modifyWithPointer(std::string *str) {
    if (str)
        *str = "Modified by pointer";
}

// Fonction avec référence
void modifyWithReference(std::string& str) {
    str = "Modified by reference";
}

// Fonction affichant avec référence constante
void displayWithConstRef(const std::string& str) {
    std::cout << "String: " << str << std::endl;
    // str = "test";  // ❌ ERREUR : const
}

int main() {
    std::string text1 = "Original";
    std::string text2 = "Original";

    modifyWithPointer(&text1);
    std::cout << text1 << std::endl;  // Modified by pointer

    modifyWithReference(text2);
    std::cout << text2 << std::endl;  // Modified by reference

    displayWithConstRef(text1);

    return 0;
}
```

---

### Exercice 02 : Allocation de Tableau Dynamique

**Objectif :** Créer un tableau dynamique de strings.

**Fichier main.cpp :**
```cpp
#include <iostream>
#include <string>

int main() {
    int size;

    std::cout << "Enter array size: ";
    std::cin >> size;

    // Allocation dynamique
    std::string *array = new std::string[size];

    // Remplissage
    for (int i = 0; i < size; i++) {
        std::cout << "Enter string " << i << ": ";
        std::cin >> array[i];
    }

    // Affichage
    std::cout << "\nYour strings:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ": " << array[i] << std::endl;
    }

    // Libération
    delete[] array;

    return 0;
}
```

---

### Exercice 03 : Pointeur sur Référence

**Objectif :** Comprendre la différence entre pointeur et référence.

**Fichier main.cpp :**
```cpp
#include <iostream>

int main() {
    // Variable simple
    int value = 42;

    // Pointeur
    int *ptr = &value;
    std::cout << "Via pointer: " << *ptr << std::endl;

    // Référence
    int& ref = value;
    std::cout << "Via reference: " << ref << std::endl;

    // Modification via pointeur
    *ptr = 100;
    std::cout << "Value after ptr: " << value << std::endl;  // 100

    // Modification via référence
    ref = 200;
    std::cout << "Value after ref: " << value << std::endl;  // 200

    // Adresses
    std::cout << "Address of value: " << &value << std::endl;
    std::cout << "Address in ptr: " << ptr << std::endl;
    std::cout << "Address of ref: " << &ref << std::endl;
    // Les 3 adresses sont identiques !

    return 0;
}
```

---

### Exercice 04 : Classe avec Allocation Dynamique

**Objectif :** Créer une classe qui gère de la mémoire dynamique.

**Fichier StringArray.hpp :**
```cpp
#ifndef STRINGARRAY_HPP
# define STRINGARRAY_HPP

# include <string>

class StringArray {
private:
    std::string *_array;
    int          _size;

public:
    StringArray(int size);
    ~StringArray();

    void        set(int index, std::string value);
    std::string get(int index) const;
    int         getSize() const;
    void        display() const;
};

#endif
```

**À toi de compléter StringArray.cpp !**

**Règles :**
- Constructeur : alloue `_size` strings avec `new std::string[size]`
- Destructeur : libère avec `delete[] _array`
- `set()` et `get()` vérifient les index

---

## 📚 5. Concepts Avancés

### Pointeurs sur Fonctions Membres

**En C (pointeur sur fonction) :**
```c
void hello() {
    printf("Hello\n");
}

int main() {
    void (*ptr)() = &hello;
    ptr();  // Appelle hello()
}
```

**En C++ (pointeur sur méthode) :**
```cpp
class Test {
public:
    void hello() {
        std::cout << "Hello" << std::endl;
    }

    void world() {
        std::cout << "World" << std::endl;
    }
};

int main() {
    Test t;

    // Pointeur sur méthode
    void (Test::*ptr)() = &Test::hello;

    // Appel via pointeur
    (t.*ptr)();  // Hello

    // Changer de méthode
    ptr = &Test::world;
    (t.*ptr)();  // World
}
```

**Syntaxe complexe mais utile pour CPP01 Ex05 (Harl) !**

---

### Pourquoi les Pointeurs sur Membres ?

**Sans pointeur (avec if/else) :**
```cpp
void complain(std::string level) {
    if (level == "DEBUG")
        debug();
    else if (level == "INFO")
        info();
    else if (level == "WARNING")
        warning();
    else if (level == "ERROR")
        error();
}
```

**Avec pointeur (plus élégant) :**
```cpp
void complain(std::string level) {
    void (Harl::*functions[])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };

    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])();
            return;
        }
    }
}
```

---

## 📚 6. Les Exercices du Sujet

### Ex00 : BraiiiiiiinnnzzzZ (Zombies)

**Objectif :** Comprendre stack vs heap avec des Zombies.

**Structure :**
```cpp
class Zombie {
private:
    std::string _name;

public:
    Zombie(std::string name);
    ~Zombie();

    void announce() const;
};

// Fonctions à implémenter
Zombie* newZombie(std::string name);      // Crée sur heap
void    randomChump(std::string name);    // Crée sur stack
```

**Question clé :** Quand utiliser stack vs heap ?

**Réponse :**
- **Stack** (`randomChump`) : Le zombie meurt à la fin de la fonction
- **Heap** (`newZombie`) : Le zombie survit et est retourné

---

### Ex01 : Moar brainz! (Horde)

**Objectif :** Allouer un tableau de Zombies.

```cpp
Zombie* zombieHorde(int N, std::string name);
```

**Ce que tu dois faire :**
1. Allouer N Zombies : `new Zombie[N]`
2. Les initialiser avec le même nom
3. Retourner le pointeur
4. Dans le main : appeler `announce()` pour chacun
5. Tout libérer : `delete[] horde`

---

### Ex02 : HI THIS IS BRAIN

**Objectif :** Comprendre références vs pointeurs.

**Ce que tu dois faire :**
```cpp
std::string str = "HI THIS IS BRAIN";
std::string *stringPTR = &str;
std::string& stringREF = str;

// Afficher les adresses
std::cout << &str << std::endl;
std::cout << stringPTR << std::endl;
std::cout << &stringREF << std::endl;

// Afficher les valeurs
std::cout << str << std::endl;
std::cout << *stringPTR << std::endl;
std::cout << stringREF << std::endl;
```

**Les 3 adresses sont identiques !**

---

### Ex03 : Unnecessary violence (Weapon)

**Objectif :** Comprendre références vs pointeurs dans des classes.

**Classes à créer :**

```cpp
class Weapon {
private:
    std::string _type;

public:
    Weapon(std::string type);
    const std::string& getType() const;
    void setType(std::string type);
};

class HumanA {
private:
    std::string _name;
    Weapon&     _weapon;  // ← RÉFÉRENCE

public:
    HumanA(std::string name, Weapon& weapon);
    void attack() const;
};

class HumanB {
private:
    std::string _name;
    Weapon*     _weapon;  // ← POINTEUR

public:
    HumanB(std::string name);
    void setWeapon(Weapon& weapon);
    void attack() const;
};
```

**Différence :**
- **HumanA** : A TOUJOURS une arme (référence)
- **HumanB** : Peut ne PAS avoir d'arme (pointeur peut être NULL)

---

### Ex04 : Sed is for losers

**Objectif :** Manipuler des fichiers et strings.

**Ce que tu dois faire :**
1. Ouvrir un fichier
2. Remplacer toutes les occurrences de `s1` par `s2`
3. Écrire dans `<filename>.replace`

**Interdit :** `std::string::replace()`

**Hints :**
- Utilise `std::ifstream` et `std::ofstream`
- Utilise `std::string::find()` et `std::string::substr()`

---

### Ex05 : Harl 2.0

**Objectif :** Utiliser des pointeurs sur fonctions membres.

**Structure :**
```cpp
class Harl {
private:
    void debug();
    void info();
    void warning();
    void error();

public:
    void complain(std::string level);
};
```

**Implémentation de `complain()` avec pointeurs sur membres :**
```cpp
void Harl::complain(std::string level) {
    void (Harl::*functions[])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };

    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])();
            return;
        }
    }
}
```

---

### Ex06 : Harl filter

**Objectif :** Filtrer les messages de Harl avec `switch`.

**Ce que tu dois faire :**
- Prendre un niveau en argument
- Afficher ce niveau + tous les niveaux supérieurs

**Exemple :**
```bash
./harlFilter "WARNING"
```

**Output :**
```
[ WARNING ]
I think I deserve to have some extra bacon for free.
...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

**Utilise un `switch` pour cet exercice !**

---

## ✅ 7. Validation du Module CPP01

**Pour valider ce module, tu dois :**

1. ✅ Comprendre stack vs heap
2. ✅ Savoir utiliser `new` et `delete` (et `new[]` / `delete[]`)
3. ✅ Maîtriser références vs pointeurs
4. ✅ Savoir quand utiliser l'un ou l'autre
5. ✅ Avoir terminé Ex00 à Ex04 (Ex05-06 optionnels mais recommandés)

---

## 🎯 Checklist Finale

- [ ] Je comprends la différence stack vs heap
- [ ] Je sais quand utiliser `new` vs stack allocation
- [ ] Je n'oublie jamais `delete` après `new`
- [ ] Je connais la différence `delete` vs `delete[]`
- [ ] Je comprends les références
- [ ] Je sais quand utiliser référence vs pointeur
- [ ] J'ai terminé Ex00 (Zombies)
- [ ] J'ai terminé Ex01 (Horde)
- [ ] J'ai terminé Ex02 (Brain)
- [ ] J'ai terminé Ex03 (Weapon)
- [ ] J'ai terminé Ex04 (Sed)

---

## 🔜 Prochaine Étape

**Module CPP02 : Operators & Orthodox Canonical Form**
- Surcharge d'opérateurs
- Forme canonique orthodoxe
- Nombres à virgule fixe (fixed-point)
- Copy constructor et copy assignment

**Passe au fichier CPP02.md quand tu es prêt ! 🚀**

---

*Module créé spécialement pour un étudiant 42 qui connaît le C.*
*Focus sur la compréhension de la gestion mémoire en C++. Let's go! 💪*
