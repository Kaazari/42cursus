# 📚 CHEATSHEET CPP05-09 - EXAM RANK 05

## 🎯 FORMAT: But | Concept | Code Clé

---

# CPP05 - EXCEPTIONS & BUREAUCRAT

### ✅ EX00 - Bureaucrat
**But:** Classe avec grade (1-150), throw si invalide
**Concept:** Exceptions custom (`std::exception`)
**Code clé:**
```cpp
class GradeTooHighException : public std::exception {
    virtual const char* what() const throw() {
        return "Grade too high!";
    }
};

// Dans constructor
if (grade < 1) throw GradeTooHighException();
```

### ✅ EX01 - Form
**But:** Formulaire signable par Bureaucrat
**Concept:** Const members, références, exceptions
**Code clé:**
```cpp
class Form {
private:
    const std::string _name;
    bool _signed;
    const int _gradeToSign;
public:
    void beSigned(Bureaucrat& b) {
        if (b.getGrade() > _gradeToSign)
            throw GradeTooLowException();
        _signed = true;
    }
};
```

### ✅ EX02 - Shrubbery/Robot/President
**But:** Formulaires exécutables (héritage)
**Concept:** Classes abstraites, polymorphisme
**Code clé:**
```cpp
class AForm {
public:
    virtual void execute(Bureaucrat const& executor) const = 0; // Pure virtual
};

class ShrubberyCreationForm : public AForm {
public:
    void execute(Bureaucrat const& executor) const {
        // Crée fichier avec ASCII trees
    }
};
```

---

# CPP06 - CASTS

### ✅ EX00 - ScalarConverter
**But:** Convertir string → char/int/float/double
**Concept:** `static_cast`, détection de type, limites
**Code clé:**
```cpp
// Détecte type
if (input == "nan" || input == "nanf") // special
else if (input.find('.') != std::string::npos) // float/double
else if (input.length() == 1 && !isdigit(input[0])) // char
else // int

// Convertit
double d = std::strtod(input.c_str(), NULL);
char c = static_cast<char>(d);
```

### ✅ EX01 - Serialization
**But:** Convertir pointeur ↔ entier
**Concept:** `reinterpret_cast`, `uintptr_t`
**Code clé:**
```cpp
uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

### ✅ EX02 - Identify Type
**But:** Trouver type réel sans `typeinfo`
**Concept:** `dynamic_cast` (pointeur et référence)
**Code clé:**
```cpp
// Avec pointeur
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A";
}

// Avec référence (throw si mauvais type)
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A";
        return;
    } catch (...) {}
}
```

---

# CPP07 - TEMPLATES

### ✅ EX00 - Swap/Min/Max
**But:** Fonctions templates génériques
**Concept:** Templates de fonctions
**Code clé:**
```cpp
template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
T const& min(T const& a, T const& b) {
    return (a < b) ? a : b;
}
```

### ✅ EX01 - Iter
**But:** Appliquer fonction sur tableau
**Concept:** Templates + pointeurs de fonctions
**Code clé:**
```cpp
template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

// Usage
iter(intArray, 5, printElement<int>);
```

### ✅ EX02 - Array
**But:** Template de classe tableau dynamique
**Concept:** Templates de classes, operator[]
**Code clé:**
```cpp
template <typename T>
class Array {
private:
    T* _array;
    unsigned int _size;
public:
    Array() : _array(NULL), _size(0) {}
    Array(unsigned int n) : _array(new T[n]()), _size(n) {}

    T& operator[](unsigned int i) {
        if (i >= _size) throw std::out_of_range("Index out of bounds");
        return _array[i];
    }
};
```

---

# CPP08 - CONTAINERS & ITERATORS

### ✅ EX00 - Easy Find
**But:** Trouver élément dans conteneur
**Concept:** `std::find`, iterators
**Code clé:**
```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found");
    return it;
}
```

### ✅ EX01 - Span
**But:** Stocker N entiers, trouver écart min/max
**Concept:** `std::vector`, `std::sort`, `std::min_element`
**Code clé:**
```cpp
int shortestSpan() const {
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = INT_MAX;
    for (size_t i = 1; i < sorted.size(); i++)
        minSpan = std::min(minSpan, sorted[i] - sorted[i-1]);
    return minSpan;
}

int longestSpan() const {
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}

// Range add
template <typename Iterator>
void addNumber(Iterator begin, Iterator end) {
    while (begin != end) {
        _numbers.push_back(*begin);
        ++begin;
    }
}
```

### ✅ EX02 - Mutant Stack
**But:** Stack avec iterators
**Concept:** Héritage `std::stack`, expose iterators
**Code clé:**
```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

// Usage
MutantStack<int> mstack;
for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
    std::cout << *it;
```

---

# CPP09 - STL ADVANCED

### ✅ EX00 - Bitcoin Exchange
**But:** Lire CSV, calculer valeur Bitcoin
**Concept:** `std::map`, parsing fichiers
**Code clé:**
```cpp
std::map<std::string, double> _data;

// Parse CSV
std::ifstream file("data.csv");
std::string line;
while (std::getline(file, line)) {
    size_t pos = line.find(',');
    std::string date = line.substr(0, pos);
    double value = std::strtod(line.substr(pos + 1).c_str(), NULL);
    _data[date] = value;
}

// Find closest date
std::map<std::string, double>::iterator it = _data.lower_bound(date);
if (it == _data.end() || it->first != date)
    --it; // Prend date précédente
return it->second * amount;
```

### ✅ EX01 - RPN Calculator
**But:** Calculatrice Reverse Polish Notation
**Concept:** `std::stack`
**Code clé:**
```cpp
std::stack<int> _stack;

