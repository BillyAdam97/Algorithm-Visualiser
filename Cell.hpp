#ifndef Cell_hpp
#define Cell_hpp
#include "raylib.h"
#include <vector>
#include "Shape.hpp"

class Cell : public Shape
{
public:
    
    //Attributes
    
    int cols;
    bool visited;
    std::vector<bool> walls;
    std::vector<std::shared_ptr<Cell>> neighbours;
    virtual void draw() override;
    
    //Methods
    std::shared_ptr<Cell> checkNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>>& grid);
    void highlight();
    int index(int i, int j);
    bool checkbounds(int i, int j);
    
    //Constructor
    Cell(int _i, int _j);
};

#endif /* Cell_hpp */
