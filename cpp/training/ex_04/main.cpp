#include "IntArray.hpp"
#include <iostream>

int main() {
    IntArray arr(5);  // Créer un tableau de 5 cases

    std::cout << "Size: " << arr.getSize() << std::endl;  // 5

    // Remplir le tableau
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    arr.set(3, 40);
    arr.set(4, 50);

    // Lire les valeurs
    std::cout << "arr[0] = " << arr.get(0) << std::endl;  // 10
    std::cout << "arr[2] = " << arr.get(2) << std::endl;  // 30
    std::cout << "arr[4] = " << arr.get(4) << std::endl;  // 50

    // Test avec index invalide
    arr.set(10, 999);   // Erreur
    arr.get(10);        // Erreur

    return 0;
}  // Destructeur appelé automatiquement ici
