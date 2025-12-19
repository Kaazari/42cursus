# MODULE CPP03 : Inheritance (Héritage)

## 🎯 Objectifs du Module

À la fin de ce module, tu seras capable de :
- ✅ Comprendre l'héritage de classes
- ✅ Créer des classes dérivées
- ✅ Gérer les chaînes de construction/destruction
- ✅ Utiliser `protected` correctement
- ✅ Comprendre quand utiliser l'héritage

**Durée estimée : 6 heures**

**Ce module est PLUS SIMPLE que CPP02, c'est un bon break ! 😄**

---

## 📖 1. L'Héritage - C'est Quoi ?

### Principe de Base

**En C, tu ferais :**
```c
typedef struct s_animal {
    char *name;
    int   health;
} t_animal;

typedef struct s_dog {
    t_animal animal;  // Contient un animal
    char    *breed;
} t_dog;
```

**En C++, c'est plus propre :**
```cpp
class Animal {
protected:
    std::string _name;
    int         _health;

public:
    Animal(std::string name);
    void eat();
};

class Dog : public Animal {  // Dog hérite de Animal
private:
    std::string _breed;

public:
    Dog(std::string name, std::string breed);
    void bark();  // Méthode spécifique à Dog
};
```

**Dog a TOUTES les méthodes et attributs de Animal + ses propres méthodes !**

---

### Vocabulaire

```cpp
class Animal { ... };        // Classe MÈRE (base class)
class Dog : public Animal    // Classe FILLE (derived class)
```

**Dog hérite de Animal :**
- ✅ Dog a `_name` et `_health` (de Animal)
- ✅ Dog a `eat()` (de Animal)
- ✅ Dog a `_breed` et `bark()` (propres à Dog)

---

### Public, Protected, Private avec Héritage

```cpp
class Animal {
private:
    int _secret;      // ❌ Pas accessible dans Dog

protected:
    int _internal;    // ✅ Accessible dans Dog

public:
    int visible;      // ✅ Accessible partout
};
```

**Tableau récap :**

| Niveau | Classe mère | Classe fille | Extérieur |
|--------|-------------|--------------|-----------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

**Règle d'or :** Utilise `protected` pour ce que les classes filles doivent pouvoir modifier.

---

## 🏗️ 2. Chaînes de Construction/Destruction

### Ordre de Construction

**Quand tu crées un objet dérivé :**

1. Constructeur de la classe MÈRE
2. Constructeur de la classe FILLE

```cpp
class Animal {
public:
    Animal() {
        std::cout << "Animal created" << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog() {
        std::cout << "Dog created" << std::endl;
    }
};

// Utilisation
Dog dog;
// Output:
// Animal created
// Dog created
```

---

### Ordre de Destruction

**Quand tu détruis un objet dérivé (INVERSE de la construction) :**

1. Destructeur de la classe FILLE
2. Destructeur de la classe MÈRE

```cpp
class Animal {
public:
    ~Animal() {
        std::cout << "Animal destroyed" << std::endl;
    }
};

class Dog : public Animal {
public:
    ~Dog() {
        std::cout << "Dog destroyed" << std::endl;
    }
};

// Utilisation
{
    Dog dog;
}
// Output:
// Dog destroyed
// Animal destroyed
```

**⚠️ IMPORTANT : La destruction se fait dans l'ordre INVERSE !**

---

### Appeler le Constructeur de la Classe Mère

```cpp
class Animal {
protected:
    std::string _name;
    int         _health;

public:
    Animal(std::string name, int health)
        : _name(name), _health(health) {
        std::cout << "Animal " << _name << " created" << std::endl;
    }
};

class Dog : public Animal {
private:
    std::string _breed;

public:
    Dog(std::string name, int health, std::string breed)
        : Animal(name, health),  // ← Appel du constructeur mère
          _breed(breed) {
        std::cout << "Dog " << _name << " created" << std::endl;
    }
};
```

