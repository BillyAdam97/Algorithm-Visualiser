#include "Node.hpp"

Node::Node(int _x, int _y, int _radius, Color color)
: Shape(_x, _y, _radius, _radius, BLUE)
{
//    color = BLUE;
    visited = false;
    clicked = false;
    character = "0";
}

Node::~Node()
{
    
}

void Node::draw()
{
    DrawCircle(row, col, width, color);
    DrawText(character.c_str(), row-width/3, col-width/2, 20, BLACK);
}

void Node::setClicked()
{
    color = GREEN;
    clicked = true;
}

void Node::reset()
{
    color = BLUE;
    clicked = false;
}

bool Node::operator==(const Node &other) const
{
    return character == other.character;
}

void Node::setVisited() {
    color = GREEN;
    visited = true;
}
