#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f
{
public:
    Vector3f(float x=0.0, float y=0.0, float z=0.0);
    ~Vector3f();

    void normalize();

    void set(Vector3f op);

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float getX() const;
    float getY() const;
    float getZ() const;

    Vector3f crossProduct(Vector3f *op) const;
    Vector3f realProduct(float op) const;
    float dotProduct(Vector3f *op) const;
    Vector3f subtract(Vector3f *op) const;
    Vector3f add(Vector3f *op) const;

    void stdPrint();
private:
    float x;
    float y;
    float z;
};

#endif // VECTOR3F_H
