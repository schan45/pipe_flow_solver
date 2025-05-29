#include "coord.h"

// Default constructor
coord::coord() : x(0), y(0) {}

coord::coord(int _x, int _y) {
    x = _x;
    y = _y;
}

coord coord::operator+(coord const &other) {
    coord ret;
    ret.x = x + other.x;
    ret.y = y + other.y;
    return ret;
}

bool coord::operator==(coord const &other) {
    return x == other.x && y == other.y;
}

coord coord::negate() {
    coord ret;
    ret.x = -x;
    ret.y = -y;
    return ret;
}

void coord::rotate() {
    int temp = x;
    x = -y;
    y = temp;
}
