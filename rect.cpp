#include "rect.hpp"
#include<iostream>

Rectangle::Rectangle(const char *type, float x, float y, float width, float heigth, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x{x}, m_y{y}, m_width{width}, m_heigth{heigth} 
{

} 

std::ostream& Rectangle::print(std::ostream& os) const
{
    return os << getType() << " "  << m_x << " "  << m_y << " "  << m_width << " "  << m_heigth << " "  << getFill() << " "  << getStroke() << " " << getStrokeWidth();
}

std::ostream& Rectangle::printForSaving(std::ostream& os) const
{
    return os << "rect x=" << '"' << m_x << '"' << " y=" << '"' << m_y << '"' << " width=" << '"' << m_width << '"' << " height=" << '"' << m_heigth << '"'
              << " fill=" << '"' << getFill() << '"' << " stroke=" << '"' << getStroke() << '"' << " stroke-width=" << '"' << getStrokeWidth() << '"';
}
