#include "circle.hpp"
#include<iostream>

Circle::Circle(const char *type, float x, float y, float r, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_x{x}, m_y{y}, m_r{r} {}