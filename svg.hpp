#ifndef __SVG_HPP
#define __SVG_HPP

#include"figure.hpp"
#include"circle.hpp"
#include"rect.hpp"
#include"line.hpp"
#include<vector>
#include<iostream>
#include<fstream>

class svg
{
private:
    std::vector<Figure> figures;

public:
    svg(/* args */);
    ~svg();
};

svg::svg(/* args */)
{
}

svg::~svg()
{
}


#endif