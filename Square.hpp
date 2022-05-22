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
    
    //Attributes
    int total_rows;
    int index;
    std::vector<std::shared_ptr<Square>> neigbours;
    
    //Methods
    
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
    
    virtual void draw() override;
    void updateNeighbours(std::vector<std::vector<std::shared_ptr<Square>>>& grid);
    bool operator==(const Square &other) const;
    bool operator!=(const Square &other) const;
    
    //Constructor & Destructor
    Square(int _row, int _col, int _width, int _total_rows, int _index);
    ~Square();
};

#endif /* Square_hpp */
