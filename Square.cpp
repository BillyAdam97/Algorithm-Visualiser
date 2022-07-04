#include "Square.hpp"


Square::Square(int _row, int _col, int _width, int _total_rows, int _index)
: Shape(_row,_col,_width,_width), total_rows{_total_rows}, index{_index}
{
    processed = false;
}

Square::~Square() {}


bool Square::isClosed()
{
    return colortype == "RED";
}

bool Square::isOpen()
{
    return colortype == "GREEN";
}

bool Square::isBarrier()
{
    return colortype == "BLACK";
}

bool Square::isStart()
{
    return colortype == "ORANGE";
}

bool Square::isEnd()
{
    return colortype == "BROWN";
}

void Square::reset()
{
    colortype = "WHITE";
    color = WHITE;
}

void Square::setClosed()
{
    colortype = "RED";
    color = RED;
}

void Square::setOpen()
{
    colortype = "GREEN";
    color = GREEN;
}

void Square::setStart()
{
    colortype = "ORANGE";
    color = ORANGE;
}

void Square::setBarrier()
{
    colortype = "BLACK";
    color = BLACK;
}

void Square::setEnd()
{
    colortype = "BROWN";
    color = BROWN;
}

void Square::setPath()
{
    colortype = "PURPLE";
    color = PURPLE;
}

void Square::setColor(Color c, std::string ct) {
    colortype = ct;
    color = c;
}

void Square::draw()
{
    DrawRectangle(x, y, width, width, color);
}

void Square::updateNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid)
{
    if (row<total_rows-1 && !grid[row+1][col]->isBarrier()) {
        neigbours.emplace_back(grid[row+1][col]);
    }
//    if (row<total_rows-1 && col<total_rows-1 && !grid[row+1][col+1]->isBarrier()) {
//        neigbours.emplace_back(grid[row+1][col+1]);
//    }
    if (row>0 && !grid[row-1][col]->isBarrier()) {
        neigbours.emplace_back(grid[row-1][col]);
    }
//    if (row>0 && col>0 && !grid[row-1][col-1]->isBarrier()) {
//        neigbours.emplace_back(grid[row-1][col-1]);
//    }
    if (col<total_rows-1 && !grid[row][col+1]->isBarrier()) {
        neigbours.emplace_back(grid[row][col+1]);
    }
//    if (row<total_rows-1 && col>0 && !grid[row+1][col-1]->isBarrier()) {
//        neigbours.emplace_back(grid[row+1][col-1]);
//    }
//    if (row>0 && col<total_rows-1 && !grid[row-1][col+1]->isBarrier()) {
//        neigbours.emplace_back(grid[row-1][col+1]);
//    }
    if (col>0 && !grid[row][col-1]->isBarrier()) {
        neigbours.emplace_back(grid[row][col-1]);
    }
}
bool Square::operator==(const Square &other) const
{
    return (x == other.x && y == other.y);
}

bool Square::operator!=(const Square &other) const
{
    return (x!= other.x || y!= other.y);
}
