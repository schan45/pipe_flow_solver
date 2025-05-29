#include "tilemap.h"
#include "coord.h"
#include "tile.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define WIDTH 9
#define HEIGHT 7


// default constructor
tilemap::tilemap() {}


// ========== ACTION STRUCT ========== //

enum ActionType {
    NEW_PLACEMENT,
    OCCUPIED
};

struct action {
    coord pos;
    int rot;
    ActionType type;

    action() {}

    action(coord _pos,int _rot,ActionType _type) {
        pos = _pos;
        rot = _rot;
        type = _type;
    }
};


// ========== GLOBAL VARIABLES ========== //



// Uncomment this for debugging the algorithm steps
//#define DEBUG


std::vector<std::tuple<coord, Color, int, int>> sources;


std::vector<coord> leaks;
std::vector<action> actions;

std::vector<std::vector<Tile>> tile_map;
int targets = 0;

std::vector<int> supply = {0, 0, 0, 0, 0, 0, 0, 0, 0};



// ========== CONSTRUCTOR ========== //

tilemap::tilemap(std::vector<std::tuple<coord, Color, int, int>> _sources, std::vector<std::tuple<coord, Color, int, int>> sinks, std::vector<std::pair<int,std::vector<Color>>> phases, std::vector<int> _supply) {
    // clearing vectors
    leaks.clear();
    actions.clear();
    supply.clear();
    targets = 0;

    // fill tilemap with empty tiles
    tile_map.clear();
    for(int x = 0; x < WIDTH; x++) {
        tile_map.push_back(std::vector<Tile>{});
        for(int y = 0; y < HEIGHT; y++) {
            tile_map[x].push_back(Tile{});
        }
    }

    // place down sources
    sources = _sources;
    for(int i = 0; i < _sources.size(); i++) {
        Tile new_source(std::get<2>(_sources[i]), SOURCE, std::get<1>(_sources[i]));
        // rotate to correct rotation
        for(int k = 0; k<std::get<3>(_sources[i]);k++) {
            new_source.rotate();
        }
        tile_map[std::get<0>(_sources[i]).x][std::get<0>(_sources[i]).y] = new_source;
        // push starter leaks
        for(int j = 0; j < new_source.leaks.size(); j++) {
            leaks.push_back(new_source.leaks[j] + std::get<0>(_sources[i]));
        }
    }

    // place down sinks and initialize targets
    targets = 0;
    for(int i = 0; i < sinks.size(); i++) {
        Tile new_sink(std::get<2>(sinks[i]), SINK, std::get<1>(sinks[i]));
        targets += new_sink.leaks.size();
        for(int k = 0; k<std::get<3>(sinks[i]);k++) {
            new_sink.rotate();
        }
        tile_map[std::get<0>(sinks[i]).x][std::get<0>(sinks[i]).y] = new_sink;
    }

    // initialize supply
    supply = _supply;
}


// ========== SOLVER ALGORITHM ========== //

bool tilemap::solver_algorithm() {
    coord current_leak;

    while(true) {
#ifdef DEBUG
        std::cout<<"Leaks: "<<leaks.size()<<" Targets: "<<targets<<std::endl;
#endif
        if(!leaks.empty()) {
            current_leak = leaks.back();
            leaks.pop_back();
            if(tile_map[current_leak.x][current_leak.y].type != EMPTY) {
                if(tile_map[current_leak.x][current_leak.y].type == SINK) {
                    targets--;
                }
                actions.push_back(action(current_leak, -1, OCCUPIED));
#ifdef DEBUG
                std::cout<<"Found occupied tile, we're good."<<std::endl;
#endif
                continue;
            }
            if(place_new_tile(current_leak)) {
#ifdef DEBUG
                std::cout<<"Placed down new tile:\n"<<to_string()<<"\n\n";
#endif
                continue;
            }
#ifdef DEBUG
            std::cout<<"Could not place new tile! ";
#endif
            leaks.push_back(current_leak);
        } else if(targets == 0) {
#ifdef DEBUG
            std::cout<<"No more targets, and leaks empty, checking for traversing..."<<std::endl;
#endif
            bool all_connect = true;
            for(int i = 0; i < sources.size(); i++) {
                if(!traverse(sources[i])) {
#ifdef DEBUG
                    std::cout<<"Found a source that is not connecting! ";
#endif
                    all_connect = false;
                    break;
                }
            }
            if(all_connect) {
#ifdef DEBUG
                std::cout<<"All sources connect to sinks, returning true!"<<std::endl;
#endif
                rearrange();
                //ide valve-os cucc
                return true;
            }
        }
#ifdef DEBUG
        std::cout<<"Tweaking last action..."<<std::endl;
#endif
        while(!tweak_last_action()) {
#ifdef DEBUG
            std::cout<<"Could not tweak last action, deleting last action:\n"<<to_string()<<"\n\n";
#endif
            if(actions.empty()) {
#ifdef DEBUG
                std::cout<<"No last action to delete, returning false."<<std::endl;
#endif
                return false;
            }
        }
#ifdef DEBUG
        std::cout<<"Tweaked last action:\n"<<to_string()<<"\n\n";
#endif
    }
}

