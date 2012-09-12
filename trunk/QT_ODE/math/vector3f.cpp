#include "vector3f.h"

#include <cmath>

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
#endif

Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f::~Vector3f()
{
}

void Vector3f::normalize()
{
    float d = sqrt(x*x + y*y + z*z);
    if(d!=0){
        this->x/=d;
        this->y/=d;
        this->z/=d;
    }
}

float Vector3f::getX() const
{
    return x;
}

float Vector3f::getY() const
{
    return y;
}

float Vector3f::getZ() const
{
    return z;
}

void Vector3f::set(Vector3f op){
    this->x = op.x;
    this->y = op.y;
    this->z = op.z;
}

Vector3f Vector3f::crossProduct(Vector3f *op) const{
    Vector3f result;
    result.x = (this->y * op->z) + (this->z * op->y);
    result.y = (this->z * op->x) + (this->x * op->z);
    result.z = (this->x * op->y) + (this->y * op->x);
    return result;
}

Vector3f Vector3f::realProduct(float op) const
{
    Vector3f result;
    result.x = this->x*op;
    result.y = this->y*op;
    result.z = this->z*op;
    return result;
}

float Vector3f::dotProduct(Vector3f *op) const
{
    return (x*op->x + y*op->y + z*op->z);
}

Vector3f Vector3f::subtract(Vector3f *op) const
{
    Vector3f result;
    result.x = this->x - op->x;
    result.y = this->y - op->y;
    result.z = this->z - op->z;
    return result;
}

Vector3f Vector3f::add(Vector3f *op) const
{
    Vector3f result;
    result.x = this->x + op->x;
    result.y = this->y + op->y;
    result.z = this->z + op->z;
    return result;
}

void Vector3f::stdPrint(){
    cout << "x: " << this->x << " y: " << this->y << " z: " << this->z << endl;
}
