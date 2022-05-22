#include "Bar.hpp"


Bar::Bar(int _row, int _col, int _width, int _height)
: Shape(_row, _col, _width, _height, BLACK, "BLACK")
{
    x=row*width;
    y=800-height;
}

bool Bar::isSorted() {
    return colortype == "GREEN";
}

void Bar::setSorted() {
    color = GREEN;
    colortype = "GREEN";
}

void Bar::draw() {
    DrawRectangle(x, y, width, height, color);
}

bool Bar::isCurr() {
    return colortype == "RED";
}

void Bar::setCurr() {
    color = RED;
    colortype = "RED";
}

void Bar::reset() {
    color = BLACK;
    colortype = "BLACK";
}
