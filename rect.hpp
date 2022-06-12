#ifndef __RECT_HPP
#define __RECT_HPP

#include "figures.hpp"
#include<iostream>


class Rectangle : public Figure
{
private:
    float m_x;
    float m_y;
    float m_width;
    float m_heigth;

public:
    Rectangle() : m_x{0}, m_y{0}, m_heigth{0}, m_width{0} {};
    Rectangle(float x, float y, float width, float heigth) : m_x{x}, m_y{y}, m_heigth{heigth}, m_width{width} {};
    ~Rectangle();
};

#endif