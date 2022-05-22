#ifndef Bar_hpp
#define Bar_hpp
#include "raylib.h"
#include <string>
#include "Shape.hpp"

class Bar : public Shape
{
public:
    
    //Methods
    bool isChecked();
    void setChecked();
    bool isFound();
    void setFound();
    bool isSorted();
    void setSorted();
    bool isCurr();
    void setCurr();
    void reset();
    virtual void draw() override;
    
    //Constructor
    Bar(int _row, int _col, int _width, int _height);
};



#endif /* Bar_hpp */
