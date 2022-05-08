#ifndef Cell_hpp
#define Cell_hpp
#include "raylib.h"
#include <vector>

class Cell
{
public:
    int x;
    int y;
    int cols;
    bool visited;
    std::vector<bool> walls;
    std::vector<std::shared_ptr<Cell>> neighbours;
    void draw();
    std::shared_ptr<Cell> checkNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>>& grid);
    void highlight();
    int index(int i, int j);
    bool checkbounds(int i, int j);
    Cell(int _x, int _j);
};

#endif /* Cell_hpp */
