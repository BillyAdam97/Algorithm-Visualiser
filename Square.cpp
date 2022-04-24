#include "Square.hpp"


Square::Square(int _row, int _col, int _width, int _total_rows, int _index)
:row{_row}, col{_col}, width{_width}, total_rows(_total_rows), index{_index}
{
    x = row*width;
    y = col*width;
    color = WHITE;
    colortype = "WHITE";
    wall = 0;
}

Square::~Square() {}

std::pair<int,int> Square::getPos()
{
    std::pair<int,int> rowcol {row,col};
    return rowcol;
}

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

void Square::draw()
{
    DrawRectangle(x, y, width, width, color);
}

void Square::updateNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid)
{
    if (row<total_rows-1 && !grid[row+1][col]->isBarrier()) {
        neigbours.emplace_back(grid[row+1][col]);
    }
    if (row>0 && !grid[row-1][col]->isBarrier()) {
        neigbours.emplace_back(grid[row-1][col]);
    }
    
    if (col<total_rows-1 && !grid[row][col+1]->isBarrier()) {
        neigbours.emplace_back(grid[row][col+1]);
    }
    
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

void Square::countNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid)
{
    wall = 0;
    bool ans=false;
    for (int y=row-1; y<=row+1; y++) {
        for (int x=col-1; x<=col+1; x++) {
            ans = within_bounds(x, y, grid.size(), grid[0].size());
            if (ans) {
                if (y!=row || x!=col) { //makes sure to not count itself
                    if (grid[y][x]->isBarrier()) {
                        wall++;
                    }
                }
            }
        }
    }
}

bool Square::within_bounds(int y, int x, int map_h, int map_w) {
    //Checks the tile being checked is within the map - used within generate_map
    if ((y>=0&&x>=0) && (x<map_h && y<map_w)) {
        return true;
    }
    else {
        return false;
    }
}
