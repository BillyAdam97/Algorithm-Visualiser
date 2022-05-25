#include "Pixel.hpp"

Pixel::Pixel(int _row, int _col, int _width)
: Shape(_row, _col, _width, _width)
{
    a=1.0;
    b=0.0;
}

Pixel::~Pixel() {}


void Pixel::draw() {
    DrawRectangle(x, y, width, width, color);
}