**La classe fille DOIT appeler le constructeur de la mère dans sa liste d'initialisation !**

---

## 📝 3. Les Exercices du Sujet - Guides Complets

### Ex00 : Aaaaand... OPEN! (ClapTrap)

#### 📋 Consignes du Sujet

Créer une classe `ClapTrap` qui représente un robot de combat.

**Attributs privés :**
- `std::string _name`
- `unsigned int _hitPoints` (10 au départ)
- `unsigned int _energyPoints` (10 au départ)
- `unsigned int _attackDamage` (0 au départ)

**Méthodes publiques :**
- `ClapTrap(std::string name)` - Constructeur
- `~ClapTrap()` - Destructeur
- `void attack(const std::string& target)` - Attaque (coûte 1 EP)
- `void takeDamage(unsigned int amount)` - Prend des dégâts
- `void beRepaired(unsigned int amount)` - Se répare (coûte 1 EP)

**Règles :**
- Attaquer ou réparer coûte 1 point d'énergie
- Sans énergie ou HP : ne peut plus rien faire
- Messages spécifiques à afficher pour chaque action

**Chaque action doit afficher un message du type :**
```
ClapTrap <name> attacks <target>, causing <damage> points of damage!
```

#### 📁 Fichiers à Créer

```
ex00/
├── ClapTrap.hpp
├── ClapTrap.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Attributs initialisés correctement (10 HP, 10 EP, 0 ATK)
- [ ] attack() coûte 1 EP et affiche un message
- [ ] takeDamage() réduit les HP
- [ ] beRepaired() coûte 1 EP et restaure des HP
- [ ] Ne peut pas agir sans HP ou EP
- [ ] Constructeur/destructeur affichent des messages

**C'est le robot de base, les exos suivants créeront des variantes !**

---

#### ClapTrap.hpp

```cpp
#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>

class ClapTrap {
protected:  // ← protected pour que les classes filles y accèdent
    std::string _name;
    int         _hitPoints;
    int         _energyPoints;
    int         _attackDamage;

public:
    ClapTrap(std::string name);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};

#endif
```

**⚠️ Utilise `protected` et pas `private` pour que ScavTrap/FragTrap puissent modifier les attributs !**

---

#### ClapTrap.cpp

```cpp
#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(std::string name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << _name << " constructed" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << _name << " destroyed" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (_energyPoints == 0 || _hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " can't attack!" << std::endl;
        return;
    }

    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target
              << ", causing " << _attackDamage << " points of damage!"
              << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    _hitPoints -= amount;
    if (_hitPoints < 0)
        _hitPoints = 0;

    std::cout << "ClapTrap " << _name << " takes " << amount
              << " damage! HP: " << _hitPoints << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (_energyPoints == 0 || _hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " can't repair!" << std::endl;
        return;
    }

    _energyPoints--;
    _hitPoints += amount;

    std::cout << "ClapTrap " << _name << " repairs " << amount
              << " HP! HP: " << _hitPoints << std::endl;
}
```

---

#### main.cpp pour Tester

```cpp
#include "ClapTrap.hpp"

