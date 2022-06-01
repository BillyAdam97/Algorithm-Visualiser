#ifndef Node_hpp
#define Node_hpp
#include "Shape.hpp"
#include <unordered_map>
#include <vector>
#include <memory>

class Node : public Shape
{
public:
    bool visited;
    bool clicked;
    std::string character;
    int ind;
    std::vector<std::pair<std::shared_ptr<Node>,float>> edges;
    std::unordered_map<int, Color> lineColor;
    void setClicked();
    void setVisited();
    void reset();
    bool operator==(const Node& other) const;
    virtual void draw() override;
    
    Node(int _x, int _y, int _radius, Color color);
    ~Node();
};

#endif /* Node_hpp */
