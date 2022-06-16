#ifndef __RECT_HPP
#define __RECT_HPP

#include "figure.hpp"
#include<iostream>


class Rectangle : public Figure
{
private:
    float m_x;
    float m_y;
    float m_width;
    float m_heigth;

public:
    Rectangle(const char *type = "rect", float x = 0, float y = 0, float width = 0, float heigth = 0, const char *fill = "none", const char *stroke = "none", float strokeWidth = 0);
    std::ostream& print(std::ostream& os = std::cout) const;
    std::ostream& printForSaving(std::ostream& os) const;
};

#endif