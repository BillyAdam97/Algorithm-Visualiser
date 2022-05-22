#ifndef Tile_hpp
#define Tile_hpp
#include "Shape.hpp"
#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

class Tile : public Shape
{
public:
    int land;
    int water;
    int darkland;
    int darkwater;
    std::vector<std::shared_ptr<Tile>> neighbours;
    
    Tile(int _row, int _col, int _width);
    ~Tile();
    
    bool isDarkLand();
    void setDarkLand();
    bool isLand();
    void setLand();
    bool isWater();
    void setWater();
    bool isDarkWater();
    void setDarkWater();
    void draw();
    void countNeighbours(std::vector<std::vector<std::unique_ptr<Tile>>>& grid);
    bool within_bounds(int y, int x, int map_h, int map_w);
    
};

#endif /* Tile_hpp */
