#ifndef __CIRCLE_HPP
#define __CIRCLE_HPP

#include "figure.hpp"
#include<iostream>


class Circle : public Figure
{
private:
    float m_x;
    float m_y;
    float m_r;

public:
    Circle(const char* type = "circle", float x = 0, float y = 0, float r = 0, const char* fill = "none", const char* stroke = "none", float strokeWidth = 0);
    std::ostream& print(std::ostream& os = std::cout) const;
    ~Circle();
};

#endif