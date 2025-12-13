#include "Point.hpp"
#include <iostream>

int main() {
    Point player(2, 2);
    Point enemy(3, 4);

    std::cout << "Player position: (" << player.getX() << ", " << player.getY() << ")" << std::endl;
    std::cout << "Enemy position: (" << enemy.getX() << ", " << enemy.getY() << ")" << std::endl;

    double distance = player.distanceTo(enemy);

    std::cout << "Distance: " << distance << std::endl;
    // Affiche : Distance: 2.23607...

    return 0;
}
