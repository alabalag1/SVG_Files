#ifndef __FIGURE_HPP
#define __FIGURE_HPP

#include<iostream>
#include<cstring>

class Figure
{
private:
    char *m_type;
    char *m_fill;
    char *m_stroke;
    float m_strokeWidth;

public:
    ///Constructor
    Figure(const char *type = "none",const char *fill = "none", const char *stroke = "none", float strokeWidth = 0);

    //Selector
    char const* getType() const { return m_type; };
    //Selector
    char const* getFill() const { return m_fill; };
    //Selector
    char const* getStroke() const { return m_stroke; };
    //Selector
    float getStrokeWidth() const { return m_strokeWidth; };

    ///Virtual function that could be used by all derived classes
    virtual std::ostream& print(std::ostream& = std::cout) const = 0; 
    ///Virtual function that could be used by all derived classes
    virtual std::ostream& printForSaving(std::ostream& os) const = 0;
    ///Virtual function that could be used by all derived classes
    virtual Figure& translate(float horizontal, float vertical) = 0;

    ///Mutator
    void setType(const char *type);
    ///Mutator
    void setFill(const char *fill);
    ///Mutator
    void setStroke(const char *stroke);
    ///Mutator
    void setStrokeWidth(const float strokeWidth) { m_strokeWidth = strokeWidth; };

    ///Destructor
    virtual ~Figure();
};



#endif