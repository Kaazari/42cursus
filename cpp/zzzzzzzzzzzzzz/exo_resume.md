# CPP05 - EXCEPTIONS & BUREAUCRAT

## 🎯 C'EST QUOI UNE EXCEPTION ?

**Problème à résoudre:**
> Comment gérer une erreur sans retourner -1 ou NULL ?

**Solution:** `throw` une exception = arrêter le programme et remonter l'erreur

---

### ✅ EX00 - Bureaucrat

**But:** Classe avec un grade (1 = meilleur, 150 = pire). Si grade invalide → exception

**Concept:** Créer sa propre classe d'erreur qui hérite de `std::exception`

**Code clé EXPLIQUÉ:**

```cpp
// 1. Créer une classe d'exception custom
class GradeTooHighException : public std::exception {
    // Hérite de std::exception = classe de base pour toutes les exceptions

public:
    // Override la méthode what() qui retourne le message d'erreur
    virtual const char* what() const throw() {
        // throw() = cette fonction ne lance pas d'exception elle-même
        return "Grade too high!";  // Message qui s'affiche dans catch
    }
};

// 2. Dans le constructor de Bureaucrat
Bureaucrat::Bureaucrat(int grade) {
    if (grade < 1)
        throw GradeTooHighException();  // Lance l'exception = arrête tout et remonte
        // Le programme cherche un "catch" pour gérer cette erreur

    if (grade > 150)
        throw GradeTooLowException();   // Pareil pour grade trop bas

    _grade = grade;  // Si on arrive ici, le grade est valide
}

// 3. Utilisation
int main() {
    try {
        // Le code ici peut lancer des exceptions
        Bureaucrat b(0);  // Grade invalide ! Va lancer GradeTooHighException
    }
    catch (std::exception& e) {
        // On arrive ici si une exception est lancée
        std::cout << "Error: " << e.what() << std::endl;
        // Affiche: "Error: Grade too high!"
    }
}
```

**Pourquoi faire ça ?**
- Plus propre que `if (error) return -1;`
- L'erreur remonte automatiquement jusqu'au `catch`
- Le message d'erreur est clair

**Piège:**
- Toujours hériter de `std::exception`
- Toujours mettre `virtual` devant `what()`
- Attraper par référence: `catch (Exception& e)` pas `catch (Exception e)`

---

### ✅ EX01 - Form

**But:** Un formulaire qui peut être signé par un Bureaucrat si son grade est assez haut

**Concept:** Membres `const` (ne changent jamais) + références

**Code clé EXPLIQUÉ:**

```cpp
class Form {
private:
    const std::string _name;        // const = ne changera jamais après construction
    bool              _signed;       // Peut changer (false → true quand signé)
    const int         _gradeToSign;  // const = grade requis fixé à la création

public:
    // Les membres const DOIVENT être initialisés dans la liste d'initialisation
    Form(std::string name, int gradeToSign)
        : _name(name),        // Initialise _name
          _signed(false),     // Par défaut pas signé
          _gradeToSign(gradeToSign)  // Initialise le grade requis
    {
        // Le corps du constructor vide, tout est fait au-dessus
    }

    void beSigned(Bureaucrat& b) {
        // Prend une RÉFÉRENCE (pas une copie) du Bureaucrat
        // & = modifie l'original, pas une copie

        if (b.getGrade() > _gradeToSign)
            // Si le grade du bureaucrat est > (donc moins bon)
            // Example: grade 100 > grade 50 requis → pas assez bon
            throw GradeTooLowException();

        _signed = true;  // Signature réussie
    }

    bool isSigned() const {
        // const à la fin = cette fonction ne modifie rien
        return _signed;
    }
};
```

**Pourquoi `const` ?**
- `const std::string _name` = le nom du formulaire ne change jamais
- `const int _gradeToSign` = le grade requis ne change jamais
- `bool isSigned() const` = cette fonction promet de ne rien modifier

**Pourquoi référence `&` ?**
```cpp
void beSigned(Bureaucrat& b)  // & = référence
```
- Sans `&` → copie tout le Bureaucrat (lent, gaspille mémoire)
- Avec `&` → utilise l'original directement (rapide)

