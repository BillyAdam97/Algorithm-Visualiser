#ifndef Bar_hpp
#define Bar_hpp
#include "raylib.h"
#include <string>

class Bar
{
public:
    int x;
    int y;
    int row;
    int col;
    int width;
    int height;
    Color color;
    std::string colortype;
    Bar(int _row, int _col, int _width, int _height);
    bool isSorted();
    void setSorted();
    bool isCurr();
    void setCurr();
    void reset();
    void draw();
};



#endif /* Bar_hpp */
