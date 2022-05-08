#include "Cell.hpp"

Cell::Cell(int _x, int _j)
{
    x = _x;
    y = _j;
    visited = false;
    walls = {true,true,true,true};
    cols = 800/40;
}

//int Cell::index(int i, int j) {
//
//    return i + j * cols;
//}

bool Cell::checkbounds(int i, int j) {
    if (i<0 || j<0 || i>cols-1 || j>cols-1) {
        return false;
    }
    return true;
}

std::shared_ptr<Cell> Cell::checkNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>>& grid) {
    neighbours.clear();
    if (checkbounds(x, y-1)) {
        std::shared_ptr<Cell> top = grid[x][y-1];
        if (!top->visited) {
            neighbours.emplace_back(top);
        }
    }
    if (checkbounds(x+1, y)) {
        std::shared_ptr<Cell> right = grid[x+1][y];
        if (!right->visited) {
            neighbours.emplace_back(right);
        }
    }
    if (checkbounds(x, y+1)) {
        std::shared_ptr<Cell> bottom = grid[x][y+1];
        if (!bottom->visited) {
            neighbours.emplace_back(bottom);
        }
    }
    if (checkbounds(x-1, y)) {
        std::shared_ptr<Cell> left = grid[x-1][y];
        if (!left->visited) {
            neighbours.emplace_back(left);
        }
    }
    
    if (neighbours.size()>0) {
        std::srand(time(0));
        int i = std::rand()%(neighbours.size());
        return neighbours[i];
    }
    else {
        return nullptr;
    }
}
void Cell::draw()
{
    int i = x*40;
    int j = y*40;
    Vector2 start;
    Vector2 end;
    
    //TOP
    if (walls[0]) {
        start = {(float)i,(float)j};
        end = {(float)i+40,(float)j};
        DrawLineEx(start, end, 2.0, BLACK);
    }
    
    
    //RIGHT
    if (walls[1]) {
        start = {(float)i+40, (float)j};
        end = {(float)i+40, (float)j+40};
        DrawLineEx(start, end, 2.0, BLACK);
    }
    
    
    //BOTTOM
    if (walls[2]) {
        start = {(float)i+40,(float)j+40};
        end = {(float)i,(float)j+40};
        DrawLineEx(start, end, 2.0, BLACK);
    }
    
    
    //LEFT
    if (walls[3]) {
        start = {(float)i, (float)j+40};
        end = {(float)i, (float)j};
        DrawLineEx(start, end, 2.0, BLACK);
    }
    
    if (visited) {
        DrawRectangle(i, j, 40, 40, WHITE);
    }
    
}

void Cell::highlight() {
    int i = x*40;
    int j = y*40;
    DrawRectangle(i, j, 40, 40, BLUE);
}