**Piège:**
- Membres `const` → DOIVENT être dans liste d'initialisation (pas dans le corps)
- Oublier `const` après une fonction qui ne modifie rien

---

### ✅ EX02 - Shrubbery/Robot/President

**But:** Différents types de formulaires qui font des actions différentes quand exécutés

**Concept:** Classe abstraite (= modèle) + héritage + polymorphisme

**Code clé EXPLIQUÉ:**

```cpp
// Classe ABSTRAITE = modèle, ne peut pas être instanciée directement
class AForm {
public:
    // Pure virtual (= 0) = les classes filles DOIVENT implémenter cette fonction
    virtual void execute(Bureaucrat const& executor) const = 0;
    // virtual = peut être redéfinie par les classes filles
    // = 0 = PAS d'implémentation ici, les filles doivent le faire

    virtual ~AForm() {}
    // Destructor TOUJOURS virtual dans une classe avec virtual functions
    // Sinon = memory leak si on delete via un pointeur AForm*
};

// Classe fille qui hérite de AForm
class ShrubberyCreationForm : public AForm {
    // public AForm = hérite publiquement (garde les public de AForm)
public:
    // DOIT implémenter execute() car c'est pure virtual dans AForm
    void execute(Bureaucrat const& executor) const {
        // const Bureaucrat& = prend référence constante (ne modifie pas executor)

        // Vérifie les conditions
        if (!this->isSigned())
            throw FormNotSignedException();
        if (executor.getGrade() > this->getGradeToExecute())
            throw GradeTooLowException();

        // Action spécifique de ShrubberyCreationForm
        std::ofstream file(_target + "_shrubbery");
        file << "ASCII trees here";
        file.close();
    }
};

// Utilisation
int main() {
    AForm* form = new ShrubberyCreationForm("home");
    // Pointeur de type AForm* mais pointe vers ShrubberyCreationForm
    // Polymorphisme = peut stocker différents types de formulaires

    form->execute(bureaucrat);
    // Appelle la version de ShrubberyCreationForm grâce à virtual

    delete form;  // Appelle ~ShrubberyCreationForm puis ~AForm (grâce à virtual)
}
```

**C'est quoi le polymorphisme ?**
```cpp
AForm* form1 = new ShrubberyCreationForm();
AForm* form2 = new RobotomyRequestForm();
AForm* form3 = new PresidentialPardonForm();

// Tous stockés dans le même type (AForm*) mais comportements différents
form1->execute();  // Crée un fichier
form2->execute();  // Fait du bruit
form3->execute();  // Affiche un message
```

**Pourquoi `virtual` ?**
- Sans `virtual`: appelle toujours AForm::execute (crash car = 0)
- Avec `virtual`: appelle la bonne version selon le type réel

**Piège:**
- Oublier `virtual ~AForm()` = memory leak
- Classe abstraite ne peut PAS être instanciée: `AForm f;` → erreur

### ✅ EX03 - Intern

**But:** Une classe sans grade ni nom qui peut créer n'importe quel formulaire sans if/else

**Concept:** Array de function pointers pour éviter le branching

**Code clé EXPLIQUÉ:**

```cpp
class Intern {
public:
    // Fonctions statiques = pas besoin d'instance pour les appeler
    static AForm* makeShrubbery(std::string target) {
        return new ShrubberyCreationForm(target);
    }
    static AForm* makeRobotomy(std::string target) {
        return new RobotomyRequestForm(target);
    }
    static AForm* makePresidential(std::string target) {
        return new PresidentialPardonForm(target);
    }

    AForm* makeForm(std::string name, std::string target) {
        // Array de strings (les noms)
        std::string names[3] = {
            "shrubbery creation",
            "robotomy request",
            "presidential pardon"
        };

        // Array de pointeurs vers fonctions
        // Syntaxe: ReturnType (*arrayName[size])(ParamType)
        AForm* (*creators[3])(std::string) = {
            &Intern::makeShrubbery,
            &Intern::makeRobotomy,
            &Intern::makePresidential
        };
        // Chaque case = pointeur vers une fonction qui prend string et retourne AForm*
        // Les 3 fonctions ont le même "shape" → peuvent cohabiter dans le même array

        for (int i = 0; i < 3; i++) {
            if (names[i] == name) {
                std::cout << "Intern creates " << name << std::endl;
                return creators[i](target);  // Appelle la bonne fonction
            }
        }

        std::cerr << "Error: form '" << name << "' does not exist" << std::endl;
        return NULL;
    }
};

// Utilisation
int main() {
    Intern intern;
    AForm* form = intern.makeForm("robotomy request", "Bender");
    // Intern creates robotomy request

    if (form) {
        // utilise form...
        delete form;  // OBLIGATOIRE, Intern alloue avec new
    }
}
```

