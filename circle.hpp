#ifndef __CIRCLE_HPP
#define __CRICLE_HPP

#include "figures.hpp"
#include<iostream>


class Circle : public Figure
{
private:
    float m_cx;
    float m_cy;
    float m_r;

public:
    Circle() : m_cx{0},m_cy{0},m_r{0} {};
    Circle(float cx, float cy, float r) : m_cx{cx}, m_cy{cy}, m_r{r} {};
    ~Circle();
};


#endif