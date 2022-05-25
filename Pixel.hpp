#ifndef Pixel_hpp
#define Pixel_hpp
#include <ctime>
#include "Shape.hpp"

class Pixel : public Shape
{
public:
    float a;
    float b;
    
    virtual void draw() override;
    Pixel(int _row, int _col, int _width);
    ~Pixel();
};


#endif /* Pixel_hpp */
