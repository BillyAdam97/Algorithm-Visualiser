#include "Shape.hpp"

Shape::Shape(int _row, int _col, int _width, int _height, Color _color, std::string _type)
: row{_row}, col{_col}, width{_width}, height{_height}, color{_color}, colortype{_type}
{
    x = row*width;
    y = col*height;
}

Shape::~Shape() {}
