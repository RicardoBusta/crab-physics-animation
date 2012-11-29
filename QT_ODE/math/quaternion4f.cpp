#include "quaternion4f.h"

Quaternion4f::Quaternion4f(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion4f Quaternion4f::operator =(Quaternion4f q)
{
    this->w = q.w;
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;

    return *this;
}
