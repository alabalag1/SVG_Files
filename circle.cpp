#include "circle.hpp"
#include<iostream>

Circle::Circle(const char *type, float x, float y, float r, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x{x}, m_y{y}, m_r{r} 
{
}

std::ostream& Circle::print(std::ostream& os) const
{
    return os << getType() << " " << m_x << " " << m_y << " " << m_r << " " << getFill() << " " << getStroke() << " " << getStrokeWidth();
}


std::ostream& Circle::printForSaving(std::ostream& os) const
{
    return os << getType() << " cx=" << '"' << m_x << '"' << " cy=" << '"' << m_y << '"' << " r=" << '"' << m_r << '"'
              << " fill=" << '"' << getFill() << '"' << " stroke=" << '"' << getStroke() << '"' << " stroke-width=" << '"' << getStrokeWidth() << '"';
}

Circle& Circle::translate(float horizontal, float vertical)
{
    m_x += horizontal;
    m_y += vertical;
    return *this;
}