bool tilemap::place_new_tile(coord pos) {
    // find fitting tile
    auto new_tile_info = find_fitting_tile(pos, -1);
    if(new_tile_info.second == -1)
        return false;

    // update map
    tile_map[pos.x][pos.y] = new_tile_info.first;

    // update supply
    supply[new_tile_info.first.shape]--;

    // push action
    actions.push_back(action(pos, new_tile_info.second, NEW_PLACEMENT));

    // push leaks
    for(coord leak : new_tile_info.first.leaks) {
        leaks.push_back(leak + pos);
    }
    return true;
}


bool tilemap::tweak_last_action() {

    if(actions.empty())
        return false;

    // save last action
    action *last_action = &actions.back();

    // save last action's tile
    Tile *last_tile = &tile_map[last_action->pos.x][last_action->pos.y];

    if(last_action->type == OCCUPIED) {
        // push leak
        leaks.push_back(last_action->pos);

        if(tile_map[last_action->pos.x][last_action->pos.y].type == SINK)
            targets++;

        // pop last action
        actions.pop_back();
        return false;
    }

    // pop leaks
    for(int i = 0; i < last_tile->leaks.size(); i++) {
        leaks.pop_back();
    }

    // check for rotation
    while(last_action->rot < 3) {
        last_tile->rotate();
        last_action->rot++;
        if(tile_fits(*last_tile, last_action->pos)) {
            // found new fitting tile
            // push leaks
            for(int i = 0; i < last_tile->leaks.size(); i++) {
                leaks.push_back(last_tile->leaks[i] + last_action->pos);
            }
            return true;
        }
    }

    // add supply
    supply[last_tile->shape]++;

    // check for new shape
    auto new_tile_info = find_fitting_tile(last_action->pos, last_tile->shape);
    if(new_tile_info.second != -1) {
        // sub supply
        supply[new_tile_info.first.shape]--;

        // update rotation in last action
        last_action->rot = new_tile_info.second;

        // update tilemap
        *last_tile = new_tile_info.first;

        // push leaks
        for(int i = 0; i < last_tile->leaks.size(); i++) {
            leaks.push_back(last_tile->leaks[i] + last_action->pos);
        }
        return true;
    }

    // push current leak
    leaks.push_back(last_action->pos);

    // pop last action
    actions.pop_back();

    // update map to empty
    last_tile->type = EMPTY;
    return false;
}


// tile and rotation info
std::pair<Tile, int> tilemap::find_fitting_tile(coord leak, int current_shape) {
    int shape = current_shape + 1;
    // loop through supplies
    while(shape <= supply.size()) {
        // check supply
        if(supply[shape] <= 0) {
            shape++;
            continue;
        }

        // check if it fits in any rotation
        Tile new_tile(shape, PIPE);
        Tile new_valve(shape,VALVE);
        for(int i = 0; i < 8; i++) {
            if(i>=5){
                new_valve.rotate();
                if(tile_fits(new_valve, leak)){
                    return std::make_pair(new_valve,i);
                }
            }else{
                new_tile.rotate();
                if(tile_fits(new_tile, leak)) {
                    // if we found one, we return it with the rotation
                    return std::make_pair(new_tile, i);
                }
            }
        }
        shape++;
    }

    // if no found, return -1 for rotation
    return std::make_pair(Tile{}, -1);
}

