# MODULE CPP01 : Mémoire & Références

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre la différence entre Stack et Heap
- ✅ Utiliser `new` et `delete` correctement
- ✅ Maîtriser les références vs pointeurs
- ✅ Comprendre quand allouer sur le stack ou le heap
- ✅ Gérer la mémoire sans leaks
- ✅ Utiliser les pointeurs sur fonctions membres

**Durée estimée : 5-6 heures**

**⚠️ Ce module est optimisé PROJET ONLY - Pas d'exercices training, direct aux exos du sujet !**

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

## 📚 4. Les Exercices du Sujet - Guides Complets

---

## 📚 4. Les Exercices du Sujet - Guides Complets

### Ex00 : BraiiiiiiinnnzzzZ (Zombies) 🧟

#### 📋 Consignes du Sujet

Créer une classe `Zombie` avec :
- Attribut privé : `std::string _name`
- Méthode publique : `void announce(void)` qui affiche : `<name>: BraiiiiiiinnnzzzZ...`

**Implémenter 2 fonctions GLOBALES (hors classe) :**
1. `Zombie* newZombie(std::string name)` - Crée un zombie sur le **heap** et le retourne
2. `void randomChump(std::string name)` - Crée un zombie sur le **stack** qui s'annonce puis est détruit

**Question centrale :** Quand utiliser stack vs heap ?

**Objectif :** Comprendre la différence entre allocation stack et heap.

#### 📁 Fichiers à Créer

```
ex00/
├── Zombie.hpp
├── Zombie.cpp
├── newZombie.cpp
├── randomChump.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Classe Zombie avec constructeur/destructeur
- [ ] `announce()` affiche le bon format
- [ ] `newZombie()` retourne un zombie heap (doit être delete)
- [ ] `randomChump()` crée un zombie stack (détruit automatiquement)
- [ ] Messages de destruction affichés
- [ ] Pas de memory leaks

---

#### Structure de Base

**Zombie.hpp :**
```cpp
#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie(std::string name);
    ~Zombie();

    void announce() const;
};

// Fonctions à implémenter
Zombie* newZombie(std::string name);
void    randomChump(std::string name);

#endif
```

---

#### Zombie.cpp - Guide

```cpp
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : _name(name) {
    std::cout << _name << " created" << std::endl;
}

Zombie::~Zombie() {
    std::cout << _name << " destroyed" << std::endl;
}

