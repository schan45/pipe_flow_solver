#include "tile.h"

#include <algorithm>
#include <iostream>

// vector for initializing tiles
std::vector<std::vector<coord>> leaks_blueprints({
    {{1, 0}, {-1, 0}},
    {{0, 1}, {1, 0}},
    {{0, 1}, {1, 0}, {-1, 0}},
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}},
    {{1, 0}},
    {{1, 0}, {-1, 0}},
    {{0, 1}, {1, 0}},
    {{0, 1}, {1, 0}, {-1, 0}},
    {{0, 1}, {0, -1}, {1, 0}, {-1, 0}},
});



// default constructor
Tile::Tile() {
    type = EMPTY;
    leaks = leaks_blueprints[0];
    is_open = true;
}

// constructor for non-empty tiles
Tile::Tile(int _shape, TileType _type, Color _color) {
    shape = _shape;
    type = _type;
    color = _color;
    is_open = true;
    if(_shape >=5){
        type = VALVE;
    }
    if(_shape >= leaks_blueprints.size() || _shape < 0) {
        std::cout << "Invalid shape index!" << std::endl;
        std::__throw_out_of_range("Invalid shape to initialize!");
    }
    else
        leaks = leaks_blueprints[_shape];
}

bool Tile::has_leak(coord leak) {
    if(leaks.empty()) return false;
    for(int i = 0; i < leaks.size(); i++) {
        if (leaks[i] == leak) {
            return true;
        }
    }
    return false;
}

void Tile::rotate() {
    for(int i = 0; i < leaks.size(); i++) {
        leaks[i].rotate();
    }
}


// function for printing tiles
std::string Tile::image_path() {
    if(type == EMPTY) return "empty.png";
    else if(type == SOURCE) {
        switch(color) {
        case BLUE:
            if (has_leak(coord(-1, 0)) && has_leak(coord(0, -1))) {
                return "source_blue_left_down.png";
            }
            else if (has_leak(coord(0, -1))) {
                        return "source_blue_down.png";
            }
            else if (has_leak(coord(1, 0))) {
                return "source_blue_right.png";
            }
        case CYAN:
            return "source_cyan.png";
        case GREEN:
            return has_leak(coord(0, 1)) ? "source_green_up.png" :
                   has_leak(coord(0, -1)) ? "source_green_down.png" :
                   has_leak(coord(-1, 0)) ? "source_green_left.png" :
                   has_leak(coord(1, 0)) ? "source_green_right.png" :
                   "source_green.png";
        case RED:
            return "source_red.png";
        case YELLOW:
            return "source_yellow.png";
        default:
            return "empty.png";
        }
    }
    else if(type == SINK) {
        switch(color) {
        case BLUE:
            if (has_leak(coord(0, 1)) && has_leak(coord(1, 0))) {
                return "sink_blue_up_right.png";
            }
            else if (has_leak(coord(0, 1))) {
                return "sink_blue_up.png";
            }
            else if (has_leak(coord(-1, 0))) {
                return "sink_blue_left.png";
            }
        case CYAN:
            return "sink_cyan.png";
        case GREEN:
            return has_leak(coord(0, 1)) ? "sink_green_up.png" :
                   has_leak(coord(0, -1)) ? "sink_green_down.png" :
                   has_leak(coord(-1, 0)) ? "sink_green_left.png" :
                   has_leak(coord(1, 0)) ? "sink_green_right.png" :
                   "sink_green.png";
        case RED:
            return "sink_red.png";
        case YELLOW:
            return "sink_yellow.png";
        default:
            return "empty.png";
        }
    }
    else if(type == VALVE){
        if(is_open){
            return "csap_nyitva.png" ; //Nyitott csap
        }else{
            return "csap_zarva.png"; //Zárt csap
        }

    }
    else if(has_leak(coord(0, 1))) { // up leaks
        if(has_leak(coord(1, 0))) { // right leaks
            if(has_leak(coord(-1, 0))) { // left leaks
                if(has_leak(coord(0, -1))) { // down leaks
                    return "kereszt0.png";
                }
                return "tcso0.png"; // down does not leak
            } else if(has_leak(coord(0, -1))) { // left does not leak but down leaks
                return "tcso1.png";
            }
            return "kanyar1.png"; // left and down does not leak
        } else if (has_leak(coord(-1, 0))) { // right does not leak but left does
            if(has_leak(coord(0, -1))) { // down leaks
                return "tcso3.png"; // left leaks
            } else if(has_leak(coord(-1, 0))) { // down does not leak but left leaks
                return "kanyar0.png";
            }
            // up leaks but right and down and left does not
            return "zsakutca0.png";
        }
        return "egyenescso0.png"; // left does not leak
    } else if(has_leak(coord(0, -1))) { // up doesen't leak, but down leaks
        if(has_leak(coord(-1, 0))) { // left leaks
            if(has_leak(coord(1, 0))) { // right leaks
                return "tcso2.png";
            }
            return "kanyar3.png";
        } else if(has_leak(coord(1, 0))) {  // left does not but right leaks
            return "kanyar2.png";
        }
        return "zsakutca2.png"; // only down leaks
    } else if(has_leak(coord(1, 0))) { // right leaks but up and down does not
        if(has_leak(coord(-1, 0))) {
            return "egyenescso1.png";
        }
        return "zsakutca1.png"; // only right leaks
    }
    return "zsakutca3.png"; // only left leaks
}
