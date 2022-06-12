#include "circle.hpp"
#include<iostream>

Circle::Circle(const char *type, float cx, float cy, float r, const char *fill, const char *stroke, float strokeWidth)
    : Figure(type, fill, stroke, strokeWidth), m_cx{cx}, m_cy{cy}, m_r{r} {}