int main() {
    ClapTrap clap("CT-01");

    clap.attack("Enemy");
    clap.takeDamage(5);
    clap.beRepaired(3);

    return 0;
}
```

**Output :**
```
ClapTrap CT-01 constructed
ClapTrap CT-01 attacks Enemy, causing 0 points of damage!
ClapTrap CT-01 takes 5 damage! HP: 5
ClapTrap CT-01 repairs 3 HP! HP: 8
ClapTrap CT-01 destroyed
```

---

### Ex01 : Serena, my love! (ScavTrap)

#### 📋 Consignes du Sujet

Créer une classe `ScavTrap` qui hérite de `ClapTrap` avec des attributs différents.

**Héritage :**
```cpp
class ScavTrap : public ClapTrap
```

**Attributs spécifiques (initialisés différemment) :**
- `_hitPoints = 100` (au lieu de 10)
- `_energyPoints = 50` (au lieu de 10)
- `_attackDamage = 20` (au lieu de 0)
- `_name` : passé en paramètre

**Méthodes :**
- `ScavTrap(std::string name)` - Constructeur (appelle ClapTrap(name))
- `~ScavTrap()` - Destructeur
- `void attack(const std::string& target)` - REDÉFINIT attack() avec message différent
- `void guardGate()` - Nouvelle méthode spécifique à ScavTrap

**Messages obligatoires :**
- Constructeur : "ScavTrap <n> is born!"
- Destructeur : "ScavTrap <n> is destroyed!"
- guardGate() : "ScavTrap is now in Gate keeper mode"

**⚠️ Ordre d'appel des constructeurs/destructeurs important !**

#### 📁 Fichiers à Créer

```
ex01/
├── ClapTrap.hpp
├── ClapTrap.cpp
├── ScavTrap.hpp
├── ScavTrap.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] ScavTrap hérite de ClapTrap
- [ ] Attributs initialisés différemment (100 HP, 50 EP, 20 ATK)
- [ ] attack() redéfinie avec message ScavTrap
- [ ] guardGate() fonctionne
- [ ] Constructeurs appelés dans le bon ordre (ClapTrap puis ScavTrap)
- [ ] Destructeurs appelés dans le bon ordre (ScavTrap puis ClapTrap)

---

#### ScavTrap.hpp

```cpp
#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
    ScavTrap(std::string name);
    ~ScavTrap();

    void attack(const std::string& target);  // ← Redéfinit attack()
    void guardGate();                        // ← Nouvelle méthode
};

#endif
```

---

#### ScavTrap.cpp

```cpp
#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    // Redéfinit les stats (différentes de ClapTrap)
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;

    std::cout << "ScavTrap " << _name << " constructed" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << _name << " destroyed" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (_energyPoints == 0 || _hitPoints == 0) {
        std::cout << "ScavTrap " << _name << " can't attack!" << std::endl;
        return;
    }

    _energyPoints--;
    std::cout << "ScavTrap " << _name << " attacks " << target
              << ", causing " << _attackDamage << " points of damage!"
              << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode"
              << std::endl;
}
```

---

#### Test de la Chaîne de Construction

```cpp
#include "ScavTrap.hpp"

int main() {
    ScavTrap scav("SC-01");

    scav.attack("Enemy");
    scav.guardGate();

    return 0;
}
```

**Output :**
```
ClapTrap SC-01 constructed       ← Constructeur mère
ScavTrap SC-01 constructed       ← Constructeur fille
ScavTrap SC-01 attacks Enemy, causing 20 points of damage!
ScavTrap SC-01 is now in Gate keeper mode
ScavTrap SC-01 destroyed         ← Destructeur fille
ClapTrap SC-01 destroyed         ← Destructeur mère
```

**⚠️ Ordre : Mère → Fille (construction), Fille → Mère (destruction)**

---

### Ex02 : Repetitive work (FragTrap)

#### 📋 Consignes du Sujet

Créer une classe `FragTrap` qui hérite de `ClapTrap` (encore une variante !).

**Héritage :**
```cpp
class FragTrap : public ClapTrap
```

**Attributs spécifiques :**
- `_hitPoints = 100`
- `_energyPoints = 100`
- `_attackDamage = 30`
- `_name` : passé en paramètre

**Méthodes :**
- `FragTrap(std::string name)` - Constructeur
- `~FragTrap()` - Destructeur
- `void highFivesGuys()` - Nouvelle méthode (demande un high five)

**Messages obligatoires :**
- Constructeur : "FragTrap <n> is born!"
- Destructeur : "FragTrap <n> is destroyed!"
- highFivesGuys() : "FragTrap <n> requests a positive high five!"

**Note :** FragTrap n'a PAS besoin de redéfinir attack() (utilise celle de ClapTrap).

