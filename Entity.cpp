#include "Entity.hpp"

Entity::Entity(int _row, int _col, int _width, int _height)
    : Shape(_row, _col, _width, _height)
{
}

Entity::~Entity() {}

bool Entity::isWall()
{
    return colortype == "BLACK";
}

void Entity::setWall()
{
    color = BLACK;
    colortype = "BLACK";
}

void Entity::reset()
{
    color = WHITE;
    colortype = "WHITE";
}

void Entity::draw()
{
    DrawRectangle(x, y, width, width, color);
}

bool Entity::within_bounds(int y, int x, int map_h, int map_w) {
    //Checks the tile being checked is within the map - used within generate_map
    if ((y>=0&&x>=0) && (x<map_h && y<map_w)) {
        return true;
    }
    else {
        return false;
    }
}

void Entity::countNeighbours(std::vector<std::vector<std::shared_ptr<Entity>>>& grid)
{
    wall = 0;
    bool ans=false;
    for (int y=row-1; y<=row+1; y++) {
        for (int x=col-1; x<=col+1; x++) {
            ans = within_bounds(x, y, grid.size(), grid[0].size());
            if (ans) {
                if (y!=row || x!=col) { //makes sure to not count itself
                    if (grid[y][x]->isWall()) {
                        wall++;
                    }
                }
            }
        }
    }
}