void calculate(std::string const& input) {
    for (size_t i = 0; i < input.length(); i++) {
        if (isdigit(input[i]))
            _stack.push(input[i] - '0');
        else if (input[i] == '+' || input[i] == '-' || ...) {
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();
            if (input[i] == '+') _stack.push(a + b);
            else if (input[i] == '-') _stack.push(a - b);
            // etc.
        }
    }
    std::cout << _stack.top(); // Résultat
}
```

### ✅ EX02 - PmergeMe (Ford-Johnson)
**But:** Tri avec 2 conteneurs différents
**Concept:** Merge-insertion sort, mesure temps
**Code clé:**
```cpp
// Ford-Johnson simplifié
void mergeInsertSort(std::vector<int>& arr, int left, int right) {
    if (right - left <= 10) {
        insertionSort(arr, left, right); // Petit tableau
        return;
    }
    int mid = left + (right - left) / 2;
    mergeInsertSort(arr, left, mid);
    mergeInsertSort(arr, mid + 1, right);
    merge(arr, left, mid, right); // Fusionne
}

// Mesure temps
double start = getTime();
mergeInsertSort(_vec, 0, _vec.size() - 1);
double end = getTime();
std::cout << "Time: " << (end - start) << " us";
```

---

# 🔥 CONCEPTS CLÉS PAR MODULE

| Module | Concept Principal |
|--------|-------------------|
| CPP05 | Exceptions custom |
| CPP06 | 4 types de casts |
| CPP07 | Templates |
| CPP08 | STL containers + iterators |
| CPP09 | STL algorithms + maps/stacks |

---

# 💡 TRICKS À RETENIR

### Orthodox Canonical Form
```cpp
class MyClass {
private:
    int* _data;
public:
    MyClass();                          // Default
    MyClass(const MyClass& other);      // Copy
    MyClass& operator=(const MyClass& rhs); // Assignment
    ~MyClass();                         // Destructor
};
```

### Héritage & Virtual
```cpp
class Base {
public:
    virtual void func() = 0;  // Pure virtual (abstract)
    virtual ~Base() {}        // TOUJOURS virtual destructor!
};
```

### Templates
```cpp
// Fonction
template <typename T>
T max(T a, T b) { return (a > b) ? a : b; }

// Classe
template <typename T>
class Container {
    T _value;
public:
    Container(T val) : _value(val) {}
};
```

### Iterators
```cpp
std::vector<int>::iterator it;
for (it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it;
```

### STL Algorithms
```cpp
std::sort(vec.begin(), vec.end());
std::find(vec.begin(), vec.end(), 42);
std::min_element(vec.begin(), vec.end());
std::max_element(vec.begin(), vec.end());
```

---

# ⚠️ PIÈGES CLASSIQUES

1. **Oublier `virtual ~Base()`** → Memory leak si delete via Base*
2. **Shallow copy** → Double free si pointeurs
3. **Pas de return *this** → Pas de chain assignment
4. **Iterators invalidés** → Après push_back/erase
5. **const vs non-const** → Template doit supporter les 2

---

# 🎯 POUR L'EXAM RANK 05

**Maîtrise absolu:**
- Orthodox Canonical Form
- Héritage & polymorphisme
- Templates simples (fonction + classe)
- Exceptions (try/catch/throw)
- STL basics (vector, list, map, stack)

**Révise:**
- CPP00-04 (bases solides)
- CPP05 (exceptions)
- CPP06 (casts)
- CPP07 (templates)
- CPP08 (containers)

**Practice:**
- Refais 1-2 exos par module sans regarder
- Mock exams (3h chrono)
- Focus sur ce que tu galères

---

# 🔥 LES 4 CASTS EN DÉTAIL

### static_cast
**Usage:** Conversions safe entre types compatibles
```cpp
double d = 3.14;
int i = static_cast<int>(d); // 3

Base* base = new Derived();
Derived* derived = static_cast<Derived*>(base); // OK si tu es SÛR du type
```

### dynamic_cast
**Usage:** Conversions polymorphiques safe (runtime check)
```cpp
Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base); // NULL si mauvais type

// Avec référence
try {
    Derived& d = dynamic_cast<Derived&>(*base);
} catch (std::bad_cast& e) {
    // Mauvais type
}
```

### const_cast
**Usage:** Ajouter/enlever const
```cpp
const int* ptr = &value;
int* nonConst = const_cast<int*>(ptr); // Enlève const (DANGEREUX)
```

### reinterpret_cast
**Usage:** Conversions binaires brutes (TRÈS DANGEREUX)
```cpp
int* ptr = &value;
uintptr_t addr = reinterpret_cast<uintptr_t>(ptr); // Pointeur → entier
```

---

# 📝 NOTES RAPIDES

**Exceptions:**
- Héritent de `std::exception`
- Override `what()` avec `throw()`
- `try { ... } catch (Exception& e) { ... }`

**Templates:**
- Déclaration: `template <typename T>`
- Instanciation automatique par le compilateur
- Peuvent être fonctions OU classes

**STL Containers:**
- `vector`: tableau dynamique
- `list`: liste doublement chaînée
- `map`: arbre binaire (clé → valeur)
- `stack`: LIFO (dernier entré, premier sorti)
- `queue`: FIFO (premier entré, premier sorti)

**Iterators:**
- `begin()`: premier élément
- `end()`: APRÈS le dernier élément
- `++it`: avance
- `*it`: déréférence

---

**READY POUR L'EXAM! 💪**
