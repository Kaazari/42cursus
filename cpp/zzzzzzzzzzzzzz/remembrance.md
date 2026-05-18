# 💪 MUSCLE MEMORY EXERCISES - C + C++

## 🎯 OBJECTIF
Refaire ces exercices DE MÉMOIRE pour retrouver les réflexes de code.
Temps total: ~3h réparties sur 3 jours.

---

## 🔵 PARTIE C (Jour 1-2)

### Exo 1: ft_strlen (5min)
```c
// Retourne longueur d'une string
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}
```

### Exo 2: ft_strcpy (10min)
```c
// Copie src dans dest
char *ft_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
```

### Exo 3: ft_strdup (15min)
```c
#include <stdlib.h>

char *ft_strdup(char *src)
{
    int len = 0;
    char *dup;
    int i;

    while (src[len])
        len++;

    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;

    i = 0;
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}
```

### Exo 4: ft_atoi (15min)
```c
int ft_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    // Skip whitespaces
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;

    // Handle sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    // Convert digits
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}
```

### Exo 5: ft_split (30min)
```c
#include <stdlib.h>

static int count_words(char *str, char c)
{
    int count = 0;
    int in_word = 0;

    while (*str)
    {
        if (*str != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*str == c)
            in_word = 0;
        str++;
    }
    return count;
}

static char *get_word(char *str, char c)
{
    int len = 0;
    char *word;
    int i;

    while (str[len] && str[len] != c)
        len++;

    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return NULL;

    i = 0;
    while (i < len)
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return word;
}

char **ft_split(char *str, char c)
{
    char **result;
    int words = count_words(str, c);
    int i = 0;

    result = (char **)malloc(sizeof(char *) * (words + 1));
    if (!result)
        return NULL;

    while (*str)
    {
        while (*str && *str == c)
            str++;
        if (*str)
        {
            result[i] = get_word(str, c);
            i++;
            while (*str && *str != c)
                str++;
        }
    }
    result[i] = NULL;
    return result;
}
```

### Exo 6: Lire fichier (20min)
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

char *read_file(char *filename)
{
    int fd;
    char buffer[BUFFER_SIZE];
    char *content = NULL;
    int total_read = 0;
    int bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        char *tmp = malloc(total_read + bytes_read + 1);
        if (!tmp)
        {
            free(content);
            close(fd);
            return NULL;
        }

        if (content)
        {
            int i = 0;
            while (i < total_read)
            {
                tmp[i] = content[i];
                i++;
            }
            free(content);
        }

        int j = 0;
        while (j < bytes_read)
        {
            tmp[total_read + j] = buffer[j];
            j++;
        }
        tmp[total_read + bytes_read] = '\0';
        content = tmp;
        total_read += bytes_read;
    }

    close(fd);
    return content;
}
```

### Exo 7: ft_putnbr (10min)
```c
#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(int nb)
{
    if (nb == -2147483648)
    {
        write(1, "-2147483648", 11);
        return;
    }

    if (nb < 0)
    {
        ft_putchar('-');
        nb = -nb;
    }

    if (nb >= 10)
        ft_putnbr(nb / 10);

    ft_putchar((nb % 10) + '0');
}
```

---

## 🔴 PARTIE C++ (Jour 2-3)

### Exo 1: Classe Contact (20min)
```cpp
#include <iostream>
#include <string>

class Contact {
private:
    std::string _firstName;
    std::string _lastName;
    int         _age;

public:
    Contact() : _firstName(""), _lastName(""), _age(0) {}

    Contact(std::string first, std::string last, int age)
        : _firstName(first), _lastName(last), _age(age) {}

    Contact(const Contact& other)
        : _firstName(other._firstName),
          _lastName(other._lastName),
          _age(other._age) {}

    Contact& operator=(const Contact& rhs) {
        if (this != &rhs) {
            _firstName = rhs._firstName;
            _lastName = rhs._lastName;
            _age = rhs._age;
        }
        return *this;
    }

    ~Contact() {}

    std::string getFirstName() const { return _firstName; }
    std::string getLastName() const { return _lastName; }
    int getAge() const { return _age; }

    void display() const {
        std::cout << _firstName << " " << _lastName
                  << ", " << _age << " years old" << std::endl;
    }
};
```

### Exo 2: Classe avec pointeur (25min)
```cpp
#include <iostream>
#include <stdexcept>

class Data {
private:
    int*   _values;
    size_t _size;

public:
    Data(size_t size) : _size(size) {
        _values = new int[size];
        for (size_t i = 0; i < size; i++)
            _values[i] = 0;
    }

    Data(const Data& other) : _size(other._size) {
        _values = new int[_size];
        for (size_t i = 0; i < _size; i++)
            _values[i] = other._values[i];
    }

    Data& operator=(const Data& rhs) {
        if (this != &rhs) {
            delete[] _values;
            _size = rhs._size;
            _values = new int[_size];
            for (size_t i = 0; i < _size; i++)
                _values[i] = rhs._values[i];
        }
        return *this;
    }

