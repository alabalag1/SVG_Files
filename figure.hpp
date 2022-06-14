#ifndef __FIGURE_HPP
#define __FIGURE_HPP

#include<iostream>
#include<cstring>

class Figure
{
private:
    char *m_type;
    char *m_fill;
    char *m_stroke;
    float m_strokeWidth;

public:
    Figure(const char *type = "none",const char *fill = "none", const char *stroke = "none", float strokeWidth = 0);

    char const* getType() const { return m_type; };
    char const* getFill() const { return m_fill; };
    char const* getStroke() const { return m_stroke; };
    float getStrokeWidth() const { return m_strokeWidth; };

    virtual std::ostream& print(std::ostream& = std::cout) const = 0;

    void setType(const char *type);
    void setFill(const char *fill);
    void setStroke(const char *stroke);
    void setStrokeWidth(const float strokeWidth) { m_strokeWidth = strokeWidth; };

    ~Figure();
};
std::ostream &operator<<(std::ostream &os, const Figure &figure) { return figure.print(os); };



#endif