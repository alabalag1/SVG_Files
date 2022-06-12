#include "figure.hpp"
#include<iostream>
#include<cstring>

Figure::Figure(const char *type, const char *fill, const char *stroke, float strokeWidth) {}


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

Figure::~Figure()
{
    delete[] m_fill;
    delete[] m_stroke;
}