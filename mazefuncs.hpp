#ifndef mazefuncs_hpp
#define mazefuncs_hpp
#include "raylib.h"
#include <vector>
#include "Cell.hpp"
#include <memory>
#include <stack>

bool in_bounds(Vector2 pos, int width, int height);
std::vector<std::vector<std::shared_ptr<Cell>>> setup(int width, int height);
void drawgrid(std::vector<std::vector<std::shared_ptr<Cell>>>& grid, std::shared_ptr<Cell>& curr, std::stack<std::shared_ptr<Cell>>& mystack);
void removeWalls(std::shared_ptr<Cell>& cell1, std::shared_ptr<Cell>& cell2);
void mazealgorithm(int width);

#endif /* mazefuncs_hpp */
