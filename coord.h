#ifndef COORD_H
#define COORD_H

class coord
{
public:
    coord();
    coord(int _x, int _y);
    int x, y;
    coord operator+(coord const &other);
    bool operator==(coord const &other);
    coord negate();
    void rotate();


};

#endif // COORD_H
