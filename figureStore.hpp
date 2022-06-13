#ifndef __FIGURESTORE_HPP
#define __FIGURESTORE_HPP

#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

#include <iostream>

class figureStore
{
private:
    Figure **figures;
    size_t capacity;
    size_t count;

public:
    figureStore();

    void addCircle(const Circle& circle);
    void addRect(const Rectangle& rect);
    void addLine(const Line& line);

    void print();
    Figure &erase();
    ~figureStore();
};

figureStore::~figureStore()
{
    for (size_t i = 0; i < count;i++)
        delete[] figures[i];
}

#endif