void Zombie::announce() const {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
```

---

#### newZombie() - Heap Allocation

**Pourquoi heap ?**
- Le zombie doit **survivre à la fonction**
- On retourne le zombie pour l'utiliser ailleurs

```cpp
Zombie* newZombie(std::string name) {
    Zombie *zombie = new Zombie(name);  // Heap
    return zombie;  // Survit à la fonction
}

// Utilisation dans main
Zombie *z = newZombie("Foo");
z->announce();
delete z;  // ⚠️ IMPORTANT : libérer
```

---

#### randomChump() - Stack Allocation

**Pourquoi stack ?**
- Le zombie est utilisé **seulement dans la fonction**
- Pas besoin qu'il survive après

```cpp
void randomChump(std::string name) {
    Zombie zombie(name);  // Stack
    zombie.announce();
    // Zombie détruit automatiquement ici
}

// Utilisation dans main
randomChump("Bar");  // Créé et détruit automatiquement
```

---

#### Règle d'Or

**Stack** : L'objet meurt à la fin du scope → Utilise stack
**Heap** : L'objet doit survivre au scope → Utilise heap

---

### Ex01 : Moar brainz! (Horde) 🧟‍♂️🧟‍♀️

#### 📋 Consignes du Sujet

Implémenter une fonction qui crée une horde de N zombies :

```cpp
Zombie* zombieHorde(int N, std::string name);
```

**Ce qu'elle doit faire :**
- Allouer N zombies en une seule allocation : `new Zombie[N]`
- Initialiser chaque zombie avec le même nom
- Retourner un pointeur vers le premier zombie

**Dans le main :**
- Faire annoncer tous les zombies
- Libérer toute la horde avec `delete[]`

**Problème à résoudre :** Comment initialiser les zombies après `new Zombie[N]` ?

#### 📁 Fichiers à Créer

```
ex01/
├── Zombie.hpp
├── Zombie.cpp
├── zombieHorde.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Fonction `zombieHorde()` alloue N zombies d'un coup
- [ ] Tous les zombies ont le bon nom
- [ ] Tous annoncent correctement
- [ ] Libération avec `delete[]` (pas `delete` !)
- [ ] Pas de memory leaks
- [ ] Constructeur par défaut ajouté si nécessaire

---

#### Fonction à Implémenter

```cpp
Zombie* zombieHorde(int N, std::string name);
```

**Ce qu'elle doit faire :**
1. Allouer N Zombies d'un coup
2. Les initialiser avec le même nom
3. Retourner le pointeur vers le premier

---

#### zombieHorde.cpp - Guide

```cpp
#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
    // Allouer N zombies d'un coup
    Zombie *horde = new Zombie[N];
    //              ^^^^^^^^^^^^
    //              new[] pour un tableau

    // Problème : les zombies sont créés sans nom !
    // Il faut les renommer un par un

    for (int i = 0; i < N; i++) {
        // Initialiser chaque zombie
        // Mais comment ? Le constructeur a déjà été appelé !
    }

    return horde;
}
```

**❌ PROBLÈME : `new Zombie[N]` appelle le constructeur par défaut !**

---

#### Solution : Ajouter un Constructeur par Défaut

**Zombie.hpp :**
```cpp
class Zombie {
private:
    std::string _name;

public:
    Zombie();                    // ← Constructeur par défaut
    Zombie(std::string name);    // ← Constructeur avec paramètre
    ~Zombie();

    void announce() const;
    void setName(std::string name);  // ← Setter pour changer le nom
};
```

**Zombie.cpp :**
```cpp
Zombie::Zombie() : _name("") {
    // Constructeur par défaut (vide)
}

void Zombie::setName(std::string name) {
    _name = name;
}
```

---

#### zombieHorde.cpp - Version Finale

```cpp
Zombie* zombieHorde(int N, std::string name) {
    Zombie *horde = new Zombie[N];  // Constructeur par défaut appelé N fois

    for (int i = 0; i < N; i++) {
        horde[i].setName(name);  // On set le nom après coup
    }

    return horde;
}
```

---

#### Utilisation dans main.cpp

```cpp
int main() {
    int N = 5;
    Zombie *horde = zombieHorde(N, "Zombie");

    // Faire annoncer chaque zombie
    for (int i = 0; i < N; i++) {
        horde[i].announce();
    }

    // ⚠️ IMPORTANT : Libérer le tableau
    delete[] horde;  // delete[] pour les tableaux !
    //    ^^

    return 0;
}
```

**⚠️ PIÈGE :** `delete[]` et PAS `delete` pour les tableaux !

---

### Ex02 : HI THIS IS BRAIN 🧠

#### 📋 Consignes du Sujet

Créer un programme qui démontre que les références sont des alias.

**Variables à créer :**
```cpp
std::string str = "HI THIS IS BRAIN";
std::string *stringPTR = &str;     // Pointeur vers str
std::string& stringREF = str;       // Référence à str
```

**Afficher :**
1. L'adresse mémoire de `str`
2. L'adresse contenue dans `stringPTR`
3. L'adresse de `stringREF`
4. La valeur de `str`
5. La valeur pointée par `stringPTR`
6. La valeur référencée par `stringREF`

**Observation attendue :** Les 3 adresses doivent être identiques !

#### 📁 Fichiers à Créer

```
ex02/
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Affiche les 3 adresses (identiques)
- [ ] Affiche les 3 valeurs (identiques)
- [ ] Démontre que référence = alias

---

**C'est l'exercice le plus SIMPLE du module !**

---

#### Ce que tu Dois Faire

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "HI THIS IS BRAIN";

    std::string *stringPTR = &str;  // Pointeur
    std::string& stringREF = str;   // Référence

    // Afficher les adresses mémoire
    std::cout << "Address of str:    " << &str << std::endl;
    std::cout << "Address in PTR:    " << stringPTR << std::endl;
    std::cout << "Address of REF:    " << &stringREF << std::endl;

    std::cout << std::endl;

    // Afficher les valeurs
    std::cout << "Value of str:      " << str << std::endl;
    std::cout << "Value via PTR:     " << *stringPTR << std::endl;
    std::cout << "Value via REF:     " << stringREF << std::endl;

    return 0;
}
```

**Output :**
```
Address of str:    0x7ffc1234abcd
Address in PTR:    0x7ffc1234abcd
Address of REF:    0x7ffc1234abcd

Value of str:      HI THIS IS BRAIN
Value via PTR:     HI THIS IS BRAIN
Value via REF:     HI THIS IS BRAIN
```

**Les 3 adresses sont IDENTIQUES ! 🎯**

**Conclusion :** Une référence, c'est juste un alias (autre nom) pour la même variable.

---

### Ex03 : Unnecessary violence (Weapon) 🗡️

#### 📋 Consignes du Sujet

Créer un système d'armes avec 3 classes :

**1. Classe Weapon**
- Attribut privé : `std::string _type`
- `const std::string& getType()` - Retourne le type
- `void setType(std::string)` - Change le type

**2. Classe HumanA**
- Attributs : `std::string _name`, `Weapon& _weapon` (référence !)
- Constructeur : `HumanA(std::string name, Weapon& weapon)`
- `void attack()` - Affiche : `<name> attacks with their <weapon_type>`

**3. Classe HumanB**
- Attributs : `std::string _name`, `Weapon* _weapon` (pointeur !)
- Constructeur : `HumanB(std::string name)` (sans arme)
- `void setWeapon(Weapon& weapon)` - Donne une arme
- `void attack()` - Affiche l'attaque (ou "no weapon")

**Question centrale :** Pourquoi HumanA utilise une référence et HumanB un pointeur ?

#### 📁 Fichiers à Créer

```
ex03/
├── Weapon.hpp
├── Weapon.cpp
├── HumanA.hpp
├── HumanA.cpp
├── HumanB.hpp
├── HumanB.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] HumanA a TOUJOURS une arme (référence)
- [ ] HumanB peut être sans arme (pointeur NULL)
- [ ] Référence initialisée dans la liste d'initialisation
- [ ] Changement de type d'arme affecte les deux humains
- [ ] Test du sujet fonctionne correctement

---

**C'est l'exercice LE PLUS IMPORTANT du module !**

---

#### Classes à Créer

**Weapon.hpp :**
```cpp
#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon {
private:
    std::string _type;

public:
    Weapon(std::string type);

    const std::string& getType() const;
    void setType(std::string type);
};

