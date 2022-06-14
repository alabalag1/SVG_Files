#include "line.hpp"
#include<iostream>

Line::Line(const char *type, float x1, float y1, float x2, float y2, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x1{x1}, m_y1{y1}, m_x2{x2}, m_y2{y2} {}

std::ostream& Line::print(std::ostream& os) const
{
    os << getType() << " " << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2 << " " << getFill() << " " << getStroke() << " " << getStrokeWidth();
}