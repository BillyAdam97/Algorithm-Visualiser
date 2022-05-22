#include "Tile.hpp"
#define DARKERGREEN  (Color){ 0, 80, 44, 255 }

Tile::Tile(int _row, int _col, int _width)
    : Shape(_row, _col, _width, _width)
{
}

Tile::~Tile() {}

bool Tile::isDarkLand()
{
    return colortype == "DARKERGREEN";
}

void Tile::setDarkLand()
{
    color = DARKERGREEN;
    colortype = "DARKERGREEN";
}

bool Tile::isLand()
{
    return colortype == "DARKGREEN";
}

void Tile::setLand()
{
    color = DARKGREEN;
    colortype = "DARKGREEN";
}

bool Tile::isWater()
{
    return colortype == "BLUE";
}

void Tile::setWater()
{
    color = BLUE;
    colortype = "BLUE";
}

bool Tile::isDarkWater()
{
    return colortype == "DARKBLUE";
}

void Tile::setDarkWater()
{
    color = DARKBLUE;
    colortype = "DARKBLUE";
}

void Tile::draw()
{
    DrawRectangle(x, y, width, width, color);
}

void Tile::countNeighbours(std::vector<std::vector<std::unique_ptr<Tile>>>& grid)
{
    land = 0;
    water = 0;
    darkland = 0;
    darkwater = 0;
    bool ans=false;
    for (int y=row-1; y<=row+1; y++) {
        for (int x=col-1; x<=col+1; x++) {
            ans = within_bounds(x, y, grid.size(), grid[0].size());
            if (ans) {
                if (y!=row || x!=col) { //makes sure to not count itself
                    if (grid[y][x]->isLand()) {
                        land++;
                    }
                    else if (grid[y][x]->isWater()) {
                        water++;
                    }
                    else if (grid[y][x]->isDarkLand()) {
                        darkland++;
                    }
                    else if (grid[y][x]->isDarkWater()) {
                        darkwater++;
                    }
                }
            }
            else {
                land++;
            }
        }
    }
}

bool Tile::within_bounds(int y, int x, int map_h, int map_w)
{
    //Checks the tile being checked is within the map - used within generate_map
    if ((y>=0&&x>=0) && (x<map_h && y<map_w)) {
        return true;
    }
    else {
        return false;
    }
}
