#ifndef QUATERNION4F_H
#define QUATERNION4F_H

class Quaternion4f
{
public:
    Quaternion4f(float w=1.0, float x=0.0, float y=0.0, float z=0.0);

public:
    float w;
    float x;
    float y;
    float z;

    Quaternion4f operator=(Quaternion4f q);
};

#endif // QUATERNION4F_H