#### 📁 Fichiers à Créer

```
ex02/
├── ClapTrap.hpp
├── ClapTrap.cpp
├── ScavTrap.hpp
├── ScavTrap.cpp
├── FragTrap.hpp
├── FragTrap.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] FragTrap hérite de ClapTrap
- [ ] Attributs initialisés différemment (100 HP, 100 EP, 30 ATK)
- [ ] highFivesGuys() affiche le bon message
- [ ] Utilise attack() de ClapTrap (pas de redéfinition)
- [ ] Chaîne constructeur/destructeur correcte

**C'est exactement comme Ex01 mais avec des stats différentes !**

---

#### FragTrap.hpp

```cpp
#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
    FragTrap(std::string name);
    ~FragTrap();

    void highFivesGuys();  // ← Nouvelle méthode
};

#endif
```

---

#### FragTrap.cpp

```cpp
#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;

    std::cout << "FragTrap " << _name << " constructed" << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap " << _name << " destroyed" << std::endl;
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << _name << " requests a high five! ✋"
              << std::endl;
}
```

---

#### Comparaison des Stats

| Classe | HP | Energy | Damage |
|--------|----|----|--------|
| **ClapTrap** | 10 | 10 | 0 |
| **ScavTrap** | 100 | 50 | 20 |
| **FragTrap** | 100 | 100 | 30 |

---

### Ex03 : Now it's weird! (DiamondTrap)

#### 📋 Consignes du Sujet

Créer une classe `DiamondTrap` avec héritage multiple de `ScavTrap` et `FragTrap`.

**Problème du diamant :**
```
        ClapTrap
       /        \
   ScavTrap   FragTrap
       \        /
      DiamondTrap  ← Hérite de ClapTrap deux fois !
```

**Solution : Héritage virtuel**
```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
class DiamondTrap : public ScavTrap, public FragTrap { ... };
```

**Attributs de DiamondTrap :**
- `std::string _name` (son propre nom)
- `_hitPoints` de FragTrap (100)
- `_energyPoints` de ScavTrap (50)
- `_attackDamage` de FragTrap (30)
- ClapTrap::_name = `<name>_clap_name`

**Méthodes :**
- `DiamondTrap(std::string name)` - Constructeur
- `~DiamondTrap()` - Destructeur
- `void attack(const std::string& target)` - Utilise ScavTrap::attack()
- `void whoAmI()` - Affiche son nom et celui de ClapTrap

**⚠️ Attention : Gestion de deux attributs _name !**

#### 📁 Fichiers à Créer

```
ex03/
├── ClapTrap.hpp
├── ClapTrap.cpp
├── ScavTrap.hpp (avec virtual)
├── ScavTrap.cpp
├── FragTrap.hpp (avec virtual)
├── FragTrap.cpp
├── DiamondTrap.hpp
├── DiamondTrap.cpp
├── main.cpp
└── Makefile
```

#### 🎯 Critères de Validation

- [ ] Héritage virtuel implémenté correctement
- [ ] DiamondTrap a ses propres attributs mixés
- [ ] whoAmI() affiche les deux noms
- [ ] attack() utilise celle de ScavTrap
- [ ] Pas de double construction de ClapTrap
- [ ] Constructeurs/destructeurs dans le bon ordre

**⚠️ Ex03 est OPTIONNEL et COMPLEXE ! Skip si tu manques de temps !**

---

#### Le Diamond Problem

```
        ClapTrap
       /        \
   ScavTrap   FragTrap
       \        /
      DiamondTrap
