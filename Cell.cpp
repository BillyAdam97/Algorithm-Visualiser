#include "Cell.hpp"

Cell::Cell(int _x, int _j)
    : Shape(_x,_j, 20, 20)
{
    visited = false;
    walls = {true,true,true,true};
    cols = 800/width;
}

bool Cell::checkbounds(int i, int j) {
    if (i<0 || j<0 || i>cols-1 || j>cols-1) {
        return false;
    }
    return true;
}

std::shared_ptr<Cell> Cell::checkNeighbours(std::vector<std::vector<std::shared_ptr<Cell>>>& grid) {
    neighbours.clear();
    if (checkbounds(row, col-1)) {
        std::shared_ptr<Cell> top = grid[row][col-1];
        if (!top->visited) {
            neighbours.emplace_back(top);
        }
    }
    if (checkbounds(row+1, col)) {
        std::shared_ptr<Cell> right = grid[row+1][col];
        if (!right->visited) {
            neighbours.emplace_back(right);
        }
    }
    if (checkbounds(row, col+1)) {
        std::shared_ptr<Cell> bottom = grid[row][col+1];
        if (!bottom->visited) {
            neighbours.emplace_back(bottom);
        }
    }
    if (checkbounds(row-1, col)) {
        std::shared_ptr<Cell> left = grid[row-1][col];
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
    int i = row*width;
    int j = col*width;
    Vector2 start;
    Vector2 end;
    
    //TOP
    if (walls[0]) {
        start = {(float)i,(float)j};
        end = {(float)i+width,(float)j};
        DrawLineEx(start, end, 3.0, BLACK);
    }
    
    
    //RIGHT
    if (walls[1]) {
        start = {(float)i+width, (float)j};
        end = {(float)i+width, (float)j+width};
        DrawLineEx(start, end, 3.0, BLACK);
    }
    
    
    //BOTTOM
    if (walls[2]) {
        start = {(float)i+width,(float)j+width};
        end = {(float)i,(float)j+width};
        DrawLineEx(start, end, 3.0, BLACK);
    }
    
    
    //LEFT
    if (walls[3]) {
        start = {(float)i, (float)j+width};
        end = {(float)i, (float)j};
        DrawLineEx(start, end, 3.0, BLACK);
    }
    
    if (visited) {
        DrawRectangle(i, j, width, width, WHITE);
    }
    
}

void Cell::highlight() {
    int i = row*width;
    int j = col*width;
    DrawRectangle(i, j, width, width, BLUE);
}
