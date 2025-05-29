#ifndef TILE_H
#define TILE_H

#include "coord.h"

#include <string>
#include <vector>

enum TileType {
    EMPTY,
    PIPE,
    SOURCE,
    SINK,
    VALVE
};

enum Color {
    NONE,
    BLUE,
    CYAN,
    GREEN,
    RED,
    YELLOW
};

class Tile
{
public:
    Tile();
    Tile(int _shape, TileType _type, Color _color = NONE);
    TileType type;
    Color color;
    int shape;
    std::vector<coord> leaks;
    bool has_leak(coord leak);
    void rotate();
    std::string image_path();
    bool is_open;

};

#endif // TILE_H