```

**Problème :** DiamondTrap hérite de ClapTrap deux fois (via ScavTrap ET FragTrap) !

**Solution :** Héritage virtuel

---

#### ClapTrap.hpp Modifié

```cpp
class ClapTrap {
    // ... (pareil)
};
```

**Pas de modification nécessaire pour ClapTrap !**

---

#### ScavTrap.hpp Modifié

```cpp
class ScavTrap : virtual public ClapTrap {  // ← virtual !
    // ...
};
```

---

#### FragTrap.hpp Modifié

```cpp
class FragTrap : virtual public ClapTrap {  // ← virtual !
    // ...
};
```

---

#### DiamondTrap.hpp

```cpp
#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string _name;  // ← Nom du DiamondTrap

public:
    DiamondTrap(std::string name);
    ~DiamondTrap();

    void whoAmI();

    using ScavTrap::attack;  // ← Utilise attack() de ScavTrap
};

#endif
```

---

#### DiamondTrap.cpp

```cpp
#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap(std::string name)
    : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name) {
    // Stats : mélange de ScavTrap et FragTrap
    _hitPoints = FragTrap::_hitPoints;       // 100 de FragTrap
    _energyPoints = ScavTrap::_energyPoints; // 50 de ScavTrap
    _attackDamage = FragTrap::_attackDamage; // 30 de FragTrap

    std::cout << "DiamondTrap " << _name << " constructed" << std::endl;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << _name << " destroyed" << std::endl;
}

void DiamondTrap::whoAmI() {
    std::cout << "I am DiamondTrap " << _name
              << " and my ClapTrap name is " << ClapTrap::_name
              << std::endl;
}
```

---

#### Test

```cpp
#include "DiamondTrap.hpp"

int main() {
    DiamondTrap diamond("DT-01");

    diamond.whoAmI();
    diamond.attack("Enemy");

    return 0;
}
```

**Output :**
```
ClapTrap DT-01_clap_name constructed
ScavTrap DT-01_clap_name constructed
FragTrap DT-01_clap_name constructed
DiamondTrap DT-01 constructed
I am DiamondTrap DT-01 and my ClapTrap name is DT-01_clap_name
ScavTrap DT-01_clap_name attacks Enemy, causing 30 points of damage!
DiamondTrap DT-01 destroyed
FragTrap DT-01_clap_name destroyed
ScavTrap DT-01_clap_name destroyed
ClapTrap DT-01_clap_name destroyed
```

---

## ✅ 4. Validation du Module CPP03

**Pour valider ce module, tu dois :**

1. ✅ Implémenter ClapTrap (Ex00)
2. ✅ Implémenter ScavTrap avec héritage (Ex01)
3. ✅ Implémenter FragTrap (Ex02)
4. ⭕ Ex03 optionnel (DiamondTrap)

---

## 🎯 Checklist Finale

- [ ] Ex00 : ClapTrap fonctionne (attack, takeDamage, beRepaired)
- [ ] Ex01 : ScavTrap hérite de ClapTrap
- [ ] Ex01 : Chaînes de construction/destruction correctes
- [ ] Ex02 : FragTrap hérite de ClapTrap
- [ ] Messages de constructeur/destructeur affichés
- [ ] Attributs en `protected` (pas `private`)
- [ ] Pas de memory leaks

---

## ⚠️ Pièges Classiques

**1. Oublier `protected` :**
```cpp
class ClapTrap {
private:         // ❌ Les classes filles n'y auront pas accès
    std::string _name;

protected:       // ✅ Les classes filles y ont accès
    std::string _name;
};
```

**2. Ne pas appeler le constructeur mère :**
```cpp
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {  // ✅
    // ...
}
```

**3. Ordre des messages :**
```
Construction : Mère → Fille
Destruction  : Fille → Mère
```

---

## 🔜 Prochaine Étape

**Module CPP04 : Polymorphism & Abstract Classes**
- Virtual functions
- Polymorphisme
- Classes abstraites
- Interfaces (pure abstract classes)
- Deep copy avec pointeurs

**Passe au fichier CPP04.md ! 🚀**

---

*Module optimisé projet-only pour un étudiant 42 pressé par le temps.*
*CPP03 est un bon break après CPP02, profite ! 😄*