#endif
```

**Weapon.cpp :**
```cpp
#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) {}

const std::string& Weapon::getType() const {
    return _type;  // Retourne une référence (pas de copie)
}

void Weapon::setType(std::string type) {
    _type = type;
}
```

---

#### HumanA - Toujours Armé (Référence)

**HumanA.hpp :**
```cpp
#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA {
private:
    std::string _name;
    Weapon&     _weapon;  // ← RÉFÉRENCE

public:
    HumanA(std::string name, Weapon& weapon);
    void attack() const;
};

#endif
```

**Pourquoi une référence ?**
- HumanA a **TOUJOURS** une arme (donné dans le constructeur)
- L'arme ne peut **PAS être NULL**
- L'arme ne **CHANGE JAMAIS** (toujours la même référence)

**HumanA.cpp :**
```cpp
#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon& weapon)
    : _name(name), _weapon(weapon) {
    // _weapon doit être initialisé dans la liste !
}

void HumanA::attack() const {
    std::cout << _name << " attacks with their "
              << _weapon.getType() << std::endl;
}
```

**⚠️ IMPORTANT :** Une référence DOIT être initialisée dans la liste d'initialisation !

---

#### HumanB - Peut Être Désarmé (Pointeur)

**HumanB.hpp :**
```cpp
#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB {
private:
    std::string _name;
    Weapon*     _weapon;  // ← POINTEUR

