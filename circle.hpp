#ifndef __CIRCLE_HPP
#define __CRICLE_HPP

#include "figure.hpp"
#include<iostream>


class Circle : public Figure
{
private:
    float m_cx;
    float m_cy;
    float m_r;

public:
    Circle(const char* type = "circle", float cx = 0, float cy = 0, float r = 0, const char* fill = "none", const char* stroke = "none", float strokeWidth = 0);
    ~Circle();
};


#endif