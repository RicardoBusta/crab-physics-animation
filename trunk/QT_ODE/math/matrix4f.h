#ifndef MATRIX4_H
#define MATRIX4_H

class Matrix4f
{
public:
    Matrix4f();

    void set(int position, float value);

    void get(float output[]) const;
    float get(int index) const;

    #ifdef DEBUG_MODE
    void stdPrint() const;
    #endif
private:
    float matrix[16];
};

#endif // MATRIX4_H
