#include "rect.hpp"
#include<iostream>

Rectangle::Rectangle(const char *type, float x, float y, float width, float heigth, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x{x}, m_y{y}, m_width{width}, m_heigth{heigth} {} 

void Rectangle::print() const
{
    std::cout << Figure::getType() << m_x << m_y << m_width << m_heigth << Figure::getFill() << Figure::getStroke() << Figure::getStrokeWidth();
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect)
{
    os << rect.getType() << " " << rect.m_x << " " << rect.m_y << " " << rect.m_width << " " << rect.m_heigth << " " << rect.getFill() << " " << rect.getStroke() << " " << rect.getStrokeWidth();
}
