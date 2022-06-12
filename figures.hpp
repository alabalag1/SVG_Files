#ifndef __FIGURES_HPP
#define __FIGURES_HPP

#include<iostream>
#include<cstring>

class Figure
{
private:
    char *m_fill;
    char *m_stroke;
    float m_strokeWidth;

public:
    Figure() : m_fill{"none"}, m_stroke{"none"}, m_strokeWidth{0} {};
    Figure(const char* fill, const char* stroke, float strokeWidth) : m_strokeWidth{strokeWidth} 
    {
        setFill(fill);
        setStroke(stroke);
    };
    void setFill(const char* fill);
    void setStroke(const char *stroke);
    ~Figure();
};



#endif