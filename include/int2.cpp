#include "int2.hpp"

int2::int2(void) : _x(0), _y(0) {}

int2::int2(int x, int y) : _x(x), y(y) {}

int2::~int2(void) {}

int2    int2::operator+(const int2& a)const
{
    return (int2(_x + a._x, _y + a._y));
}

int2&    int2::operator=(const int2& a)
{
    if (&a != this)
    {
        _x = a._x;
        _y = a._y;
    }
    return (*this);
}