#ifndef INTARRAY_HPP
# define INTARRAY_HPP

class IntArray {
private:
    int *_array;
    int  _size;

public:
    IntArray(int size);
    ~IntArray();

    void set(int index, int value);
    int  get(int index) const;
    int  getSize() const;
};

#endif
