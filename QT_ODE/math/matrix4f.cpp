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

float Matrix4f::getPosX(){
    return matrix[12];
}
float Matrix4f::getPosY(){
    return matrix[13];
}
float Matrix4f::getPosZ(){
    return matrix[14];
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

void Matrix4f::setRotation(Vector3f dir, Vector3f up)
{
    //---------------------------------
    Vector3f forward;
    forward.set( dir );
    forward.normalizeSelf();
    //---------------------------------
    Vector3f side;
    if(forward == up){
        up.addSelfX(1);
    }
    side.set( forward.crossProduct( &up ) );
    side.normalizeSelf();
    //---------------------------------
    Vector3f rup;
    rup.set( side.crossProduct( &forward ) );
    //---------------------------------
    set( 0, side.getX() );
    set( 1, side.getY() );
    set( 2, side.getZ() );
    set( 3, 0 );
    //------------------
    set( 4, rup.getX() );
    set( 5, rup.getY() );
    set( 6, rup.getZ() );
    set( 7, 0 );
    //------------------
    set( 8, -forward.getX() );
    set( 9, -forward.getY() );
    set(10, -forward.getZ() );
    set(11, 0 );
    //------------------
    set(12, 0 );
    set(13, 0 );
    set(14, 0 );
    set(15, 1 );
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