bool tilemap::tile_fits(Tile t, coord pos) {
    // see if it fits to all neighbours
    return tiles_meet(t, pos, coord(0, 1)) &&
           tiles_meet(t, pos, coord(-1, 0)) &&
           tiles_meet(t, pos, coord(0, -1)) &&
           tiles_meet(t, pos, coord(1, 0));
}

bool tilemap::tiles_meet(Tile base, coord pos, coord relation) {
    coord neighbour = pos + relation;
    // if at the border, see if we leak there
    if(neighbour.x < 0 || neighbour.y < 0 || neighbour.y >= HEIGHT || neighbour.x >= WIDTH) {
        return !base.has_leak(relation);
    }

    // if not, get the tile there
    Tile env = tile_map[neighbour.x][neighbour.y];

    // for empty tile, we always fit
    if(env.type == EMPTY)
        return true;

    // they fit if either both or neigh has leak
    return base.has_leak(relation) == env.has_leak(relation.negate());
}


bool tilemap::traverse(std::tuple<coord, Color, int, int> source) {
    std::vector<coord> leaks_to_check;
    coord current_coord{0, 0};
    std::vector<coord> already_checked;
    // Fill in starter leaks
    Tile current_source = tile_map[std::get<0>(source).x][std::get<0>(source).y];
    for(int i = 0; i < current_source.leaks.size(); i++) {
        leaks_to_check.push_back(current_source.leaks[i] + std::get<0>(source));
    }
    // We already know the position of the source
    already_checked.push_back(std::get<0>(source));

#ifdef DEBUG
    std::cout<<"\n==TRAVERSING STEP==\n";
    //std::cout<<"Traversing source at ("<<source.first.x<<", "<<source.first.y<<")"<<std::endl;
#endif

    // Check if we can get to a sink with the correct color
    while(leaks_to_check.size() > 0) {
#ifdef DEBUG
        std::cout<<"leaks to check size: "<<leaks_to_check.size()<<"\t\t";
#endif
        current_coord = leaks_to_check.back();
        leaks_to_check.pop_back();
#ifdef DEBUG
        std::cout<<"Currently popped: ("<<current_coord.x<<", "<<current_coord.y<<")\n";
#endif
        if(tile_map[current_coord.x][current_coord.y].type == SINK) {
            if(tile_map[current_coord.x][current_coord.y].color ==  std::get<1>(source)) {
                // We can get there, we're good
#ifdef DEBUG
                std::cout<<"Found sink, and correct color, we're good!"<<std::endl;
#endif

                return true;
            }
#ifdef DEBUG
            else {
                std::cout<<"Found sink, but wrong color!"<<std::endl;
            }
#endif
        }
        if(std::find(already_checked.begin(), already_checked.end(), current_coord) != already_checked.end()) {
            // Already checked, go on
#ifdef DEBUG
            std::cout<<"Already checked, we're good."<<std::endl;
#endif
            continue;
        }
#ifdef DEBUG
        std::cout<<"New tile, pushing leaks... ";
#endif
        already_checked.push_back(current_coord);
        for(int i = 0; i < tile_map[current_coord.x][current_coord.y].leaks.size(); i++) {
            // Push leaks, if new tile
#ifdef DEBUG
            std::cout<<"("<<tile_map[current_coord.x][current_coord.y].leaks[i].x
                      <<", "<<tile_map[current_coord.x][current_coord.y].leaks[i].y<<") ";
#endif
            leaks_to_check.push_back(tile_map[current_coord.x][current_coord.y].leaks[i] + current_coord);
        }
#ifdef DEBUG
        std::cout<<std::endl;
#endif
    }
#ifdef DEBUG
    std::cout<<"No more leaks to pop and haven't found any sink with the correct color! Returning false."<<std::endl;
#endif
    return false;
}