    ~Data() {
        delete[] _values;
    }

    int& operator[](size_t i) {
        if (i >= _size)
            throw std::out_of_range("Index out of bounds");
        return _values[i];
    }

    size_t size() const { return _size; }
};
```

### Exo 3: Héritage simple (20min)
```cpp
#include <iostream>
#include <string>

class Animal {
protected:
    std::string _name;

public:
    Animal(std::string name) : _name(name) {}
    virtual ~Animal() {}

    virtual void makeSound() const = 0;

    std::string getName() const { return _name; }
};

class Dog : public Animal {
public:
    Dog(std::string name) : Animal(name) {}

    void makeSound() const {
        std::cout << _name << " says: Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(std::string name) : Animal(name) {}

    void makeSound() const {
        std::cout << _name << " says: Meow!" << std::endl;
    }
};
```

### Exo 4: Factory + dynamic_cast (25min)
```cpp
#include <iostream>
#include <string>

// Utilise les classes Animal/Dog/Cat de l'exo précédent

Animal* createAnimal(std::string type, std::string name) {
    if (type == "dog")
        return new Dog(name);
    else if (type == "cat")
        return new Cat(name);
    return NULL;
}

void identifyAnimal(Animal* animal) {
    if (dynamic_cast<Dog*>(animal))
        std::cout << "It's a dog!" << std::endl;
    else if (dynamic_cast<Cat*>(animal))
        std::cout << "It's a cat!" << std::endl;
    else
        std::cout << "Unknown animal" << std::endl;
}

int main() {
    Animal* dog = createAnimal("dog", "Rex");
    Animal* cat = createAnimal("cat", "Whiskers");

    dog->makeSound();
    cat->makeSound();

    identifyAnimal(dog);
    identifyAnimal(cat);

    delete dog;
    delete cat;
    return 0;
}
```

### Exo 5: Template swap/min/max (15min)
```cpp
#include <iostream>

template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int a = 5, b = 10;
    std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << std::endl;

    std::cout << "Min: " << min(a, b) << std::endl;
    std::cout << "Max: " << max(a, b) << std::endl;

    return 0;
}
```

### Exo 6: Classe template Array (30min)
```cpp
#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T*           _array;
    unsigned int _size;

public:
    Array() : _array(NULL), _size(0) {}

    Array(unsigned int n) : _array(new T[n]()), _size(n) {}

    Array(const Array& other) : _size(other._size) {
        _array = new T[_size];
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = other._array[i];
    }

    Array& operator=(const Array& rhs) {
        if (this != &rhs) {
            delete[] _array;
            _size = rhs._size;
            _array = new T[_size];
            for (unsigned int i = 0; i < _size; i++)
                _array[i] = rhs._array[i];
        }
        return *this;
    }

    ~Array() {
        delete[] _array;
    }

    T& operator[](unsigned int i) {
        if (i >= _size)
            throw std::out_of_range("Index out of bounds");
        return _array[i];
    }

    unsigned int size() const {
        return _size;
    }
};
```

---

## 🟢 PARTIE STL (Jour 3)

### Exo 7: Vector operations (15min)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    std::vector<int> v;

    // Fill with 10 random numbers
    std::srand(std::time(NULL));
    for (int i = 0; i < 10; i++)
        v.push_back(std::rand() % 100);

    // Display unsorted
    std::cout << "Unsorted: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    // Sort
    std::sort(v.begin(), v.end());

    // Display sorted
    std::cout << "Sorted: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    // Find min/max
    int min = *std::min_element(v.begin(), v.end());
    int max = *std::max_element(v.begin(), v.end());

    std::cout << "Min: " << min << ", Max: " << max << std::endl;

    return 0;
}
```

### Exo 8: Map usage (15min)
```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> ages;

    // Insert
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages.insert(std::make_pair("Charlie", 35));

    // Find
    std::map<std::string, int>::iterator it = ages.find("Bob");
    if (it != ages.end())
        std::cout << "Found: " << it->first << " is "
                  << it->second << " years old" << std::endl;

    // Iterate all
    std::cout << "\nAll entries:" << std::endl;
    for (it = ages.begin(); it != ages.end(); ++it)
        std::cout << it->first << " = " << it->second << std::endl;

    return 0;
}
```

---

## 📅 PLANNING RECOMMANDÉ

**Jour 1:** Exo C 1-4 (45min)
**Jour 2:** Exo C 5-7 + C++ 1-2 (1h30)
**Jour 3:** C++ 3-6 + STL 7-8 (1h30)

**Total: ~3h30 réparties sur 3 jours**

---

## ✅ COMMENT UTILISER CE FICHIER

1. Ouvre un nouveau terminal/VSCode
2. Essaie de recoder SANS regarder
3. Si tu bloques >5min → regarde la solution
4. Recommence le lendemain

**L'objectif = retrouver les réflexes, pas apprendre par cœur.**

---

**GOOD LUCK! 💪**

---
