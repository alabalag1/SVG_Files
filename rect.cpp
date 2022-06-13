#include "rect.hpp"
#include<iostream>

Rectangle::Rectangle(const char *type, float x, float y, float width, float heigth, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x{x}, m_y{y}, m_width{width}, m_heigth{heigth} 
{

} 

void Rectangle::print() const
{
    std::cout << getType() << " "  << m_x << " "  << m_y << " "  << m_width << " "  << m_heigth << " "  << getFill() << " "  << getStroke() << " " << getStrokeWidth();
}

