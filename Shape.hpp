#ifndef Shape_hpp
#define Shape_hpp
#include "raylib.h"
#include <string>

class Shape
{
public:
    
    //Attributes
    
    int row;
    int col;
    int x;
    int y;
    int width;
    int height;
    Color color;
    std::string colortype;
    
    //Methods
    
    virtual void draw() = 0;
    
    //Constructor + Destructor
    
    Shape(int _row, int _col, int _width, int _height, Color _color=WHITE, std::string _type="WHITE");
    virtual ~Shape();
    
};

#endif /* Shape_hpp */
