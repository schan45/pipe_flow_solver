#ifndef TILEMAP_H
#define TILEMAP_H
#include "coord.h"
#include "tile.h"
#include <vector>
#include <string>

class tilemap
{
public:
    tilemap();
    tilemap(std::vector<std::tuple<coord, Color, int, int>> _sources, std::vector<std::tuple<coord, Color, int, int>> sinks, std::vector<std::pair<int,std::vector<Color>>> phases, std::vector<int> _supply);
    bool solver_algorithm();
    std::string to_string();
    void rearrange();
    void toggle_valves();
    Tile get_tile_at(const coord& position) const;
    static constexpr int HEIGHT = 7;
    static constexpr int WIDTH = 9;


private:
    bool place_new_tile(coord pos);
    bool tweak_last_action();
    std::pair<Tile, int> find_fitting_tile(coord leak, int current_shape);
    bool tiles_meet(Tile base, coord pos, coord relation);
    bool tile_fits(Tile t, coord pos);
    bool traverse(std::tuple<coord, Color, int, int> source);


};

#endif // TILEMAP_H
