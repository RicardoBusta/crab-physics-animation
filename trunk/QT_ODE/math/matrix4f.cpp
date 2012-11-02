#include "matrix4f.h"

#include <cstring>

#include "math/vector3f.h"

Matrix4f::Matrix4f()
{
}

void Matrix4f::set(int position, float value)
{
    if(position >= 0 and position < 16){
        matrix[position] = value;
    }
}

void Matrix4f::set(Matrix4f *matrix)
{
    memcpy(this->matrix, matrix->matrix, 16*sizeof(float));
}

void Matrix4f::setIdentity()
{
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrix[i]=1;
        }else{
            matrix[i]=0;
        }
    }
}

void Matrix4f::get(float output[]) const
{
    memcpy(output, matrix, 16*sizeof(float));
}

float Matrix4f::get(int index) const
{
    if(index > 0 and index < 16){
        return matrix[index];
    }else{
        return 0;
    }
}

void Matrix4f::setPos(float x, float y, float z)
{
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void Matrix4f::setPos( Vector3f pos )
{
    matrix[12] = pos.getX();
    matrix[13] = pos.getY();
    matrix[14] = pos.getZ();
}

void Matrix4f::translate(float x, float y, float z)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] +=z;
}

void Matrix4f::translate(Vector3f vector)
{
    matrix[12] += vector.getX();
    matrix[13] += vector.getY();
    matrix[14] += vector.getZ();
}

void Matrix4f::transpose()
{
    for(int i=0;i<4;i++){
        for(int j=i+1;j<4;j++){
            int i1 = i+4*j, i2 = j+4*i;
            float aux = matrix[i1];
            matrix[i1] = matrix[i2];
            matrix[i2] = aux;
        }
    }
}

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;

void Matrix4f::stdPrint() const
{
    cout << "==Matrix=="<< endl;
    for(int i=0;i<4;i++){
        cout << matrix[0+i] << " " << matrix[4+i] << " " << matrix[8+i] << " " << matrix[12+i] << endl;
    }
    cout << "=========="<< endl;
}
#endif
