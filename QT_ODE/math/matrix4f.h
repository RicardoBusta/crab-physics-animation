#ifndef MATRIX4_H
#define MATRIX4_H

class Vector3f;

class Matrix4f
{
public:
    Matrix4f();

    void set(int position, float value);
    void set(Matrix4f *matrix);

    void setIdentity();

    void get(float output[]) const;
    float get(int index) const;

    void setPos(float x, float y, float z);
    void setPos( Vector3f pos );

    void setRotation( Vector3f dir, Vector3f up );

    void translate(float x, float y, float z);
    void translate( Vector3f vector );

    void transpose();

    #ifdef DEBUG_MODE
    void stdPrint() const;
    #endif
private:
    float matrix[16];
};

#endif // MATRIX4_H