public:
    HumanB(std::string name);
    void setWeapon(Weapon& weapon);
    void attack() const;
};

#endif
```

**Pourquoi un pointeur ?**
- HumanB peut **NE PAS avoir d'arme** au début
- L'arme peut être **NULL**
- On peut **changer d'arme** plus tard

**HumanB.cpp :**
```cpp
#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
    // Pas d'arme au début
}

void HumanB::setWeapon(Weapon& weapon) {
    _weapon = &weapon;  // Stocke l'adresse
}

void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their "
                  << _weapon->getType() << std::endl;
    else
        std::cout << _name << " has no weapon!" << std::endl;
}
```

---

#### Test du Sujet

```cpp
int main() {
    {
        Weapon club = Weapon("crude spiked club");

        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");

        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }

    return 0;
}
```

**Output attendu :**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

---

#### Règle à Retenir

**Référence :** Quand l'objet existe TOUJOURS (jamais NULL)
**Pointeur :** Quand l'objet peut être NULL ou changer

---

### Ex04 : Sed is for losers 📝

#### 📋 Consignes du Sujet

Créer un programme qui remplace toutes les occurrences d'une chaîne par une autre.

**Paramètres :**
```bash
./replace <filename> <s1> <s2>
```

**Comportement :**
1. Ouvre le fichier `<filename>`
2. Remplace TOUTES les occurrences de `<s1>` par `<s2>`
3. Écrit le résultat dans `<filename>.replace`

**Restrictions :**
- ❌ **Interdit** d'utiliser `std::string::replace()`
- ❌ Pas de fonctions C (fopen, fgets, etc.)
- ✅ Utiliser `std::ifstream` et `std::ofstream`
- ✅ Utiliser `std::string::find()` et `std::string::substr()`

**Exemple :**
```bash
echo "Hello world Hello" > test.txt
./replace test.txt Hello Bonjour
cat test.txt.replace
# Output: Bonjour world Bonjour
```

#### 📁 Fichiers à Créer

```
ex04/
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Prend exactement 3 arguments
- [ ] Gère les erreurs (fichier inexistant, etc.)
- [ ] Remplace TOUTES les occurrences (pas juste la première)
- [ ] Crée bien `<filename>.replace`
- [ ] N'utilise PAS `std::string::replace()`
- [ ] Gère les cas limites (s1 vide, s1 non trouvé, etc.)

---

#### Ce que tu Dois Faire

**Programme qui prend 3 paramètres :**
```bash
./replace <filename> <s1> <s2>
```

**Comportement :**
1. Ouvre `<filename>`
2. Remplace TOUTES les occurrences de `<s1>` par `<s2>`
3. Écrit le résultat dans `<filename>.replace`

---

#### Gestion des Fichiers en C++

**Lecture :**
```cpp
#include <fstream>

std::ifstream infile("input.txt");
//            ^^^
//            input file stream

if (!infile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
}

std::string line;
while (std::getline(infile, line)) {
    // Traiter la ligne
}

infile.close();
```

**Écriture :**
```cpp
std::ofstream outfile("output.txt");
//            ^^^
//            output file stream

outfile << "Hello" << std::endl;
outfile << "World" << std::endl;

outfile.close();
```

---

#### Remplacer une String

**Sans `replace()`, utilise `find()` et `substr()` :**

```cpp
std::string replaceAll(std::string str, std::string s1, std::string s2) {
    std::string result = "";
    size_t pos = 0;
    size_t found;

    while ((found = str.find(s1, pos)) != std::string::npos) {
        // Ajoute tout avant s1
        result += str.substr(pos, found - pos);
        // Ajoute s2 à la place de s1
        result += s2;
        // Avance après s1
        pos = found + s1.length();
    }

    // Ajoute le reste
    result += str.substr(pos);

    return result;
}
```

---

#### Structure du Programme