**Pourquoi `static` sur les creators ?**
- Sans `static` → la syntaxe du array devient beaucoup plus complexe
- Avec `static` → la fonction n'appartient pas à une instance, donc même syntaxe qu'une fonction normale
- Inconvénient : pas accès aux attributs de l'instance (mais Intern n'en a pas, donc pas grave)

**Pourquoi `AForm*` comme return type commun ?**
- Les 3 fonctions retournent des types différents (`ShrubberyCreationForm*`, etc.)
- Pour les mettre dans le même array, il faut un type commun
- `AForm*` fonctionne car toutes les classes héritent de `AForm` → polymorphisme

**Piège principal :**
- Penser à `delete` le form après utilisation (Intern alloue avec `new`, c'est toi qui libères)
- Ne jamais utiliser `if/else` branching → éliminatoire à l'éval

---

# CPP06 - CASTS (CONVERSIONS)

## 🎯 C'EST QUOI UN CAST ?

**Problème:**
> J'ai un `double` mais je veux un `int`. Comment convertir ?

**Solution:** Les 4 types de casts C++

---

### LES 4 CASTS EXPLIQUÉS

#### 1. static_cast - CONVERSION NORMALE
```cpp
double d = 3.14;
int i = static_cast<int>(d);  // i = 3
// "Prends ce double et transforme-le en int"
// Safe = le compilateur vérifie que c'est possible

float f = 2.5f;
int j = static_cast<int>(f);  // j = 2
```

**Quand utiliser:** Conversions normales entre types compatibles

---

#### 2. dynamic_cast - CONVERSION POLYMORPHIQUE
```cpp
class Animal { virtual void sound() = 0; };
class Dog : public Animal { void sound() { bark(); } };
class Cat : public Animal { void sound() { meow(); } };

Animal* animal = getRandomAnimal();  // Retourne Dog ou Cat, on sait pas

// Essayer de convertir en Dog*
Dog* dog = dynamic_cast<Dog*>(animal);
if (dog != NULL) {
    // C'était bien un Dog !
    dog->bark();
} else {
    // C'était pas un Dog (peut-être un Cat)
}
```

**Avec référence (lance exception si échec):**
```cpp
try {
    Dog& dog = dynamic_cast<Dog&>(*animal);
    // Si animal n'est PAS un Dog, lance std::bad_cast
    dog.bark();
} catch (std::bad_cast& e) {
    std::cout << "Not a dog!" << std::endl;
}
```

**Quand utiliser:** Vérifier le type réel d'un objet polymorphique

---

#### 3. const_cast - AJOUTER/ENLEVER const
```cpp
const int* ptr = &value;
int* modifiable = const_cast<int*>(ptr);
// Enlève le const (DANGEREUX! À éviter sauf cas très spécifiques)
*modifiable = 42;  // Modifie value même si ptr est const
```

**Quand utiliser:** Presque jamais (mauvaise pratique la plupart du temps)

---

#### 4. reinterpret_cast - CONVERSION BINAIRE BRUTE
```cpp
int value = 42;
int* ptr = &value;

// Convertir pointeur en nombre entier
uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
// address contient l'adresse mémoire de value sous forme d'entier

// Reconvertir en pointeur
int* ptr2 = reinterpret_cast<int*>(address);
// ptr2 pointe vers value
```

**Quand utiliser:** Serialization, manipulations bas niveau (très rare)

---

### ✅ EX00 - ScalarConverter

**But:** Convertir une string ("42", "3.14f", "a") en tous les types (char/int/float/double)

**Étapes:**

```cpp
void ScalarConverter::convert(std::string const& input) {
    // 1. Détection du type d'entrée

    // Cas spéciaux
    if (input == "nan" || input == "nanf") {
        // nan = "Not a Number" (résultat d'opération invalide: 0/0)
        printSpecial("nan");
        return;
    }

    if (input == "+inf" || input == "inf" || input == "+inff" || input == "inff") {
        // inf = infini (résultat de 1/0)
        printSpecial("inf");
        return;
    }

    // Détection char
    if (input.length() == 1 && !isdigit(input[0])) {
        // Un seul caractère ET pas un chiffre = c'est un char
        char c = input[0];
        printChar(c);
        return;
    }

    // Détection float
    if (input.find('.') != std::string::npos && input[input.length() - 1] == 'f') {
        // Contient un '.' ET se termine par 'f' = float
        // Example: "3.14f"
        float f = std::strtof(input.c_str(), NULL);
        printFloat(f);
        return;
    }

    // Sinon c'est un nombre (int ou double)
    // ...
}

void printChar(char c) {
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    // Convertit char en int (exemple: 'A' = 65 en ASCII)

    std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}
```

**Ce qu'il faut comprendre:**
- `static_cast<int>(c)` = convertit proprement le char en int
- 'A' en int = 65 (code ASCII)
- Un float se termine par 'f': `3.14f`
- Un double n'a pas de 'f': `3.14`

---

### ✅ EX01 - Serialization

**But:** Transformer un pointeur en nombre (et vice-versa) pour le stocker/transmettre

**Pourquoi ?**
> Tu veux envoyer un pointeur sur le réseau ou le sauvegarder dans un fichier
> Problème: tu peux pas envoyer directement un pointeur
> Solution: convertir en nombre

**Code EXPLIQUÉ:**

```cpp
// uintptr_t = type entier assez grand pour stocker un pointeur
// Sur 64-bit: uintptr_t = unsigned long (8 bytes)

uintptr_t serialize(Data* ptr) {
    // Prend un pointeur Data*
    // Le transforme en nombre entier
    return reinterpret_cast<uintptr_t>(ptr);
    // reinterpret_cast = "prends les bits du pointeur, interprète-les comme un entier"
}

Data* deserialize(uintptr_t raw) {
    // Prend un nombre entier
    // Le retransforme en pointeur Data*
    return reinterpret_cast<Data*>(raw);
    // "Prends ce nombre, interprète-le comme un pointeur"
}

// Utilisation
int main() {
    Data data;
    data.value = 42;

    // Sérialisation: pointeur → nombre
    uintptr_t number = serialize(&data);
    std::cout << "Pointeur transformé en: " << number << std::endl;
    // Affiche quelque chose comme: 140735268474000

    // Désérialisation: nombre → pointeur
    Data* ptr = deserialize(number);

    // ptr pointe vers le même endroit que &data
    std::cout << ptr->value << std::endl;  // Affiche: 42
}
```

**Ce qu'il faut retenir:**
- `serialize` = pointeur → nombre (pour stocker/transmettre)
- `deserialize` = nombre → pointeur (pour réutiliser)
- Les deux sont l'inverse l'un de l'autre

---

### ✅ EX02 - Identify Type

**But:** Trouver le type réel d'un objet sans utiliser `typeinfo` (header interdit)

**Solution:** `dynamic_cast` qui retourne NULL si mauvais type

**Code EXPLIQUÉ:**

```cpp
class Base { public: virtual ~Base() {} };
class A : public Base {};
class B : public Base {};
class C : public Base {};

// Avec POINTEUR
void identify(Base* p) {
    // Essaie de caster en A*
    if (dynamic_cast<A*>(p) != NULL) {
        // Si ça marche (pas NULL), c'est un A !
        std::cout << "A" << std::endl;
        return;
    }

    // Essaie de caster en B*
    if (dynamic_cast<B*>(p) != NULL) {
        std::cout << "B" << std::endl;
        return;
    }

    // Essaie C*
    if (dynamic_cast<C*>(p) != NULL) {
        std::cout << "C" << std::endl;
        return;
    }
}

// Avec RÉFÉRENCE (pas de pointeur permis!)
void identify(Base& p) {
    // Avec référence, dynamic_cast lance une exception si mauvais type
    // Donc on try/catch

    try {
        // Essaie de caster en A&
        (void)dynamic_cast<A&>(p);
        // Si on arrive ici sans exception, c'est un A !
        std::cout << "A" << std::endl;
        return;
    } catch (...) {
        // Exception = c'est pas un A, on continue
    }

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
}
```

**Différence pointeur vs référence:**
- Pointeur: `dynamic_cast` retourne `NULL` si échec
- Référence: `dynamic_cast` lance exception si échec

**Le `(void)` devant:**
```cpp
(void)dynamic_cast<A&>(p);
```
- On s'en fout du résultat du cast
- On veut juste savoir si ça marche (pas d'exception) ou pas (exception)
- `(void)` = "ignore le résultat"

---

# CPP07 - TEMPLATES

## 🎯 C'EST QUOI UN TEMPLATE ?

**Problème:**
> J'ai une fonction `swap` pour int, une pour double, une pour string...
> C'est le MÊME code à chaque fois !

**Solution:** Template = fonction générique qui marche pour N'IMPORTE QUEL type

---

### ✅ EX00 - Swap/Min/Max

**Code EXPLIQUÉ:**

```cpp
// Template de fonction
template <typename T>
// "typename T" = T est un type qu'on ne connaît pas encore
// T peut être int, double, string, n'importe quoi!

void swap(T& a, T& b) {
    // Prend 2 références de type T
    T tmp = a;  // tmp est du même type que a et b
    a = b;
    b = tmp;
}

// Utilisation
int main() {
    int x = 5, y = 10;
    swap(x, y);  // Le compilateur génère swap<int>
    // x = 10, y = 5

    std::string s1 = "hello", s2 = "world";
    swap(s1, s2);  // Le compilateur génère swap<std::string>
    // s1 = "world", s2 = "hello"
}
```

**Comment ça marche:**
1. Tu écris `swap(x, y)` avec des int
2. Le compilateur voit que x et y sont int
3. Il génère automatiquement une version `swap<int>`
4. Magie !

**Template min/max:**
```cpp
template <typename T>
T const& min(T const& a, T const& b) {
    // const& = ne copie pas, ne modifie pas
    return (a < b) ? a : b;
    // Utilise l'opérateur < du type T
    // Marche si T a un operator< défini
}
```

**Pourquoi `const&` ?**
- `const` = promet de ne pas modifier a ou b
- `&` = ne copie pas (économise mémoire/temps)

---

### ✅ EX01 - Iter

**But:** Fonction qui applique une autre fonction sur chaque élément d'un tableau

**Code EXPLIQUÉ:**

```cpp
template <typename T, typename F>
// 2 types: T = type du tableau, F = type de la fonction
void iter(T* array, size_t length, F func) {
    // T* = pointeur sur tableau de T
    // size_t = taille du tableau
    // F = fonction à appliquer

    for (size_t i = 0; i < length; i++) {
        func(array[i]);  // Appelle func sur chaque élément
    }
}

// Exemple de fonction à passer
template <typename T>
void print(T const& x) {
    std::cout << x << " ";
}

// Utilisation
int main() {
    int arr[] = {1, 2, 3, 4, 5};

    iter(arr, 5, print<int>);
    // Appelle print(1), print(2), print(3), print(4), print(5)
    // Affiche: 1 2 3 4 5
}
```

**Ce qui se passe:**
1. `iter` parcourt le tableau
2. Pour chaque élément, appelle `func(element)`
3. Marche avec n'importe quel type et n'importe quelle fonction

---

### ✅ EX02 - Array

**But:** Créer une classe tableau dynamique générique (comme `std::vector` mais simple)

**Code EXPLIQUÉ:**

```cpp
template <typename T>
// T = type des éléments du tableau
class Array {
private:
    T*           _array;  // Pointeur vers le tableau dynamique
    unsigned int _size;   // Taille du tableau

public:
    // Constructeur par défaut
    Array() : _array(NULL), _size(0) {}

    // Constructeur avec taille
    Array(unsigned int n) : _array(new T[n]()), _size(n) {}
    // new T[n]() = alloue n éléments de type T et les initialise à 0
    // Les () à la fin = initialisation par défaut

    // Copy constructor (DEEP COPY obligatoire!)
    Array(const Array& other) : _size(other._size) {
        _array = new T[_size];  // Alloue nouveau tableau
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = other._array[i];  // Copie élément par élément
    }

    // Assignment operator
    Array& operator=(const Array& rhs) {
        if (this != &rhs) {  // Protection contre self-assignment
            delete[] _array;  // Libère ancien tableau
            _size = rhs._size;
            _array = new T[_size];  // Nouveau tableau
            for (unsigned int i = 0; i < _size; i++)
                _array[i] = rhs._array[i];  // Copie
        }
        return *this;  // Permet a = b = c;
    }

    // Destructor
    ~Array() {
        delete[] _array;  // Libère mémoire
    }

    // Operator[] pour accéder aux éléments
    T& operator[](unsigned int i) {
        if (i >= _size)
            throw std::out_of_range("Index out of bounds");
        return _array[i];  // Retourne référence = peut modifier
    }

    unsigned int size() const {
        return _size;
    }
};

// Utilisation
int main() {
    Array<int> arr(5);  // Tableau de 5 int
    arr[0] = 42;
    arr[1] = 100;

    Array<std::string> strings(3);  // Tableau de 3 strings
    strings[0] = "hello";
    strings[1] = "world";
}
```

**Points clés:**
- `new T[n]()` = alloue ET initialise
- Copy constructor = DEEP copy (nouveau tableau, pas juste copier le pointeur)
- `operator[]` retourne `T&` = on peut modifier: `arr[0] = 42`

---

# CPP08 - CONTAINERS & ITERATORS

## 🎯 C'EST QUOI STL ?

**STL = Standard Template Library**
- Conteneurs: `vector`, `list`, `map`, `stack`...
- Algorithmes: `sort`, `find`, `min_element`...
- Iterators: pour parcourir les conteneurs

---

### ✅ EX00 - Easy Find

**But:** Fonction template qui trouve un élément dans n'importe quel conteneur

**Code EXPLIQUÉ:**

```cpp
template <typename T>
// T = type du conteneur (vector, list, etc.)
typename T::iterator easyfind(T& container, int value) {
    // Retourne un iterator du type T
    // typename T::iterator = le type d'iterator de T

    typename T::iterator it = std::find(container.begin(), container.end(), value);
    // std::find = algorithme STL qui cherche value dans [begin, end)
    // Retourne iterator pointant sur value, ou end() si pas trouvé

    if (it == container.end())
        throw std::runtime_error("Value not found");

    return it;
}

// Utilisation
int main() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    try {
        std::vector<int>::iterator it = easyfind(vec, 2);
        std::cout << "Found: " << *it << std::endl;  // *it = déréférence
    } catch (std::exception& e) {
        std::cout << "Not found" << std::endl;
    }
}
```

**C'est quoi un iterator ?**
- Comme un pointeur intelligent
- `begin()` = premier élément
- `end()` = APRÈS le dernier (pas le dernier!)
- `*it` = accède à l'élément
- `++it` = avance au suivant

---

### ✅ EX01 - Span

**But:** Classe qui stocke N entiers et trouve l'écart min/max entre eux

**Code EXPLIQUÉ:**

```cpp
class Span {
private:
    unsigned int        _maxSize;   // Taille max
    std::vector<int>    _numbers;   // Stocke les nombres

public:
    Span(unsigned int N) : _maxSize(N) {
        _numbers.reserve(N);  // Pré-alloue la mémoire (optimisation)
    }

    void addNumber(int number) {
        if (_numbers.size() >= _maxSize)
            throw std::length_error("Span is full");
        _numbers.push_back(number);  // Ajoute à la fin
    }

    int shortestSpan() const {
        if (_numbers.size() < 2)
            throw std::runtime_error("Need at least 2 numbers");

        // 1. Créer copie et trier
        std::vector<int> sorted = _numbers;
        std::sort(sorted.begin(), sorted.end());
        // Trie du plus petit au plus grand

        // 2. Trouver plus petite différence entre voisins
        int minSpan = INT_MAX;  // Plus grande valeur possible
        for (size_t i = 1; i < sorted.size(); i++) {
            int span = sorted[i] - sorted[i-1];
            // Différence entre voisins
            if (span < minSpan)
                minSpan = span;
        }
        return minSpan;
    }

    int longestSpan() const {
        if (_numbers.size() < 2)
            throw std::runtime_error("Need at least 2 numbers");

        // Plus simple: max - min
        int min = *std::min_element(_numbers.begin(), _numbers.end());
        // std::min_element retourne iterator, * = déréférence

        int max = *std::max_element(_numbers.begin(), _numbers.end());

        return max - min;
    }

    // Ajouter un range d'éléments
    template <typename Iterator>
    void addNumber(Iterator begin, Iterator end) {
        while (begin != end) {
            if (_numbers.size() >= _maxSize)
                throw std::length_error("Span is full");
            _numbers.push_back(*begin);  // *begin = élément actuel
            ++begin;  // Avance au suivant
        }
    }
};

// Utilisation
int main() {
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;  // 2 (entre 9 et 11)
    std::cout << sp.longestSpan() << std::endl;   // 14 (entre 3 et 17)

    // Avec range
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Span sp2(10);
    sp2.addNumber(v.begin(), v.end());  // Ajoute tout le vector d'un coup
}
```

**Algorithmes STL utilisés:**
- `std::sort`: trie un range
- `std::min_element`: trouve le plus petit
- `std::max_element`: trouve le plus grand

---

### ✅ EX02 - Mutant Stack

**But:** Une stack (pile) qu'on peut parcourir avec des iterators

**Problème:** `std::stack` n'a PAS d'iterators normalement

**Solution:** Hériter et exposer le conteneur interne

**Code EXPLIQUÉ:**

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
    // Hérite de std::stack<T>

public:
    // std::stack utilise std::deque en interne (container_type)
    // On expose son iterator
    typedef typename std::stack<T>::container_type::iterator iterator;
    // typedef = alias de type pour simplifier

    iterator begin() {
        return this->c.begin();
        // this->c = le conteneur interne de std::stack (std::deque)
        // On accède à son begin()
    }

    iterator end() {
        return this->c.end();
    }
};

// Utilisation
int main() {
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);
    mstack.push(3);

    // Maintenant on peut itérer!
    for (MutantStack<int>::iterator it = mstack.begin();
         it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    // Affiche: 5 17 3
}
```

**Pourquoi `this->c` ?**
- `std::stack` stocke ses données dans `c` (membre protected)
- En héritant, on y a accès via `this->c`

---

# CPP09 - STL ADVANCED

### ✅ EX00 - Bitcoin Exchange

**But:** Lire un fichier CSV de prix Bitcoin et calculer la valeur d'un montant à une date

**Code EXPLIQUÉ:**

```cpp
class BitcoinExchange {
private:
    std::map<std::string, double> _data;
    // map = dictionnaire: clé (date) → valeur (prix)
    // Trié automatiquement par clé (date)

public:
    void loadDatabase(std::string filename) {
        std::ifstream file(filename);  // Ouvre fichier en lecture
        std::string line;

        std::getline(file, line);  // Skip header line

        while (std::getline(file, line)) {
            // Lit ligne par ligne
            // Format: "2011-01-03,0.3"

            size_t pos = line.find(',');  // Trouve position de la virgule
            std::string date = line.substr(0, pos);  // Extrait date
            double price = std::strtod(line.substr(pos + 1).c_str(), NULL);
            // Extrait prix et convertit en double

            _data[date] = price;  // Stocke dans map
        }
    }

    double getValue(std::string date, double amount) {
        // Trouve le prix à cette date (ou la date juste avant)

        std::map<std::string, double>::iterator it = _data.lower_bound(date);
        // lower_bound = premier élément >= date

        if (it == _data.end() || it->first != date) {
            // Pas de prix exact à cette date
            if (it == _data.begin())
                throw std::runtime_error("Date too early");
            --it;  // Prend la date juste avant
        }

        return it->second * amount;
        // it->first = la clé (date)
        // it->second = la valeur (prix)
    }
};
```

**std::map expliqué:**
```cpp
std::map<std::string, double> prices;
prices["2024-01-01"] = 50000.0;  // Insert ou update
prices["2024-01-02"] = 51000.0;

double p = prices["2024-01-01"];  // Accès
```

---

### ✅ EX01 - RPN Calculator

**But:** Calculatrice en notation polonaise inversée (RPN)

**RPN:** `3 4 +` = 3 + 4 = 7
**Normal:** `3 + 4`

**Code EXPLIQUÉ:**

```cpp
class RPNCalculator {
private:
    std::stack<int> _stack;  // LIFO: Last In First Out

public:
    int calculate(std::string const& expression) {
        // Expression: "3 4 + 2 *"

        for (size_t i = 0; i < expression.length(); i++) {
            if (expression[i] == ' ')
                continue;  // Skip espaces

            if (isdigit(expression[i])) {
                // C'est un chiffre, empile-le
                _stack.push(expression[i] - '0');
                // '5' - '0' = 5 (conversion char → int)
            }
            else if (expression[i] == '+' || expression[i] == '-' ||
                     expression[i] == '*' || expression[i] == '/') {
                // C'est un opérateur

                if (_stack.size() < 2)
                    throw std::runtime_error("Not enough operands");

                int b = _stack.top(); _stack.pop();  // Dépile 2ème nombre
                int a = _stack.top(); _stack.pop();  // Dépile 1er nombre
                // Ordre important! a est avant b dans l'expression

                if (expression[i] == '+')
                    _stack.push(a + b);
                else if (expression[i] == '-')
                    _stack.push(a - b);
                else if (expression[i] == '*')
                    _stack.push(a * b);
                else if (expression[i] == '/') {
                    if (b == 0)
                        throw std::runtime_error("Division by zero");
                    _stack.push(a / b);
                }
            }
        }

        if (_stack.size() != 1)
            throw std::runtime_error("Invalid expression");

        return _stack.top();  // Résultat final
    }
};

// Exemple: "3 4 + 2 *"
// 1. Push 3 → stack: [3]
// 2. Push 4 → stack: [3, 4]
// 3. + → pop 4 et 3, push 7 → stack: [7]
// 4. Push 2 → stack: [7, 2]
// 5. * → pop 2 et 7, push 14 → stack: [14]
// Résultat: 14
```

**std::stack:**
- `push(x)`: empile x
- `top()`: regarde le sommet (sans dépiler)
- `pop()`: dépile (enlève le sommet)
- `size()`: taille

---

### ✅ EX02 - PmergeMe

**But:** Trier des nombres avec l'algorithme Ford-Johnson sur 2 conteneurs différents

**Ford-Johnson simplifié:**
- Si petit tableau (≤10): insertion sort
- Sinon: merge sort (diviser pour régner)

**Code EXPLIQUÉ:**

```cpp
void insertionSort(std::vector<int>& arr, int left, int right) {
    // Tri par insertion (efficace pour petits tableaux)
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];  // Élément à insérer
        int j = i - 1;

        // Déplace les éléments > key vers la droite
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // Insère key à sa place
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    // Fusionne deux sous-tableaux triés

    // Copie les deux moitiés
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    // Fusionne en comparant
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    // Copie les restes
    while (i < leftArr.size())
        arr[k++] = leftArr[i++];
    while (j < rightArr.size())
        arr[k++] = rightArr[j++];
}

void mergeInsertSort(std::vector<int>& arr, int left, int right) {
    if (right - left <= 10) {
        // Petit tableau: insertion sort
        insertionSort(arr, left, right);
        return;
    }

    // Grand tableau: merge sort
    int mid = left + (right - left) / 2;

    mergeInsertSort(arr, left, mid);      // Trie gauche
    mergeInsertSort(arr, mid + 1, right); // Trie droite
    merge(arr, left, mid, right);         // Fusionne
}

// Mesure temps
double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
    // Retourne temps en microsecondes
}

int main() {
    std::vector<int> vec = {5, 2, 9, 1, 5, 6};

    double start = getTime();
    mergeInsertSort(vec, 0, vec.size() - 1);
    double end = getTime();

    std::cout << "Time: " << (end - start) << " us" << std::endl;
}
```

---

# 🎯 RÉCAP FINAL

**Ce qu'il faut absolument maîtriser:**

1. **Orthodox Canonical Form** (constructor/copy/assign/destructor)
2. **Exceptions** (throw/try/catch)
3. **Les 4 casts** (static/dynamic/const/reinterpret)
4. **Templates** (fonctions et classes)
5. **STL** (vector, map, stack + algorithmes)
