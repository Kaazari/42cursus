#ifndef POINT_HPP
# define POINT_HPP

# include <cmath>

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
