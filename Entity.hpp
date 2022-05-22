#ifndef Entity_hpp
#define Entity_hpp
#include "Shape.hpp"
#include <vector>

class Entity : public Shape
{
public:
    int wall;
    
    bool isWall();
    void setWall();
    void reset();
    virtual void draw() override;
    void countNeighbours(std::vector<std::vector<std::shared_ptr<Entity>>>& grid);
    bool within_bounds(int y, int x, int map_h, int map_w);
    Entity(int _row, int _col, int _width, int _height);
    ~Entity();
};

#endif /* Entity_hpp */