**main.cpp :**
```cpp
#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(std::string str, std::string s1, std::string s2) {
    // Implémentation ci-dessus
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    // Ouvrir le fichier
    std::ifstream infile(filename.c_str());
    if (!infile.is_open()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return 1;
    }

    // Créer le fichier de sortie
    std::ofstream outfile((filename + ".replace").c_str());

    // Lire ligne par ligne
    std::string line;
    while (std::getline(infile, line)) {
        outfile << replaceAll(line, s1, s2) << std::endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
```

**⚠️ `.c_str()` nécessaire en C++98 pour les streams !**

---

#### Test

**Créer un fichier test.txt :**
```
Hello world
Hello everyone
Hello Hello
```

**Exécuter :**
```bash
./replace test.txt Hello Bonjour
```

**test.txt.replace :**
```
Bonjour world
Bonjour everyone
Bonjour Bonjour
```

---

### Ex05 : Harl 2.0 🗣️

#### 📋 Consignes du Sujet

Créer une classe `Harl` qui se plaint à différents niveaux.

**Méthodes privées (4 niveaux de plainte) :**
- `void debug()` - Message de debug
- `void info()` - Message informatif
- `void warning()` - Message d'avertissement
- `void error()` - Message d'erreur

**Méthode publique :**
```cpp
void complain(std::string level);
```

**Contrainte IMPORTANTE :**
- ❌ **Interdit** d'utiliser une "forest of if/else if/else"
- ✅ **Obligatoire** d'utiliser un tableau de pointeurs sur fonctions membres

**Exemple d'utilisation :**
```cpp
Harl harl;
harl.complain("DEBUG");   // Affiche le message debug
harl.complain("WARNING"); // Affiche le message warning
```

#### 📁 Fichiers à Créer

```
ex05/
├── Harl.hpp
├── Harl.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] 4 méthodes privées (debug, info, warning, error)
- [ ] `complain()` utilise un tableau de pointeurs sur membres
- [ ] PAS de if/else if/else (seulement une boucle)
- [ ] Messages corrects pour chaque niveau
- [ ] Gère les niveaux invalides

---

**C'est l'exercice le PLUS TECHNIQUE du module !**

---

#### Classe Harl

**Harl.hpp :**
```cpp
#ifndef HARL_HPP
# define HARL_HPP

# include <string>

class Harl {
private:
    void debug();
    void info();
    void warning();
    void error();

public:
    void complain(std::string level);
};

#endif
```

---

#### Implémentation des Méthodes Privées

**Harl.cpp :**
```cpp
#include "Harl.hpp"
#include <iostream>

