#ifndef __LINE_HPP
#define __LINE_HPP

#include "figure.hpp"
#include<iostream>


class Line : public Figure
{
private:
    float m_x1;
    float m_y1;
    float m_x2;
    float m_y2;

public:
    ///Constructor
    Line(const char* type = "line", float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0, const char* fill = "none", const char* stroke = "none", float strokeWidth = 0);
    
    ///Virtual function, inherited by base class
    std::ostream& print(std::ostream& os = std::cout) const;
    ///Virtual function, inherited by base class
    std::ostream& printForSaving(std::ostream& os) const;
    ///Virtual function, inherited by base class
    Line &translate(float horizontal, float vertical);
};

#endif