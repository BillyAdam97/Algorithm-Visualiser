#ifndef Shape_hpp
#define Shape_hpp

class Shape
{
public:
    
    //Attributes
    
    int row;
    int col;

    
    //Methods
    
    virtual void draw() = 0;
    
    //Constructor + Destructor
    
    Shape(int row, int col);
    virtual ~Shape();
    
};

#endif /* Shape_hpp */
