#ifndef Square_hpp
#define Square_hpp
#include <string>
#include <vector>
#include <utility>
#include "raylib.h"
#include <memory>
#include "Shape.hpp"

class Square : public Shape
{
public:
    int wall;
    int width;
    Color color;
    std::string colortype;
    int total_rows;
    int x;
    int y;
    int index;
    std::vector<std::shared_ptr<Square>> neigbours;
    Square(int _row, int _col, int _width, int _total_rows, int _index);
    ~Square();
    std::pair<int,int> getPos();
    bool isClosed();
    bool isOpen();
    bool isBarrier();
    bool isStart();
    bool isEnd();
    void reset();
    void setClosed();
    void setOpen();
    void setBarrier();
    void setStart();
    void setEnd();
    void setPath();
    virtual void draw();
    void updateNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid);
    bool operator==(const Square &other) const;
    bool operator!=(const Square &other) const;
    void countNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid);
    bool within_bounds(int y, int x, int map_h, int map_w);
};

#endif /* Square_hpp */
