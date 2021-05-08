#include <iostream>
#include <vector>
#ifndef TEMPLATE_H
#define TEMPLATE_H
template <class T>
class PointOnPlane
{
private:
    T x;
    T y;
public:
    PointOnPlane(T x = 0, T y = 0);
    void foo(T x = 0, T y = 0);
    T get_x(){return this->x;};
    T get_y(){return this->y;};
    //
    PointOnPlane<T>& operator +=(PointOnPlane<T> P)
    {
        this->x += P.x;
        this->y += P.y;
        return *this;
    }
    PointOnPlane<T>& operator / (int size)
    {
        this->x /= size;
        this->y /= size;
        return *this;
    }
};
template <typename T>
void PointOnPlane<T>::foo(T x, T y){ std::cout<<x<<", "<<y<<" "<<typeid(T).name();}

template <typename T>
PointOnPlane<T>::PointOnPlane(T x, T y)
{
    this->x = x;
    this->y = y;
}

#endif // TEMPLATE_H
