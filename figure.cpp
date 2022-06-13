#include "figure.hpp"
#include<iostream>
#include<cstring>

Figure::Figure(const char *type, const char *fill, const char *stroke, float strokeWidth) 
    : m_strokeWidth{strokeWidth}
{
    setType(type);
    setFill(fill);
    setStroke(stroke);
}

void Figure::setType(const char* type)
{
    if(type == nullptr || m_type == type)
        return;
    m_type = new char[strlen(type) + 1];
    strcpy(m_type, type);
}

void Figure::setFill(const char* fill)
{
    if(fill == nullptr || m_fill == fill)
        return;
    delete[] m_fill;
    m_fill = new char[strlen(fill) + 1];
    strcpy(m_fill, fill);
}

void Figure::setStroke(const char* stroke)
{
    if(stroke == nullptr || m_stroke == stroke)
        return;
    delete[] m_stroke;
    m_stroke = new char[strlen(stroke) + 1];
    strcpy(m_stroke, stroke);
}


std::ostream &operator<<(std::ostream &os, const Figure &fig)
{
    return os << fig.getType() << " " << fig.getFill() << " " << fig.getStroke() << " "  << fig.getStrokeWidth();
}

Figure::~Figure()
{
    delete[] m_type;
    delete[] m_fill;
    delete[] m_stroke;
}