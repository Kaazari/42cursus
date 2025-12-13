#ifndef RECTANGLE_HPP
# define RECTANGLE_HPP

class Rectangle {
private:
    int _width;
    int _height;

public:
    Rectangle();                        // Constructeur par défaut (1x1)
    Rectangle(int w, int h);            // Constructeur avec paramètres
    ~Rectangle();

    int  getArea() const;               // Retourne width * height
    int  getPerimeter() const;          // Retourne 2 * (width + height)
    void setWidth(int w);
    void setHeight(int h);
};

#endif
