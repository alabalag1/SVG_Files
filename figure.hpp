#ifndef __FIGURE_HPP
#define __FIGURE_HPP

#include<iostream>
#include<cstring>

class Figure
{
private:
    char *type;
    char *m_fill;
    char *m_stroke;
    float m_strokeWidth;

public:
    Figure(const char *type = "none",const char *fill = "none", const char *stroke = "none", float strokeWidth = 0);
    void setFill(const char *fill);
    void setStroke(const char *stroke);
    ~Figure();
};



#endif