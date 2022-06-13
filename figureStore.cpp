#include "figureStore.hpp"
#include<iostream>

void figureStore::addRect(const Rectangle& rect)
{
    figures[count++] = new Rectangle(rect);
}


void figureStore::print()
{
    for (size_t i = 0; i < count; i++)
        std::cout << figures[i] << " ";
}
