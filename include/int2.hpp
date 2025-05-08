#ifndef INT2_HPP
#define INT2_HPP

class   int2
{
    public:
        int _x;
        int _y;
        int2(void);
        int2(int x, int y);
        ~int2(void);
        int2    operator+(const int2& a)const;
        int2&    operator=(const int2& a);
};

#endif