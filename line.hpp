#ifndef __LINE_HPP
#define __LINE_HPP

#include "figures.hpp"
#include<iostream>


class Line : public Figure
{
private:
    float x1;
    float y1;
    float x2;
    float y2;

public:
    Line(/* args */);
    ~Line();
};

Line::Line(/* args */)
{
}

Line::~Line()
{
}


#endif