void Harl::debug() {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::info() {
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning() {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error() {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}
```

---

#### La Méthode complain() - SANS Pointeurs (Interdit)

**❌ Version avec if/else (le sujet l'interdit) :**
```cpp
void Harl::complain(std::string level) {
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

**Le sujet dit :** "without using a forest of if/else if/else"

---

#### La Méthode complain() - AVEC Pointeurs (Correct)

**✅ Version avec pointeurs sur fonctions membres :**

```cpp
void Harl::complain(std::string level) {
    // Tableau de pointeurs sur méthodes
    void (Harl::*functions[])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };

    // Tableau des noms correspondants
    std::string levels[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };

    // Chercher le niveau et appeler la fonction
    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])();  // Appel via pointeur
            return;
        }
    }
}
```

---

#### Explication de la Syntaxe

**Déclaration du tableau de pointeurs :**
```cpp
void (Harl::*functions[])()
//   ^^^^^  ^           ^^
//   |      |           Pas de paramètres
//   |      Tableau de pointeurs
//   Retourne void
```

**Initialisation :**
```cpp
functions[0] = &Harl::debug;
functions[1] = &Harl::info;
//             ^^^^^
//             Adresse de la méthode
```

**Appel :**
```cpp
(this->*functions[i])();
//^^^^  ^          ^^
//|     Déréférence Appel
//Objet
```

---

#### main.cpp pour Tester

```cpp
#include "Harl.hpp"

int main() {
    Harl harl;

    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    harl.complain("UNKNOWN");  // Ne fait rien

    return 0;
}
```

---

### Ex06 : Harl filter 🎚️

#### 📋 Consignes du Sujet

Créer un programme qui filtre les messages de Harl selon un niveau minimum.

**Paramètre :**
```bash
./harlFilter <level>
```

**Comportement :**
- Affiche le niveau demandé + TOUS les niveaux supérieurs
- Utilise un `switch` avec fall-through intentionnel (pas de `break`)

**Niveaux (ordre croissant) :**
1. DEBUG
2. INFO
3. WARNING
4. ERROR

**Exemple :**
```bash
./harlFilter "WARNING"
# Affiche WARNING + ERROR

./harlFilter "DEBUG"
# Affiche DEBUG + INFO + WARNING + ERROR
```

**Contrainte :**
- ✅ Utiliser un `switch` sans `break` (fall-through)

#### 📁 Fichiers à Créer

```
ex06/
├── Harl.hpp
├── Harl.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Prend exactement 1 argument
- [ ] Affiche le niveau + niveaux supérieurs
- [ ] Utilise `switch` avec fall-through
- [ ] Gère les niveaux invalides
- [ ] Messages affichés dans le bon ordre

---

**⚠️ Ex06 est OPTIONNEL mais utilise `switch` (nouveau concept) !**

---

#### Ce que tu Dois Faire

**Programme qui prend un niveau en paramètre :**
```bash
./harlFilter "WARNING"
```

**Affiche ce niveau + tous les niveaux supérieurs :**
```
[ WARNING ]
I think I deserve to have some extra bacon for free...

[ ERROR ]
This is unacceptable! I want to speak to the manager now.
```

---

#### Utilisation du switch

**main.cpp :**
```cpp
#include "Harl.hpp"
#include <iostream>

int getLevelIndex(std::string level) {
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; i++) {
        if (level == levels[i])
            return i;
    }
    return -1;  // Niveau inconnu
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./harlFilter <level>" << std::endl;
        return 1;
    }

    Harl harl;
    int level = getLevelIndex(argv[1]);

    switch (level) {
        case 0:  // DEBUG
            harl.complain("DEBUG");
            // Pas de break : continue
        case 1:  // INFO
            harl.complain("INFO");
        case 2:  // WARNING
            harl.complain("WARNING");
        case 3:  // ERROR
            harl.complain("ERROR");
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }

    return 0;
}
```

**⚠️ Pas de `break` entre les cases → Fall-through intentionnel !**

---

## ✅ 5. Validation du Module CPP01

---

## ✅ 5. Validation du Module CPP01

**Pour valider ce module, tu dois :**

1. ✅ Comprendre stack vs heap (Ex00)
2. ✅ Savoir utiliser `new[]` et `delete[]` (Ex01)
3. ✅ Maîtriser références vs pointeurs (Ex02-03)
4. ✅ Manipuler fichiers et strings (Ex04)
5. ✅ Utiliser pointeurs sur fonctions membres (Ex05)
6. ⭕ Ex06 optionnel mais recommandé pour le `switch`

---

## 🎯 Checklist Finale

- [ ] Ex00 : Zombies fonctionnent (stack et heap)
- [ ] Ex01 : zombieHorde() alloue et libère correctement
- [ ] Ex02 : Les 3 adresses sont identiques
- [ ] Ex03 : HumanA utilise référence, HumanB utilise pointeur
- [ ] Ex04 : replace() remplace toutes les occurrences
- [ ] Ex05 : complain() utilise des pointeurs sur membres
- [ ] Pas de memory leaks (teste avec valgrind)

---

## 🔜 Prochaine Étape

**Module CPP02 : Operators & Orthodox Canonical Form**
- Surcharge d'opérateurs (`+`, `-`, `<<`, etc.)
- Forme canonique orthodoxe (OCF)
- Copy constructor et copy assignment operator
- Nombres à virgule fixe (fixed-point)

**Passe au fichier CPP02.md ! 🚀**

---

*Module optimisé projet-only pour un étudiant 42 pressé par le temps.*
*Focus sur les exos du sujet, pas de training inutile. Let's go! 💪*

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
