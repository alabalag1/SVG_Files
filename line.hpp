#ifndef __LINE_HPP
#define __LINE_HPP

#include "figures.hpp"
#include<iostream>


class Line : public Figure
{
private:
    float m_x1;
    float m_y1;
    float m_x2;
    float m_y2;

public:
    Line() : m_x1{0}, m_y1{0}, m_x2{0}, m_y2{0} {};
    Line(float x1, float y1, float x2, float y2) : m_x1{x1}, m_y1{y1}, m_x2{x2}, m_y2{y2} {};
    ~Line();
};

#endif