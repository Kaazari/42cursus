#include "StringBuilder.hpp"
#include <iostream>

int main() {
    StringBuilder sb;

    // Utilisation avec chaînage
    sb.append("Hello")
      .append(" ")
      .append("World")
      .appendInt(42)
      .append("!");

    std::cout << sb.toString() << std::endl;
    // Affiche : Hello World42!

    // Clear et réutiliser
    sb.clear()
      .append("New")
      .append(" ")
      .append("String");

    std::cout << sb.toString() << std::endl;
    // Affiche : New String

    return 0;
}