void tilemap::rearrange() {
#ifdef DEBUG
    std::cout<<"Elkezdve."<<std::endl;
#endif
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            Tile& valve_tile = tile_map[x][y];

            // Valve keresése
            if (valve_tile.type != VALVE) {
                continue;
            }

            coord valve_pos{x, y};
            int valve_priority = 0;
            //std::cout<<"Csapot talált: "<<valve_pos.x<<" "<<valve_pos.y;

            // VALVE prioritása
            std::vector<coord> neighbours = {
                valve_pos + coord(0, 1),
                valve_pos + coord(1, 0),
                valve_pos + coord(0, -1),
                valve_pos + coord(-1, 0)
            };

            for (coord neighbour_pos : neighbours) {
                if (neighbour_pos.x < 0 || neighbour_pos.y < 0 || neighbour_pos.x >= WIDTH || neighbour_pos.y >= HEIGHT) {
                    continue;
                }

                Tile& neighbour_tile = tile_map[neighbour_pos.x][neighbour_pos.y];
                if (neighbour_tile.type == PIPE){
                    std::cout<<"Found pipe shape: "<<neighbour_tile.shape<<std::endl;
                    if(neighbour_tile.shape == 2 || neighbour_tile.shape == 3){
                        std::cout<<"Valve prio updated"<<std::endl;
                        ++valve_priority;
                    }
                }
            }
            //std::cout<<"VALVE priority: "<<valve_priority<<std::endl;

            // Keresünk egy azonos alakú PIPE-ot, aminek nagyobb a prioritása
            int matching_pipe_shape = valve_tile.shape - 5;
            coord best_pipe_pos = {-1, -1};
            int best_pipe_priority = -1;

            for (int px = 0; px < WIDTH; ++px) {
                for (int py = 0; py < HEIGHT; ++py) {
                    Tile& pipe_tile = tile_map[px][py];
                    if (pipe_tile.type != PIPE || pipe_tile.shape != matching_pipe_shape) {
                        continue;
                    }

                    // PIPE prioritása
                    int pipe_priority = 0;
                    coord pipe_pos{px, py};
                    std::vector<coord> pneighbours = {
                        pipe_pos + coord(0, 1),
                        pipe_pos + coord(1, 0),
                        pipe_pos + coord(0, -1),
                        pipe_pos + coord(-1, 0)
                    };

                    for (coord neighbour_pos : pneighbours){
                        if (neighbour_pos.x < 0 || neighbour_pos.y < 0 || neighbour_pos.x >= WIDTH || neighbour_pos.y >= HEIGHT) {
                            continue;
                        }
                        Tile& neighbour_tile = tile_map[neighbour_pos.x][neighbour_pos.y];
                        if (neighbour_tile.type == PIPE){
                            std::cout<<"Found pipe shape"<<std::endl;
                            if(neighbour_tile.shape == 2 || neighbour_tile.shape == 3){
                                std::cout<<"Pipe prio updated"<<std::endl;
                                ++pipe_priority;
                            }

                        }

                    }
                    //std::cout<<"Found PIPE with prio: "<<pipe_priority<<std::endl;

                    // Ha magasabb a PIPE prioritása, elmentjük
                    if (pipe_priority > valve_priority && pipe_priority > best_pipe_priority) {
                        best_pipe_priority = pipe_priority;
                        best_pipe_pos = pipe_pos;
                    }
                }
            }

            //Kicseréljük
            if (best_pipe_pos.x != -1 && best_pipe_pos.y != -1) {
                Tile& best_pipe_tile = tile_map[best_pipe_pos.x][best_pipe_pos.y];
                valve_tile.type = PIPE;
                // valve_tile.shape = valve_tile.shape-5;
                best_pipe_tile.type = VALVE;
#ifdef DEBUG
                std::cout<<"Kicserélve.";
#endif \
    // best_pipe_tile.shape = best_pipe_tile.shape + 5; \
    //tile_map[valve_pos.x][valve_pos.y] = best_pipe_tile; \
    //tile_map[best_pipe_pos.x][best_pipe_pos.y] = valve_tile;
            }
        }
    }
}
void tilemap::toggle_valves(){

    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            Tile& valve_tile = tile_map[x][y];

            // Valve keresése
            if (valve_tile.type == VALVE) {
                valve_tile.is_open = false;
            }

        }
    }
}





// ========== PRINTING THE MAP ========== //

Tile tilemap::get_tile_at(const coord& position) const {
    if (position.x >= 0 && position.x < WIDTH && position.y >= 0 && position.y < HEIGHT) {
        return tile_map[position.x][position.y];
    } else {
        return Tile(); // Return an empty tile for out-of-bounds access
    }
}

